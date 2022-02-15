add_library(libcJson cJSON.c cJSON.h cJSON_Utils.c cJSON_Utils.h)
target_include_directories(libcJson PUBLIC FreeRTOS-Kernel/include include/ FreeRTOS-Kernel/portable/GCC/ARM_CM .)
target_link_libraries(libcJson PUBLIC pico_stdlib FreeRTOS pico-cpp)