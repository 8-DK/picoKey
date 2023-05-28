cmake_minimum_required(VERSION 3.12)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)
set(PICO_CXX_ENABLE_RTTI 1)
set(NAME PICO_FREERTOS) # <-- Name your project/executable here!
set(ENV{FREERSTOS_KERNEL_PATH}  ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_BOARD pico_w) # Set the board used
# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)
add_subdirectory(pico-cpp)
project(picoKey C CXX ASM)
add_subdirectory(lib)

include(lwip_import.cmake) # lwip config files
SET(FREERTOS_CONFIG_FILE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/configs/FreeRTOS-Kernel" CACHE STRING "Local Config")
include_directories("${FREERTOS_CONFIG_FILE_DIRECTORY}") # FreeRTOS config files

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

# Add pico_stdlib library which aggregates commonly used features
#target_link_libraries(picoKey PUBLIC pico_stdlib pico_stdlib tinyusb_device tinyusb_board)
add_library(FreeRTOS STATIC
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

target_sources(picoKey PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/usb_descriptors.c ${CMAKE_CURRENT_LIST_DIR}/src/msc_disk_dual.c)

# Make sure TinyUSB can find tusb_config.h
include_directories(picoKey PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${FREERSTOS_KERNEL_PATH}/include)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(picoKey)
include(${CMAKE_CURRENT_LIST_DIR}/lib/ws2812Lib/CMakeLists.txt)
target_link_libraries(picoKey PUBLIC hardware_dma pico_stdlib hardware_flash tinyusb_device tinyusb_board pico-cpp hardware_spi hardware_i2c libeeprom liboled libcJson libspistorage)
add_custom_command(TARGET picoKey
        POST_BUILD
        COMMAND arm-none-eabi-size picoKey.elf
        )

pico_enable_stdio_usb(picoKey 1)
include(lib/ws2812Lib/CMakeLists.txt)
linkws2812lib(picoKey ${CMAKE_CURRENT_LIST_DIR}/lib/ws2812Lib)

# Initialize all other external libs & dependencies
include(FreeRTOS_Kernel_import.cmake)
# rest of your project