//
// Waveshare LCD Module Pins (hardwired)
// hardwired to SPI1 as per RPI datasheet
// Pin 12 is anomalous - SPI1-RX on Pico, Reset on waveshare

enum PANEL_GPIO_SPI { 
    
    PIN_DC      =  8, 
    PIN_CS      =  9, 
    PIN_CLK     = 10, 
    PIN_DIN     = 11, 
    PIN_RESET   = 12, 
    PIN_BL      = 13 

} __packed ;

enum PANEL_GPIO_JOY { 
    
    JOY_UP      =  2, 
    JOY_DOWN    = 18, 
    JOY_LEFT    = 16, 
    JOY_RIGHT   = 20, 
    JOY_CENTRE  =  3 

} __packed ;

enum PANEL_GPIO_KEY { 
    
    KEY_A       = 15, 
    KEY_B       = 17, 
    KEY_X       = 19, 
    KEY_Y       = 21 
    
} __packed ;
