#include <math.h>
#include <pico.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/rand.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/divider.h"
#include "include/random.h"
#include "include/physarum.h"
#include "include/core_0_main.h"
#include "include/waveshare_st7789.h"

// https://github.com/jlswbs/Pico_ST7789_240x240/tree/main

uint32_t P, Q, T;
uint16_t P_VALUE_THRESHOLD;
uint16_t grid[LCD_WIDTH][LCD_HEIGHT]; 

bool STEP_COMPLETE;
extern uint8_t ACTIVE_COLONIES;

void  __not_in_flash_func(nextstep)() {

  int x = __fast_mul(2, (1 + rand() % LCD_WIDTH_DIV_2 - 1));
  int y = __fast_mul(2, (1 + rand() % LCD_HEIGHT_DIV_2 - 1));

  if (x_y_grid_check(x, y, 100, 1000)) {
      
    grid_value_small(x, y);
      
  } else if (x_y_grid_check(x, y, 1000, 2000)) {
      
    grid_value_medium(x, y);

  } else if (grid[x][y] >= 9000)

    grid_value_large(x, y);
         
}

inline void __not_in_flash_func (p_value_small)(int x, int y) {

  T = 1 + rand() % 5;

  uint32_t Q2 = __fast_mul(Q, 100);

  switch (T) {

    case 1:   if (grid[x+2][y] == 0) { grid[x+2][y] = Q2; grid[x+1][y] = Q2; } break;
    case 2:   if (grid[x][y+2] == 0) { grid[x][y+2] = Q2; grid[x][y+1] = Q2; } break;
    case 3:   if (grid[x-2][y] == 0) { grid[x-2][y] = Q2; grid[x-1][y] = Q2; } break;
    case 4:   if (grid[x][y-2] == 0) { grid[x][y-2] = Q2; grid[x][y-1] = Q2; } break;

    default:  break;

  }

  grid[x][y] = grid[x][y] + 1;

}

inline void __not_in_flash_func(p_value_large)(int x, int y) {

  T = 0;
  
  if (grid[x+1][y] > 1) T = T + 1;
  if (grid[x][y+1] > 1) T = T + 1;
  if (grid[x-1][y] > 1) T = T + 1;
  if (grid[x][y-1] > 1) T = T + 1;
        
  if (T <= 1) {
        
    grid[x][y] = 9100;
    grid[x+1][y] = 0;
    grid[x][y+1] = 0;
    grid[x-1][y] = 0;
    grid[x][y-1] = 0; 
  
  }

}

inline void __not_in_flash_func(grid_value_small)(int x, int y) {

  Q = div_u32u32(grid[x][y], 100);

  P = grid[x][y] - __fast_mul(Q, 100);

  if (P < P_VALUE_THRESHOLD) {

    p_value_small(x, y);
        
  } else {
        
    p_value_large(x, y);

  }      

}

inline void __not_in_flash_func(grid_value_medium)(int x, int y) {

  Q = div_u32u32(grid[x][y], 100) - 10;

  uint32_t Q2 = __fast_mul(Q, 100);
  
  if (grid[x+2][y] == 0) { grid[x+2][y] = Q2; grid[x+1][y] = Q2; }
  if (grid[x][y+2] == 0) { grid[x][y+2] = Q2; grid[x][y+1] = Q2; }
  if (grid[x-2][y] == 0) { grid[x-2][y] = Q2; grid[x-1][y] = Q2; }
  if (grid[x][y-2] == 0) { grid[x][y-2] = Q2; grid[x][y-1] = Q2; }
    
}

inline void __not_in_flash_func(grid_value_large)(int x, int y) {

  grid[x][y] -= 1;

  if (grid[x][y] < 9000) grid[x][y] = 0; 

}

inline bool __not_in_flash_func(x_y_grid_check)(int x, int y, int min, int max) {
  
  uint16_t grid_value = grid[x][y];

  return ((grid_value >= min) && (grid_value < max)) ;

}

void physarum_defaults() {

  ACTIVE_COLONIES = 2;

  P_VALUE_THRESHOLD = MAX(9, get_rand_32() % 21);
 
}