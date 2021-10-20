#include <stdlib.h>
#include "qmk_rc.h"

#ifndef QMK_RC_DISABLE_DEFAULT_COMMANDS
#  include <string.h>
#  include "quantum.h"
#  ifdef OLED_DRIVER_ENABLE
#    include "oled_driver.h"
#  endif
#endif

__attribute__((weak)) void qmk_rc_process_command_user(qmk_rc_command_t* command) { }


enum qmk_rc_commands_quantum {
  RESERVED = 0,
#ifndef QMK_RC_DISABLE_DEFAULT_COMMANDS
  OLED_ON,
  OLED_OFF,
  OLED_WRITE,
  OLED_CLEAR,

  LAYER_ON,
  LAYER_OFF,
  LAYER_CLEAR,
  LAYER_MOVE,

  SEND_STRING,
#endif
};

#ifndef QMK_RC_DISABLE_DEFAULT_COMMANDS
void qmk_rc_process_command_quantum(qmk_rc_command_t* command) {
  switch (command->id) {
#ifdef OLED_DRIVER_ENABLE
    case OLED_WRITE: {
        if (is_keyboard_master()) {
          oled_write((const char*) command->data, false);
        }
      break;
    }
    case OLED_CLEAR: {
        if (is_keyboard_master()) {
            oled_clear();
        }
        break;
    };
    case OLED_OFF: oled_off(); break;
    case OLED_ON: oled_on(); break;
#endif

    case LAYER_ON: layer_on(command->data[0]); break;
    case LAYER_OFF: layer_off(command->data[0]); break;
    case LAYER_CLEAR: layer_clear(); break;
    case LAYER_MOVE: layer_move(command->data[0]); break;

    case SEND_STRING: send_string((const char*) command->data); break;

    default:
      qmk_rc_process_command_user(command);
  }
}
#else
#  define qmk_rc_process_command_quantum qmk_rc_process_command_user
#endif

qmk_rc_parser_t parser = {
  .state = RECEIVING_COMMAND,
  .data_bytes_read = 0,
};

qmk_rc_command_t command = {
  .id = UINT8_MAX,
  .data_length = 0,
  .data = NULL,
};

void qmk_rc_receive(uint8_t *buffer, uint16_t max_buffer_length, uint8_t* data, uint8_t data_length) {
  for (int i = 0; i < data_length; i++) {
    if (parser.state == RECEIVING_COMMAND) {
      // Raw HID packets are padded to `RAW_EPSIZE`, 32 or 64 bytes. Since this
      // is an afterthought for this parser, we reserve the 0 command code as
      // a "skip" instruction in receiving command mode. In the sender we then
      // universally pad to 64 bytes with 0s.
      if (data[i] == 0) continue;

      command.id = data[i];
      parser.state = RECEIVING_DATA_LENGTH;

      parser.data_length_bytes_read = 0;
      parser.data_length.data_length = 0;
    }
    else if (parser.state == RECEIVING_DATA_LENGTH) {
      parser.data_length.raw[parser.data_length_bytes_read++] = data[i];

      if (parser.data_length_bytes_read == sizeof(qmk_rc_data_length_t)) {
        command.data_length = parser.data_length.data_length;

        command.data = NULL;

        if (command.data_length == 0) {
          qmk_rc_process_command_quantum(&command);
          parser.state = RECEIVING_COMMAND;
        }
        else {
          parser.state = RECEIVING_DATA;
          parser.data_bytes_read = 0;
        }
      }
    }
    else if (parser.state == RECEIVING_DATA) {
      buffer[parser.data_bytes_read++] = data[i];
      if (parser.data_bytes_read == command.data_length) {
        command.data = buffer;
        qmk_rc_process_command_quantum(&command);
        parser.state = RECEIVING_COMMAND;
      }
    }
  }
}
