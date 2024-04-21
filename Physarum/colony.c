
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "include/colony.h"
#include "include/random.h"
#include "include/physarum.h"

uint8_t ACTIVE_COLONIES;

struct colony_profile colony[8];

void all_colony() {
 
  uint8_t offset = 0;
  
  uint8_t colony_count = count_of(colony);
 
  uint32_t random_RGB = pico_random_RGB565();

  do {
    
    colony[offset].colour_16 = random_RGB; 
    colony[offset].colour_8L = random_RGB % 0x100;
    colony[offset].colour_8H = random_RGB / 0x100;

  } while (++offset < colony_count);

}

void inv_colony() {

  uint8_t offset = 0;
  
  uint8_t colony_count = count_of(colony);
 
  do {
    
    uint8_t temp_colony_8L;
    uint8_t temp_colony_8H;
    
    colony[offset].colour_16 = !colony[offset].colour_16; 
    
    temp_colony_8L = colony[offset].colour_8L;
    temp_colony_8H = colony[offset].colour_8H;

    colony[offset].colour_8L = temp_colony_8H;
    colony[offset].colour_8H = temp_colony_8L;

  } while (++offset < colony_count);


}

void rnd_colony() {

  uint8_t offset = 0;
  
  uint32_t random_RGB;
  
  uint8_t colony_count = count_of(colony);

  do {

    random_RGB = pico_random_RGB565();

    colony[offset].colour_16 = random_RGB; 
    colony[offset].colour_8L = random_RGB % 0x100;
    colony[offset].colour_8H = random_RGB / 0x100;

  } while (++offset < colony_count);

}

void dec_colony() {

  uint8_t offset = 0;
  
  uint8_t colony_count = count_of(colony);

  do {

    colony[offset].colour_16 += 1;
    colony[offset].colour_8L -= 1;
    colony[offset].colour_8H -= 1;

  } while (++offset < colony_count);

}