#include <math.h>
#include "pico/float.h"
#include "pico/stdlib.h"
#include "pico/printf.h"
#include "pico/stdio_usb.h"

#include "include/waveshare_gpio.h"
#include "include/waveshare_pins.h"
#include "include/waveshare_irq.h"

 void panel_gpio_init() {

    // Waveshare 1.3 inch LCD Display Module, Joypad and 4 buttons

    set_panel_gpio(KEY_A);
    set_panel_gpio(KEY_B);
    set_panel_gpio(KEY_X);
    set_panel_gpio(KEY_Y);

    set_panel_gpio(JOY_UP);
    set_panel_gpio(JOY_DOWN);
    set_panel_gpio(JOY_LEFT);
    set_panel_gpio(JOY_RIGHT);
    set_panel_gpio(JOY_CENTRE);
    
    gpio_init(PIN_BL);
    gpio_init(PIN_RESET);
    gpio_init(PICO_DEFAULT_LED_PIN);
   
    gpio_set_dir(PIN_BL, GPIO_OUT);
    gpio_set_dir(PIN_RESET, GPIO_OUT);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    
    gpio_put(PIN_BL, 1);
    gpio_put(PIN_RESET, 1);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    #define RISE_AND_FALL GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL

    gpio_set_irq_enabled_with_callback(JOY_UP, RISE_AND_FALL, true, &gpio_callback_all);  // irq is for all gpios

    gpio_set_irq_enabled(JOY_DOWN,      RISE_AND_FALL, true);
    gpio_set_irq_enabled(JOY_LEFT,      RISE_AND_FALL, true);
    gpio_set_irq_enabled(JOY_RIGHT,     RISE_AND_FALL, true);
    gpio_set_irq_enabled(JOY_CENTRE,    RISE_AND_FALL, true);

    gpio_set_irq_enabled(KEY_A,         RISE_AND_FALL, true);
    gpio_set_irq_enabled(KEY_B,         RISE_AND_FALL, true);
    gpio_set_irq_enabled(KEY_X,         RISE_AND_FALL, true);
    gpio_set_irq_enabled(KEY_Y,         RISE_AND_FALL, true);

}

void set_panel_gpio(uint gpio_pin_number) {

    gpio_init(gpio_pin_number);
    gpio_pull_up(gpio_pin_number);
    gpio_set_dir(gpio_pin_number, GPIO_IN);
}
