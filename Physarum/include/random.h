
void rndseed();
uint16_t pico_random_RGB565();
uint8_t  __not_in_flash_func(small_random_from_rosc)();
uint8_t  __not_in_flash_func(get_random_from_rosc)(uint8_t bits);
bool __not_in_flash_func(x_y_limit_check)(int x, int y);
void __not_in_flash_func(core_1_main_graphic_loop)();