OLED_DRIVER_ENABLE = yes
ENCODER_ENABLE = yes
CONSOLE_ENABLE = no
EXTRAKEY_ENABLE = no
WPM_ENABLE = yes
RAW_ENABLE = no
TAP_DANCE_ENABLE = no
STENO_ENABLE = no
BOOTMAGIC_ENABLE =no
TERMINAL_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
KEY_LOCK_ENABLE = no
AUDIO_ENABLE = no
CONSOLE_ENABLE = no
VELOCIKEY_ENABLE = no
RGBLIGHT_ENABLE = no
MOUSEKEY_ENABLE = yes

Link_Time_Optimization = yes # Reduce size of firmware by optimizing at link time
EXTRAFLAGS += -flto
