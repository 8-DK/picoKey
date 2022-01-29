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
#include "displayHelper.h"
#include "hardware/flash.h"
#include "usbHelper.h"

MainApp *MainApp::instance = nullptr;
uint8_t MainApp::mUnlockSeq = 0;
uint8_t MainApp::mListCount = 0;
MAINAPP_STATS MainApp::mainAppState = EM_MAINAPP_INIT;
vector<string> MainApp::userNameList;
vector<string> MainApp::passwordList;

// uint32_t MainApp::startAddress = (uint32_t) (XIP_BASE+ 0x103ff000);
#define FLASH_TARGET_OFFSET (1792 * 1024)
uint8_t * MainApp::startAddress = (uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

MainApp::MainApp()
{
    if( (mUnlockSeq == 0xFF) || (mListCount == 0xFF))
    {
        mUnlockSeq =  0;
        mListCount = 0;
    }
    // storeListInEeprom();
    // readListFromEeprom();
}

MainApp::~MainApp()
{

}

void MainApp::storeListInEeprom()
{
    mListCount = 20;
    uint8_t buffer[FLASH_SECTOR_SIZE] = {0};
    int j = 0;
    buffer[j++] = mListCount;
    buffer[j++] = mUnlockSeq;
    for(int i = 0 ; i < mListCount ; i++)
    {
        char listData[100] = {0};    
        sprintf(listData,"E%d,Password%d",i);
        for(int m = 0 ; m < 100 ; m ++)
            buffer[j++] = listData[m];
    }
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(FLASH_TARGET_OFFSET, buffer, FLASH_SECTOR_SIZE);
}

void MainApp::readListFromEeprom()
{
    mListCount = 0;
    mUnlockSeq = 0;
    uint8_t* ptr;
    int j = 0;

    mListCount = startAddress[j++];
    mUnlockSeq = startAddress[j++];
    vector<string> m_dispList;
    for(int i = 0 ; i < mListCount ; i++)
    {
        char listData[100] = {0};    
        memcpy(listData,startAddress+j+(i*100),100);
        m_dispList.push_back(listData);
    }
    DisplayHelper::getInstance()->updateList(m_dispList);
}


void MainApp::mainApp( void * pvParameters )
{
    while (1)
    {                     
        const EventBits_t xBitsToWaitFor  = (KEY_TASK_KEY_PRESS_EVENT);
        EventBits_t xEventGroupValue;
        while(1)
        {
            switch(mainAppState)
            {
                    case EM_MAINAPP_INIT:
                    DisplayHelper::displaySetState(EM_DISP_INIT);
                    mainAppState = EM_MAINAPP_WLCM;
                    break; 

                    case EM_MAINAPP_IDEAL:
                    {
                        xEventGroupValue  = xEventGroupWaitBits(xEventGroup,
                                    xBitsToWaitFor,
                                    pdTRUE,
                                    pdTRUE,
                                    100
                                    );
                        if((xEventGroupValue & KEY_TASK_KEY_PRESS_EVENT) !=0)
                        {                
                            readListFromEeprom();
                            mPrintf("mainAppState---Key event\r\n");
                            DisplayHelper::displaySetState(EM_DISP_LIST);
                        }
                    }
                    // mainAppState = EM_MAINAPP_WLCM;
                    break; 
                    
                    case EM_MAINAPP_WLCM:
                    DisplayHelper::displaySetState(EM_DISP_WLCM);
                    delay(2000);
                    DisplayHelper::displaySetState(EM_DISP_LOCKSCR);
                    mainAppState = EM_MAINAPP_IDEAL;
                    break; 
                    
                    case EM_MAINAPP_FIRSTTIME:
                    break; 
                    
                    case EM_MAINAPP_LOCKED:
                    break; 
                    
                    case EM_MAINAPP_UNLOCKED:
                    break; 
                    
                    case EM_MAINAPP_SELECT:
                    break; 
                    
                    case EM_MAINAPP_SEND_USERNAEM:
                    break; 
                    
                    case EM_MAINAPP_SEND_PASS:
                    break;                     
            }
        }
    }
    
}