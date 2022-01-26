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

//Boards include 
#include "GPIO.hpp"
#include "bsp/board.h"

//Display includes 
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

//Utils
#include "utils.h"

//flash
#include "pico/stdlib.h"
#include "hardware/flash.h"


//Display enums
typedef enum DISP_STATS{
    EM_INIT,
    EM_SHOW_WLCM,
    EM_SHOW_LOCKSCR,
    EM_SHOW_FAILED,
    EM_SHOW_SUCCESS,
    EM_SHO_TYPE_USER,
    EM_SHOW_TYPE_PASS,
    EM_SHOW_LIST,    
}DISP_STATS;


#endif