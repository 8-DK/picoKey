/*
 * File: keyHelper.cpp
 * Project: picoKey
 * File Created: Tuesday, 11th January 2022 11:10:03 pm
 * Author: Dhananjay Khairnar (khairnardm@gmail.com)
 * -----
 * Last Modified: Wednesday, 12th January 2022 12:07:53 am
 * Modified By: 8-DK (khairnardm@gmail.com>)
 * -----
 * Copyright 2021 - 2022 https://github.com/8-DK
 */

#include "keyHelper.h"

//Singletone

KeyHelper *KeyHelper::instance = 0;

int KeyHelper::pinNums[TOTAL_KEY_COUNT] = {KEY_1_PIN,KEY_2_PIN,KEY_3_PIN,KEY_4_PIN,KEY_5_PIN,KEY_6_PIN};
pico_cpp::GPIO_Pin *KeyHelper::m_keys[TOTAL_KEY_COUNT];

KeyHelper::KeyHelper()
{ 
}

bool KeyHelper::readKeyPress(int keyNum)
{   
    return  m_keys[keyNum]->get();
}

void KeyHelper::initKey()
{
    for(int i=0 ; i<TOTAL_KEY_COUNT ;i++)
    {
        m_keys[i] = new pico_cpp::GPIO_Pin(pinNums[i],pico_cpp::PinType::Input);
    }  
}

void KeyHelper::keyTask( void * pvParameters )
{
    initKey();
    while(1)
    {
         vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}