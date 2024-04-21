add_executable(waveshare_physarum)

target_sources(waveshare_physarum PRIVATE 

    core_0_main.c 
    core_0_menu.c
    core_1_main.c 
    physarum.c 
    random.c 
    colony.c 
    waveshare_irq.c 
    waveshare_gpio.c 
    waveshare_st7789.c 
    pico_dma.c 
    pico_spi.c 
    pico_binary.c
    
)

target_link_libraries(waveshare_physarum PRIVATE 
    
    pico_stdlib 
    pico_rand
    pico_multicore 
    hardware_spi 
    hardware_dma 

    )

# enable usb output, disable uart output
pico_enable_stdio_usb(waveshare_physarum 1)
pico_enable_stdio_uart(waveshare_physarum 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(waveshare_physarum)

# add url via pico_set_program_url
pico_set_program_url(waveshare_physarum "https://github.com/Serialcomms/Raspberry-Pico-Waveshare-ST7789-Physarum")

# pico_set_binary_type(waveshare_physarum copy_to_ram)
# insufficent RAM for above due to framebuffer size
