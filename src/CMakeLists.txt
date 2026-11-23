# This is the main binary. List your C files here.
add_executable(lab4_test_fifo
    test_fifo.c
    fifo.c
    ../test/unity_config.c
    )

pico_set_program_name(lab4_test_fifo "test_fifo")
pico_set_program_version(lab4_test_fifo "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(lab4_test_fifo 1)
pico_enable_stdio_usb(lab4_test_fifo 0)

# Add the libraries to the build
target_link_libraries(lab4_test_fifo PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  unity
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
    target_link_libraries(lab4_test_fifo PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(lab4_test_fifo)

find_program(OPENOCD openocd)
find_program(PICOTOOL picotool)

add_custom_target(flash ${PICOTOOL} load -f $<TARGET_FILE:lab4_test_fifo> DEPENDS lab4_test_fifo)
add_custom_target(openocd_flash ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000' -c program "$<TARGET_FILE:lab4_test_fifo>" verify reset exit' DEPENDS lab4_test_fifo)
