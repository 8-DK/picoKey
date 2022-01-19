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
uint8_t MainApp::mUnlockSeq = 0;
uint8_t MainApp::mListCount = 0;
vector<string> MainApp::userNameList;
vector<string> MainApp::passwordList;

MainApp::MainApp()
{
    EEPROM.begin(4096);
    mUnlockSeq = EEPROM.read(EAddress);
    mListCount = EEPROM.read(ListCountAddr);
    if( (mUnlockSeq == 0xFF) || (mListCount == 0xFF))
    {
        mUnlockSeq =  0;
        mListCount = 0;
    }
}

MainApp::~MainApp()
{

}

void MainApp::storeListInEeprom()
{

}

void MainApp::readListFromEeprom()
{
    for(int i = 0 ; i < mListCount;i++)
    {
        char listData[100] = {0};
        EEPROM.get(ListDataAddr+i,listData);
        char* ptr = strtok(listData, " , ");
        userNameList.push_back(string(ptr));
        userNameList.push_back(string(strtok (NULL, " , ")));
    }
}


void MainApp::mainApp( void * pvParameters )
{
    while (1)
    {
       vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
}