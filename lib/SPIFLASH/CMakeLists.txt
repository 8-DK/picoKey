add_library(libspistorage Storage.cpp Storage.h)
target_include_directories(libspistorage PUBLIC FreeRTOS-Kernel/include include/ FreeRTOS-Kernel/portable/GCC/ARM_CM .)
target_link_libraries(libspistorage PUBLIC pico_stdlib FreeRTOS pico-cpp hardware_spi hardware_flash hardware_i2c tinyusb_device tinyusb_board)