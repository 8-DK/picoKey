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

#endif