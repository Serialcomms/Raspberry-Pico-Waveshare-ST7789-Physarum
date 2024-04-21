// Sitronix ST7789VW Commands

enum ST7789_COMMANDS { 
    
    NOP         = 0x00,        // No Operation 
    SWRESET     = 0x01,        // Software Reset
    SLPOUT      = 0x11,        // Sleep Out
    NORON       = 0x13,        // Normal Display Mode On
    INVOFF      = 0x20,        // Display Inversion Off
    INVON       = 0x21,        // Display Inversion On
    DISPOFF     = 0x28,        // Display Off
    DISPON      = 0x29,        // Display On
    CASET       = 0x2A,        // Column Address Set 
    RASET       = 0x2B,        // Row Address Set
    RAMWR       = 0x2C,        // RAM Write
    RAMRD       = 0x2E,        // RAM Read
    TEOFF       = 0x34,        // Line Tearing Effect Off
    TEON        = 0x35,        // Line Tearing Effect On
    MADCTL      = 0x36,        // Memory Data Access Control
    IDMOFF      = 0x38,        // Idle Mode Off
    IDMON       = 0x39,        // Idle Mode On
    COLMOD      = 0x3A,        // Interface Pixel Format
    WRMEMC      = 0x3C,        // Write Memory Continue
    WRDISBV     = 0x51         // Write Display Brightness

} __packed;