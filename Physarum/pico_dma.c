
#include "hardware/dma.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/spi.h"
#include "include/waveshare_pins.h"
#include "include/waveshare_st7789.h"
#include "include/st7789_commands.h"
#include "include/pico_dma.h"
#include "pico/float.h"
#include "pico/stdlib.h"

uint8_t txbuf[DMA_DISPLAY_BUFFER_BYTES];

static uint dma_tx;

void display_data_dma_init() {

  dma_channel_config c;

  dma_tx = dma_claim_unused_channel(true);
 
  c = dma_channel_get_default_config(dma_tx);

  channel_config_set_read_increment(&c, true);
  channel_config_set_write_increment(&c, false);
  channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
  channel_config_set_dreq(&c, spi_get_dreq(spi1, true));

  dma_channel_set_read_addr(dma_tx, txbuf, true);
  dma_channel_set_write_addr(dma_tx, &spi_get_hw(spi1)->dr, false);
  dma_channel_set_trans_count(dma_tx, DMA_DISPLAY_BUFFER_BYTES, false);
  dma_channel_set_config(dma_tx, &c, false);

  dma_channel_set_irq0_enabled(dma_tx, true); 
  irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
  irq_set_enabled(DMA_IRQ_0, true);

}


void __not_in_flash_func (dma_handler)() {

  static const uint8_t RAM_WRITE = RAMWR;

  gpio_put(PIN_DC, LCD_COMMAND);

  spi_write_blocking(spi1, &RAM_WRITE, 1);

  gpio_put(PIN_DC, LCD_DATA);

  dma_irqn_acknowledge_channel(DMA_IRQ_0, dma_tx);

  trigger_dma_transfer();

}

void clear_display_buffer() {

  uint32_t offset = 0;

  uint32_t buffer_count = count_of(txbuf);

  do {

    txbuf[offset] = 0x00;

    ++offset;

  } while (--buffer_count);

}

void __not_in_flash_func (trigger_dma_transfer)() {

  const uint32_t buffer_size = count_of(txbuf);

  dma_channel_transfer_from_buffer_now(dma_tx, txbuf, buffer_size);

}