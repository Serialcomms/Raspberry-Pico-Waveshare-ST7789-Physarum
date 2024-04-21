
#include <ctype.h>
#include "stdlib.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"

#include "pico/stdio_usb.h"
#include "pico/multicore.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

#include "include/random.h"
#include "include/physarum.h"
#include "include/pico_spi.h"
#include "include/pico_binary.h"
#include "include/core_0_main.h"
#include "include/core_1_main.h"
#include "include/core_0_menu.h"
#include "include/waveshare_gpio.h"
#include "include/waveshare_st7789.h"

extern bool STEP_COMPLETE;

int  __not_in_flash_func (main)() {

  core_0_setup();

  while (1) {

    check_console_input();

    if (STEP_COMPLETE) {

      update_buffer();

      STEP_COMPLETE = false;

    }

  }

  return 0;

}

void core_0_setup() {

  stdio_usb_init();

  busy_wait_ms(500);

  panel_gpio_init();

  set_binary_declarations();

  display_spi_master_init();

  display_init_lcd();

  busy_wait_ms(5);

  multicore_reset_core1();

  seed_random_from_rosc();

  busy_wait_ms(10);
   
  multicore_launch_core1(core_1_main_graphic_loop); 

  busy_wait_ms(100);

}

void __not_in_flash_func(check_console_input)() {

  int get_character = getchar_timeout_us(0);

  if (get_character != PICO_ERROR_TIMEOUT) {

    uint8_t menu_option = toupper(get_character & 0x7F);

    if (menu_option) { 

      select_menu_option(menu_option);
  
    }
    
  }

}

