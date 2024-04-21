
#include "stdio.h"
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "include/st7789_commands.h"
#include "include/waveshare_st7789.h"
#include "include/waveshare_pins.h"

// Format: cmd length (including cmd byte), post delay in units of 5 ms, then command payload.
// Simplified initialisation using power-on/swreset default values, including CASET and RASET.
// derived from Pico examples

const uint8_t st7789_init_sequence[] = {

        1, 2, NOP,                             // No Operation - 10ms power on delay
        1, 2, SWRESET,                         // Software reset, 10ms stability delay
        1, 2, SLPOUT,                          // Exit sleep mode, 10ms stability delay
        2, 0, COLMOD, 0x55,                    // Set interface colour mode to 16 bits/pixel
        2, 0, MADCTL, 0x60,                    // Set MADCTL for LCD 90° physical hardware orientation 
        1, 0, INVON,                           // Colour inversion on (positive image with supplied data)
        1, 1, DISPON,                          // Main screen display on, 5ms guard time
        0                                      // Terminate initialisation command list
};

void display_init_lcd() {
  
  const uint8_t *commands = st7789_init_sequence;

  const uint16_t init_seq_length = count_of(st7789_init_sequence); 

  uint8_t byte_count = *commands;
  uint8_t sleep_time = 0;
  uint8_t data_byte = 0;
  uint8_t command_byte = 0;

  while (byte_count) {

    byte_count = *commands++;
    sleep_time = *commands++;
    command_byte =  *commands++;

    if (byte_count > 0) {

      display_write_command_byte(command_byte);
  
      if (byte_count > 1) {

        for (size_t i = 1 ; i < byte_count ; ++i) {

        data_byte = *commands++;
   
        display_write_data_byte(data_byte);

        }

      }

      busy_wait_ms(sleep_time * 5);

    }
  
  }

}

void display_write_command_byte(uint8_t command_byte) {

  absolute_time_t spi_wait_timeout = make_timeout_time_us(100000);

  while (spi_is_busy(spi1) && !time_reached(spi_wait_timeout));  // allow any current spi activity to finish

  if (time_reached(spi_wait_timeout)) {

    printf("ERROR - Timeout waiting for SPI\n\r");

  } else {

    write_command_byte(command_byte);

  }

}

void display_write_data_byte(uint8_t data_byte) {

  spi_write_blocking(spi1, &data_byte, 1);

}

void write_command_byte(uint8_t write_command) {

  gpio_put(PIN_DC, LCD_COMMAND);

  spi_write_blocking(spi1, &write_command, 1);

  gpio_put(PIN_DC, LCD_DATA);

}


void display_start_pixels() {

  absolute_time_t spi_wait_timeout = make_timeout_time_ms(99);

  display_write_command_byte(RAMWR);

  while (spi_is_busy(spi1) && !time_reached(spi_wait_timeout));

  if (time_reached(spi_wait_timeout)) {

    printf("ERROR - Start Pixels Timeout waiting for SPI\n\r");

    busy_wait_ms(3000);

  }

}
