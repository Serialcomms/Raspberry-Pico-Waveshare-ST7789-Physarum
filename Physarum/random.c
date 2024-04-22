#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "pico/rand.h"
#include "include/random.h"
#include "include/waveshare_st7789.h"
#include "hardware/structs/rosc.h"

extern uint16_t grid[LCD_WIDTH][LCD_HEIGHT]; 

extern uint8_t ACTIVE_COLONIES;

void rndseed() {

  uint8_t colony_count = MAX(ACTIVE_COLONIES, 1);

  for (int y = 0; y < LCD_HEIGHT; y++) {  
    
    for (int x = 0; x < LCD_WIDTH; x++) {

        grid[x][y] = (x_y_limit_check(x, y)) ? 1 : 0;

    }

  }
  
  for (int i = 1; i < colony_count; i++){

    uint32_t random_x = get_rand_32();
    uint32_t random_y = get_rand_32();
    
    int x = __fast_mul(2, (5 + random_x % LCD_WIDTH_DIV_2 - 5));
    int y = __fast_mul(2, (5 + random_y % LCD_HEIGHT_DIV_2 - 5));

    if(grid[x][y] == 0) grid[x][y] = 1000 + __fast_mul(i, 100);

  }
  
}

uint16_t pico_random_RGB565() {
   
    uint16_t random_RGB565 = 0;

    uint8_t bias_R = 7;
    uint8_t bias_G = 15;
    uint8_t bias_B = 7;

    uint8_t random_bits_R = pow(2, 5) - 1;
    uint8_t random_bits_G = pow(2, 6) - 1;
    uint8_t random_bits_B = pow(2, 5) - 1;

    uint8_t pico_random_R = bias_R + (get_rand_32() % (random_bits_R - bias_R)) & 0x1F;
    uint8_t pico_random_G = bias_G + (get_rand_32() % (random_bits_G - bias_G)) & 0x3F;
    uint8_t pico_random_B = bias_B + (get_rand_32() % (random_bits_B - bias_B)) & 0x1F;

    random_RGB565 |= (pico_random_R << 11); 
    random_RGB565 |= (pico_random_G << 5); 
    random_RGB565 |= (pico_random_B); 

    return random_RGB565; 

}

inline bool __not_in_flash_func(x_y_limit_check)(int x, int y) {

    bool x_limit = (x == 0 || x == 1 || x == LCD_WIDTH - 2  || x == LCD_WIDTH - 1);

    bool y_limit = (y == 0 || y == 1 || y == LCD_HEIGHT - 2 || y == LCD_HEIGHT - 1);

    return x_limit || y_limit;

}

void seed_random_from_rosc() {
  
  uint32_t random = 0;
  uint32_t random_bit;

  for (int k = 0; k < 32; ++k) {
  
  while (1) {
  
    random_bit = rosc_hw->randombit;
  
    if (random_bit != rosc_hw->randombit & 1) break;
  
    }

    random = (random << 1) | random_bit;
  }

  srand(random);

}


uint8_t  __not_in_flash_func(small_random_from_rosc)() {
  
  uint32_t random = 0;
  uint32_t random_bit;

  for (int k = 0; k < 4; ++k) {
  
    random_bit = rosc_hw->randombit;
  
    random = (random << 1) | random_bit;
  }

  return random & 0x07;

}

uint8_t  __not_in_flash_func (get_random_from_rosc)(uint8_t bits) {

    uint32_t random = 0;
   
    uint8_t bit_count = MIN(bits, 7);

    do {
  
        random = (random << 1) | rosc_hw->randombit;

    } while (--bit_count);

  return random & 0x7F;  

}
