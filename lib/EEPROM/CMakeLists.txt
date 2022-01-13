add_library(libeeprom EEPROM.cpp EEPROM.h)
target_include_directories(libeeprom PUBLIC FreeRTOS-Kernel/include include/ FreeRTOS-Kernel/portable/GCC/ARM_CM .)
target_link_libraries(libeeprom PUBLIC pico_stdlib FreeRTOS pico-cpp hardware_flash)