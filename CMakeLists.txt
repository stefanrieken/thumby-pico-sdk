cmake_minimum_required(VERSION 3.13)

include(../pico-sdk/pico_sdk_init.cmake)

project(hello)

pico_sdk_init()

add_executable(hello hello.c ssd1306.c write.c)

target_link_libraries(hello pico_stdlib hardware_pwm hardware_spi)

pico_enable_stdio_usb(hello 1)
pico_enable_stdio_uart(hello 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hello)
