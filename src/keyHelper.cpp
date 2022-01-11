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

KeyHelper::KeyHelper()
{
    for(int i=0 ; i<TOTAL_KEY_COUNT ;i++)
    {
        m_keys[i] = new pico_cpp::GPIO_Pin(pinNums[i],pico_cpp::PinType::Input);
    }    
}

bool KeyHelper::readKeyPress(int keyNum)
{   
    return  m_keys[keyNum]->get();
}
