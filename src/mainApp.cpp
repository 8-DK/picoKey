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
#include "keyHelper.h"

MainApp *MainApp::instance = nullptr;
uint8_t MainApp::mUnlockSeq = 0;
uint8_t MainApp::mListCount = 0;
MAINAPP_STATS MainApp::mainAppState = EM_MAINAPP_INIT;
vector<string> MainApp::userNameList;
vector<string> MainApp::passwordList;
TimerHandle_t MainApp::xTimerKeyTimeout;

uint32_t MainApp::inUnlkSeq = 0;
int MainApp::currentKeyIndex = 0;

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

void MainApp::vKeyTimeoutCallback( TimerHandle_t xTimer )
{
    mPrintf("------------------\n");
    for(int i=0 ; i < currentKeyIndex ; i++)
    {       
        if(inUnlkSeq & (1 << i))
             mPrintf("unlock[%d] - P1\n",i);
        else
             mPrintf("unlock[%d] - P2\n",i);
    }    
    mPrintf("------------------\n");
    inUnlkSeq = 0;
    currentKeyIndex = 0;
}

void MainApp::mainApp( void * pvParameters )
{
    readListFromEeprom();
    xTimerKeyTimeout = xTimerCreate
                   ("KeyTimer",
                     toMs(2000),
                     pdFALSE,
                     ( void * ) 0,
                     vKeyTimeoutCallback
                   );
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
                        {                                                                                                    
                            KEY_ID mKey= KeyHelper::readKeyPress();
                            if(mKey == P1)
                            {
                                mPrintf("mainAppState---Key P1\n");
                                inUnlkSeq = inUnlkSeq | (1 << currentKeyIndex++);
                                xTimerStart( xTimerKeyTimeout, 0 ); //restart timer
                            }
                            else if(mKey == P2)
                            {
                                mPrintf("mainAppState---Key P2\n");
                                inUnlkSeq = inUnlkSeq | (0 << currentKeyIndex++);       
                                xTimerStart( xTimerKeyTimeout, 0 ); //restart timer                     
                            }                                                        
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
            delay(1);
        }
    }
    
}