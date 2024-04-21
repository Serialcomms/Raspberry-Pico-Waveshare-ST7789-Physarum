
void display_init_lcd();

void display_start_pixels();

void display_write_data_byte(uint8_t data_byte);

void display_write_command_byte(uint8_t write_command_byte);

void write_command_byte(uint8_t write_command);

enum ST7789_SCREEN { 
    
    LCD_COMMAND         =   0, 
    LCD_DATA            =   1, 
    LCD_WIDTH           = 240, 
    LCD_HEIGHT          = 240, 
    LCD_WIDTH_DIV_2     = LCD_WIDTH / 2,
    LCD_HEIGHT_DIV_2    = LCD_HEIGHT / 2,


} __packed ;

enum ST7789_COLOURS {

    BLACK   =   0x0000,
    BLUE    =   0x001F,
    RED     =   0xF800,
    GREEN   =   0x07E0,
    CYAN    =   0x07FF,
    MAGENTA =   0xF81F,
    YELLOW  =   0xFFE0,
    WHITE   =   0xFFFF

};

enum ST7789_BUFFER {

    DMA_DISPLAY_BUFFER_BYTES = LCD_WIDTH * LCD_HEIGHT * 2 

};