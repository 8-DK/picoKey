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
#include "usbHelper.h"
//Singletone

KeyHelper *KeyHelper::instance = 0;
KEY_ID     KeyHelper::lastKeyPressed = KEY_INVALID;
int        KeyHelper::pinNums[TOTAL_KEY_COUNT] = {KEY_1_PIN,KEY_2_PIN,KEY_3_PIN,KEY_4_PIN,KEY_5_PIN,KEY_6_PIN};
int        KeyHelper::keyPressed[TOTAL_KEY_COUNT] = {RELEASED};

void disableIRQ(uint8_t keyId,uint32_t events){gpio_set_irq_enabled( KeyHelper::pinNums[keyId],events,false);}
void enableIRQ(uint8_t keyId,uint32_t events){gpio_set_irq_enabled( KeyHelper::pinNums[keyId],events,true);}

void gpio_callback(uint gpio, uint32_t events) {
    // Put the GPIO event(s) that just happened into event_str
    // so we can print it
    // mPrintf("Button press %d,%d\r\n",gpio,events);
    if(events == GPIO_IRQ_EDGE_RISE)
    {
        if (gpio == KeyHelper::pinNums[P1]) //detect only rising edge
        {
            KeyHelper::lastKeyPressed = P1;
            KeyHelper::keyPressed[P1] = PRESSED;
            disableIRQ(P1,events);
        } 
        else if(gpio == KeyHelper::pinNums[P2])
        {
            KeyHelper::lastKeyPressed = P2;
            KeyHelper::keyPressed[P2] = PRESSED;
            disableIRQ(P2,events);
        }   
        else if(gpio == KeyHelper::pinNums[P3])
        {
            KeyHelper::lastKeyPressed = P3;
            KeyHelper::keyPressed[P3] = PRESSED;
            disableIRQ(P3,events);
        }   
        else if(gpio == KeyHelper::pinNums[P4])
        {
            KeyHelper::lastKeyPressed = P4;
            KeyHelper::keyPressed[P4] = PRESSED;
            disableIRQ(P4,events);
        }   
        else if(gpio == KeyHelper::pinNums[P5])
        {
            KeyHelper::lastKeyPressed = P5;
            KeyHelper::keyPressed[P5] = PRESSED;
            disableIRQ(P5,events);
        }   
        else if(gpio == KeyHelper::pinNums[P6])
        {
            KeyHelper::lastKeyPressed = P6;
            KeyHelper::keyPressed[P6] = PRESSED;
            disableIRQ(P6,events);
        }   
    }
}


KeyHelper::KeyHelper()
{ 
}

bool KeyHelper::readKeyPress(int keyId)
{   
    return keyPressed[keyId];
}

void KeyHelper::initKey()
{
    for(int i=0 ; i<TOTAL_KEY_COUNT ;i++)
    {        
        gpio_set_input_enabled(pinNums[i],true);
        gpio_set_pulls(pinNums[i],true,false);
        gpio_put(pinNums[i],true);
        gpio_set_irq_enabled_with_callback(pinNums[i], GPIO_IRQ_EDGE_RISE , true, &gpio_callback);
    }  
}

void KeyHelper::keyTask( void * pvParameters )
{
    initKey();
    int m = 0;
    while(1)
    {                 
        if(lastKeyPressed != KEY_INVALID)
        {
            xEventGroupSetBits(xEventGroup, KEY_TASK_KEY_PRESS_EVENT);
            //debounce delay
             vTaskDelay(10 / portTICK_PERIOD_MS);             
            //proocess key press
            for(int i = 0 ; i < TOTAL_KEY_COUNT ;i++)
            {
                mPrintf("Key status[%d] %d\r\n",i,keyPressed[i]);               
            }                        

            for(int i = 0 ; i < TOTAL_KEY_COUNT ;i++)
            {
                 gpio_set_irq_enabled_with_callback(pinNums[i], GPIO_IRQ_EDGE_RISE , true, &gpio_callback);
                keyPressed[i] = RELEASED;
            }
            lastKeyPressed = KEY_INVALID;
        }
        mPrintf("Keymon %d\r\n",m++);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}