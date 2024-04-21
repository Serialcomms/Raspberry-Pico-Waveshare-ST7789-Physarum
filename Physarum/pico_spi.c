#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "include/pico_spi.h"
#include "include/waveshare_pins.h"

void display_spi_master_init() {
      
  gpio_set_function(PIN_CS,  GPIO_FUNC_SPI);
  gpio_set_function(PIN_CLK, GPIO_FUNC_SPI);
  gpio_set_function(PIN_DIN, GPIO_FUNC_SPI);

  gpio_put(PIN_CS, 1);

  gpio_init(PIN_DC);

  gpio_set_dir(PIN_DC, GPIO_OUT);
   
  spi_init(spi1, SPI_BAUD_RATE);

  spi_set_format(spi1, SPI_DATA_BITS, SPI_CLOCK_POLARITY, SPI_CLOCK_PHASE, SPI_MSB_FIRST);

}