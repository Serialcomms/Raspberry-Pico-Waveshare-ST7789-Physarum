#include <math.h>
#include "pico/float.h"
#include "pico/stdlib.h"
#include "pico/divider.h"
#include "hardware/spi.h"
#include "include/colony.h"
#include "include/random.h"
#include "include/physarum.h"
#include "include/pico_dma.h"
#include "include/core_1_main.h"
#include "include/waveshare_st7789.h"
#include "include/waveshare_pins.h"

static const float PICO_PI = 3.14159265358979323846;

extern uint8_t txbuf[];

extern struct colony_profile colony[];

extern uint16_t grid[LCD_WIDTH][LCD_HEIGHT]; 

extern uint32_t   T;
extern uint32_t   Q;
extern bool       STEP_COMPLETE;
extern uint8_t    ACTIVE_COLONIES;
extern uint16_t   P_VALUE_THRESHOLD;
extern uint16_t   GRID_THRESHOLD_SMALL;

void  __not_in_flash_func(core_1_main_graphic_loop)() {

  core_1_setup();

  while (1) {

    nextstep();

    STEP_COMPLETE = true;

  }
 
}
 
void __not_in_flash_func(update_buffer)() {

  uint32_t buffer_position = 0;

  for (int y = 0; y < LCD_HEIGHT; y++) {  

    for (int x = 0; x < LCD_WIDTH; x++) {
    
      if (grid[x][y] >= 100 && grid[x][y] < 1000) {

        Q = (grid[x][y] / 100) % ACTIVE_COLONIES;

        txbuf[ buffer_position ++] = colony[Q].colour_8H;
        txbuf[ buffer_position ++] = colony[Q].colour_8L;

      } else {
        
        txbuf[ buffer_position ++] = 0;
        txbuf[ buffer_position ++] = 0;
  
      } 

    }

  }

}

void __not_in_flash_func(spi_write_st7789)(uint8_t spi_byte) {

  while (spi_is_busy(spi1));

  spi_write_blocking(spi1, &spi_byte, 1);

}

void core_1_setup() {

  display_data_dma_init();

  display_start_pixels();

  clear_display_buffer();

  trigger_dma_transfer();

  physarum_defaults();

  rnd_colony();

  rndseed();
  
}
