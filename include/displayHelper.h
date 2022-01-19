/*
 * File: displayHelper.h
 * Project: picoKey
 * File Created: Wednesday, 12th January 2022 10:36:10 pm
 * Author: Dhananjay Khairnar (khairnardm@gmail.com)
 * -----
 * Last Modified: Wednesday, 12th January 2022 10:36:13 pm
 * Modified By: 8-DK (khairnardm@gmail.com>)
 * -----
 * Copyright 2021 - 2022 https://github.com/8-DK
 */

#ifndef __DISPLAYHLPR__
#define __DISPLAYHLPR__
#include "common.h"
#include "ss_oled.hpp"


/* Example code to talk to an SSD1306-based OLED display

   NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Pico
   GPIO (and therefore I2C) cannot be used at 5v.

   You will need to use a level shifter on the I2C lines if you want to run the
   board at 5v.

   Connections on Raspberry Pi Pico board, other boards may vary.

   GPIO PICO_DEFAULT_I2C_SDA_PIN (on Pico this is GP4 (pin 6)) -> SDA on display
   board
   GPIO PICO_DEFAULT_I2C_SCK_PIN (on Pico this is GP5 (pin 7)) -> SCL on
   display board
   3.3v (pin 36) -> VCC on display board
   GND (pin 38)  -> GND on display board
*/
// RPI Pico
#define SDA_PIN 4
#define SCL_PIN 5
#define PICO_I2C i2c0
#define I2C_SPEED 100 * 1000


#define OLED_WIDTH 128
#define OLED_HEIGHT 64

class DisplayHelper{

    static uint8_t raspberry26x32[];

    static DisplayHelper *instance;
    static picoSSOLED myOled;    
    static uint8_t ucBuffer[1024];
    static vector<string> dispList;
public: 
    static auto *getInstance() {
        if (!instance)
            instance = new DisplayHelper;
        return instance;
    }

    DisplayHelper();
    static void displayTask( void * pvParameters );
    static void displayLoop();    
    static void scrnWithLockMsg(string message);
    static void showlist(string message);
};

#endif
