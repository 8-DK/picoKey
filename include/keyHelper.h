/*
 * File: keyHelper.h
 * Project: picoKey
 * File Created: Tuesday, 11th January 2022 11:09:54 pm
 * Author: Dhananjay Khairnar (khairnardm@gmail.com)
 * -----
 * Last Modified: Wednesday, 12th January 2022 12:08:24 am
 * Modified By: 8-DK (khairnardm@gmail.com>)
 * -----
 * Copyright 2021 - 2022 https://github.com/8-DK
 */

#ifndef __KEYHELPER__
#define __KEYHELPER__

#include "common.h"

#define KEY_PORT 0
#define KEY_1_PIN 16
#define KEY_2_PIN 17
#define KEY_3_PIN 18
#define KEY_4_PIN 19
#define KEY_5_PIN 20
#define KEY_6_PIN 21

#define TOTAL_KEY_COUNT 6

class KeyHelper{
    
    static KeyHelper *instance;
public: 
    static auto *getInstance() {
        if (!instance)
            instance = new KeyHelper;
        return instance;
    }

    static int pinNums[TOTAL_KEY_COUNT];
    static pico_cpp::GPIO_Pin *m_keys[TOTAL_KEY_COUNT];

    KeyHelper();
    bool readKeyPress(int keyNum);
    static void initKey();
    static void keyTask( void * pvParameters );
    
};

#endif