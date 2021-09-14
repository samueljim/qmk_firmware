
OLED_DRIVER_ENABLE = yes
ENCODER_ENABLE = yes
CONSOLE_ENABLE = no
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
RGBLIGHT_ENABLE = no

# If you want to change the display of OLED, you need to change here
SRC +=  ./glcdfont.c \

RAW_ENABLE = yes            # Enable RAW HID communication to PC

Link_Time_Optimization = yes # Reduce size of firmware by optimizing at link time
EXTRAFLAGS += -flto
