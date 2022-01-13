/*
 * File: mainApp.cpp
 * Project: picoKey
 * File Created: Thursday, 13th January 2022 12:17:57 am
 * Author: Dhananjay Khairnar (khairnardm@gmail.com)
 * -----
 * Last Modified: Thursday, 13th January 2022 9:13:58 pm
 * Modified By: 8-DK (khairnardm@gmail.com>)
 * -----
 * Copyright 2021 - 2022 https://github.com/8-DK
 */

#include "mainApp.h"
#include "EEPROM.h"

MainApp *MainApp::instance = nullptr;

MainApp::MainApp()
{
}

MainApp::~MainApp()
{
}


void MainApp::mainApp( void * pvParameters )
{
    while (1)
    {
       vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
}