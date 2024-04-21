#include "pico/binary_info.h"
#include "include/waveshare_pins.h"

void set_binary_declarations() { // for use with Picotool

    bi_decl(bi_program_description("Waveshare LCD"));
    
    bi_decl(bi_program_feature("1.3 Inch LCD panel"));
    bi_decl(bi_program_feature("Joypad and buttons"));
    bi_decl(bi_program_version_string("Demo Version DMA/SPI1"));
    bi_decl(bi_1pin_with_name(PIN_DC, "LCD Data/Command"));
    bi_decl(bi_1pin_with_name(PIN_CS, "LCD Chip Select"));
    bi_decl(bi_1pin_with_name(PIN_BL, "LCD Backlight"));
    bi_decl(bi_1pin_with_name(PIN_CLK, "LCD Clock"));
    bi_decl(bi_1pin_with_name(PIN_DIN, "LCD Receive Data"));
    bi_decl(bi_1pin_with_name(PIN_RESET, "LCD Reset"));

    bi_decl(bi_1pin_with_name(KEY_A, "Button A"));
    bi_decl(bi_1pin_with_name(KEY_B, "Button B"));
    bi_decl(bi_1pin_with_name(KEY_X, "Button X"));
    bi_decl(bi_1pin_with_name(KEY_Y, "Button Y"));
}

