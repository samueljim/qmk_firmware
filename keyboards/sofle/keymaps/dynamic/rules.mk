SRC += qmk_rc.c
AUTO_SHIFT_ENABLE = yes
OLED_DRIVER_ENABLE = yes
ENCODER_ENABLE = yes
CONSOLE_ENABLE = yes
EXTRAKEY_ENABLE = yes
RAW_ENABLE = yes
MOUSEKEY_ENABLE = yes
WPM_ENABLE = yes

Link_Time_Optimization = yes # Reduce size of firmware by optimizing at link time
EXTRAFLAGS += -flto
