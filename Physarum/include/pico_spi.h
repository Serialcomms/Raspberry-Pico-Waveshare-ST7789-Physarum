void display_spi_master_init();

enum SPI_SETTINGS { 
    
    SPI_CLOCK_PHASE     = SPI_CPHA_0, 
    SPI_CLOCK_POLARITY  = SPI_CPOL_0, 
    SPI_BAUD_RATE       = 625 * 100000, 
    SPI_DATA_BITS       = 8
};