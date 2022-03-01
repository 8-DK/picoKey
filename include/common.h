/*
 * File: common.h
 * Project: picoKey
 * File Created: Wednesday, 12th January 2022 11:17:09 pm
 * Author: Dhananjay Khairnar (khairnardm@gmail.com)
 * -----
 * Last Modified: Thursday, 10th February 2022 12:02:22 am
 * Modified By: Dhananjay-Khairnar (khairnardm@gmail.com>)
 * -----
 * Copyright 2021 - 2022 https://github.com/8-DK
 */

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
#include "timers.h"

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
    EM_DISP_NEWLOCKSCR,
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
    EM_MAINAPP_SEND_USERNAME,
    EM_MAINAPP_SEND_PASS,
}MAINAPP_STATS;


typedef enum COMMAND_CH{
    EM_GET_DATA_LIST = 'A',    
    EM_SET_DATA_LIST,
    EM_GET_DATA_AT_INDEX,
    EM_SET_DATA_AT_INDEX,
    EM_ADD_NEW_ENTRY,
    EM_DELETE_ENTRY_AT,
    EM_DELETE_ALL_ENTRY,
    EM_ERASE_DEVICE,
    EM_LOGOUT,
    EM_REMOUNT,
    EM_PLAY_ANIMATION,    
    EM_COMMAND_CH_MAX
}COMMAND_CH;


typedef struct command_t
{
    const char *command;    
    const char *data;    
    const uint32_t currentItem;
    const uint32_t totalItem;    
}command_t;


//task globals
#define KEY_TASK_KEY_PRESS_EVENT   (1UL << 0UL) // zero shift for bit0

#endif