cmake_minimum_required(VERSION 3.12)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)
add_subdirectory(pico-cpp)
project(picoKey)
add_subdirectory(lib)

# initialize the Pico SDK
pico_sdk_init()


add_executable(picoKey
    src/main.cpp
    src/mainApp.cpp 
    src/ledHelper.cpp 
    src/usbHelper.cpp 
    src/keyHelper.cpp 
    src/displayHelper.cpp 
    src/utils.cpp    
)

target_sources(picoKey PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/usb_descriptors.c ${CMAKE_CURRENT_LIST_DIR}/src/msc_disk_dual.c)

# Make sure TinyUSB can find tusb_config.h
include_directories(picoKey PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

# Add pico_stdlib library which aggregates commonly used features
#target_link_libraries(picoKey PUBLIC pico_stdlib pico_stdlib tinyusb_device tinyusb_board)
add_library(FreeRTOS STATIC FreeRTOS-Kernel/croutine.c
FreeRTOS-Kernel/event_groups.c
FreeRTOS-Kernel/list.c
FreeRTOS-Kernel/queue.c
FreeRTOS-Kernel/stream_buffer.c
FreeRTOS-Kernel/tasks.c
FreeRTOS-Kernel/timers.c
FreeRTOS-Kernel/portable/GCC/ARM_CM0/port.c
FreeRTOS-Kernel/portable/MemMang/heap_4.c
src/FreeRTOS_Support_Files/IdleMemory.c
)

target_include_directories(FreeRTOS PUBLIC FreeRTOS-Kernel/include include/ FreeRTOS-Kernel/portable/GCC/ARM_CM0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(picoKey)
target_link_libraries(picoKey PUBLIC pico_stdlib hardware_flash tinyusb_device tinyusb_board FreeRTOS pico-cpp hardware_i2c libeeprom liboled)
add_custom_command(TARGET picoKey
        POST_BUILD
        COMMAND arm-none-eabi-size picoKey.elf
        )

pico_enable_stdio_usb(picoKey 1)
# rest of your project