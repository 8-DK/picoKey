#ifndef __COMMON__
#define __COMMON__

//standar includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//cpp includes
#include <array>
#include <string>
#include <vector>
using namespace std;

//USB includes
#include <iostream>
#include "tusb.h"

//FreeRTOS include
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

//Boards include 
#include "GPIO.hpp"
#include "bsp/board.h"

//Display includes 
#include "pico/binary_info.h"
#include "hardware/i2c.h"

//Utils
#include "utils.h"

//flash
#include "hardware/flash.h"

//GPIO
#include "hardware/gpio.h"


//Display enums
typedef enum DISP_STATS{
    EM_DISP_INIT,
    EM_DISP_IDEAL,
    EM_DISP_WLCM,
    EM_DISP_LOCKSCR,
    EM_DISP_UNLOCKSCR,
    EM_DISP_FAILED,
    EM_DISP_SUCCESS,
    EM_DISP_TYPE_USER,
    EM_DISP_TYPE_PASS,
    EM_DISP_LIST,    
}DISP_STATS;

//MainApp enums
typedef enum MAINAPP_STATS{
    EM_MAINAPP_INIT,
    EM_MAINAPP_IDEAL,
    EM_MAINAPP_WLCM,
    EM_MAINAPP_FIRSTTIME,
    EM_MAINAPP_LOCKED,
    EM_MAINAPP_UNLOCKED,
    EM_MAINAPP_SELECT,
    EM_MAINAPP_SEND_USERNAEM,
    EM_MAINAPP_SEND_PASS,
}MAINAPP_STATS;

//task globals
#define KEY_TASK_KEY_PRESS_EVENT   (1UL << 0UL) // zero shift for bit0
extern EventGroupHandle_t  xEventGroup;

#endif