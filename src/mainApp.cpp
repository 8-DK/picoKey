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
uint8_t MainApp::mUnlockSeq[MAX_COUNT_UNLOCK_SEQ] = {0};
uint8_t MainApp::inUnlkSeq[MAX_COUNT_UNLOCK_SEQ] = {0};
uint8_t MainApp::mListCount = 0;
MAINAPP_STATS MainApp::mainAppState = EM_MAINAPP_INIT;
vector<string> MainApp::userNameList;
vector<string> MainApp::passwordList;
TimerHandle_t MainApp::xTimerKeyTimeout;

int MainApp::currentKeyIndex = 0;
int MainApp::currentSeqInd = 0;

// uint32_t MainApp::startAddress = (uint32_t) (XIP_BASE+ 0x103ff000);
#define FLASH_TARGET_OFFSET (2044 * 1024)
uint8_t * MainApp::startAddress = (uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

MainApp::MainApp()
{
    if(mListCount == 0xFF)
    {
        mListCount = 0;
    }    
}

MainApp::~MainApp()
{

}

void MainApp::storeListInEeprom()
{
    taskENTER_CRITICAL();
    mListCount = 20;
    uint8_t buffer[4096];
    int j = 0;
    buffer[j++] = mListCount;
    for(int i = 0 ; i < MAX_COUNT_UNLOCK_SEQ ; i ++)
        buffer[j++] = mUnlockSeq[i];
    for(int i = 0 ; i < mListCount ; i++)
    {
        char listData[100] = {0};    
        sprintf(listData,"%d,Password",i);
        mPrintf("%s",listData);
        memcpy(buffer+j+(i*100),listData,100);
        delay(100);
    }
    flash_range_erase(FLASH_TARGET_OFFSET, 4096);
    flash_range_program(FLASH_TARGET_OFFSET, buffer, 4096);
    taskEXIT_CRITICAL();
}

void MainApp::readListFromEeprom()
{
    taskENTER_CRITICAL();
    mListCount = 0;    
    uint8_t* ptr;
    int j = 0;

    mListCount = startAddress[j++];
    for(int i = 0 ; i < MAX_COUNT_UNLOCK_SEQ ; i++)
        mUnlockSeq[i] = startAddress[j+i];
    j = j + MAX_COUNT_UNLOCK_SEQ;
    vector<string> m_dispList;
    for(int i = 0 ; i < mListCount ; i++)
    {
        char listData[100] = {0};    
        memcpy(listData,startAddress+j+(i*100),100);
        m_dispList.push_back(listData);
    }
    DisplayHelper::getInstance()->updateList(m_dispList);
    taskEXIT_CRITICAL();
    mPrintf("Old unlock sequence : ");
    for(int i = 0 ; i < MAX_COUNT_UNLOCK_SEQ ; i++)
       mPrintf("%d)[%d]\r\n",i,mUnlockSeq[i]);
    mPrintf("\n");
}

void MainApp::vKeyTimeoutCallback( TimerHandle_t xTimer )
{
    // mPrintf("------------------\n");
    // for(int i=0 ; i < currentKeyIndex ; i++)
    // {       
    //     if(inUnlkSeq & (1 << i))
    //          mPrintf("unlock[%d] - P1\n",i);
    //     else
    //          mPrintf("unlock[%d] - P2\n",i);
    // }    
    // mPrintf("------------------\n");
    // inUnlkSeq = 0;
    // currentKeyIndex = 0;
}

void MainApp::mainApp( void * pvParameters )
{
    delay(3000);
    readListFromEeprom();
    // storeListInEeprom();
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
                                if(currentSeqInd >= MAX_COUNT_UNLOCK_SEQ)     
                                    break;   
                                inUnlkSeq[currentSeqInd++] = 1;
                                mPrintf("Key P1");
                                // xTimerStart( xTimerKeyTimeout, 0 ); //restart timer
                            }
                            else if(mKey == P2)
                            {                                
                                if(currentSeqInd >= MAX_COUNT_UNLOCK_SEQ)     
                                   break;
                                inUnlkSeq[currentSeqInd++] = 2; 
                                mPrintf("Key P2");
                                // xTimerStart( xTimerKeyTimeout, 0 ); //restart timer                     
                            }
                            else if(mKey == P3) //ok key
                            {
                                if(memcmp(&mUnlockSeq,&inUnlkSeq,MAX_COUNT_UNLOCK_SEQ) == 0)
                                {
                                    mPrintf("Device unlocked\n");
                                    mainAppState = EM_MAINAPP_UNLOCKED;
                                }
                                else
                                {
                                    mPrintf("Device locked\n");
                                    mainAppState = EM_MAINAPP_LOCKED;
                                }
                                    mPrintf("unlock sequence : ");
                                    for(int i = 0 ; i < MAX_COUNT_UNLOCK_SEQ ; i++)
                                        mPrintf("%d)[%d]==[%d]\r\n",i,mUnlockSeq[i],inUnlkSeq[i]);
                                    mPrintf("\n");
                                memset(inUnlkSeq,0,MAX_COUNT_UNLOCK_SEQ);
                                currentSeqInd = 0;
                            }
                            else if(mKey == P4) //ok key
                            {
                                memcpy(&mUnlockSeq,&inUnlkSeq,MAX_COUNT_UNLOCK_SEQ);
                                mPrintf("new unlock sequence %x\n",mUnlockSeq);
                                storeListInEeprom();
                                memset(inUnlkSeq,0,MAX_COUNT_UNLOCK_SEQ);
                                currentSeqInd = 0;
                            }
                            else if(mKey == P5) //ok key
                            {
                                readListFromEeprom();
                                DisplayHelper::displaySetState(EM_DISP_LIST);
                            }
                        }
                    }
                    // mainAppState = EM_MAINAPP_WLCM;
                    break; 
                    
                    case EM_MAINAPP_WLCM:
                        DisplayHelper::displaySetState(EM_DISP_WLCM);
                        delay(2000);
                        if(mUnlockSeq == 0)
                        {
                            DisplayHelper::displaySetState(EM_DISP_NEWLOCKSCR);
                            mainAppState = EM_MAINAPP_IDEAL;
                        }
                        else
                            mainAppState = EM_MAINAPP_LOCKED;
                    break; 
                    
                    case EM_MAINAPP_FIRSTTIME:
                    break; 
                    
                    case EM_MAINAPP_LOCKED:
                        DisplayHelper::displaySetState(EM_DISP_LOCKSCR);
                        mainAppState = EM_MAINAPP_IDEAL;
                    break; 
                    
                    case EM_MAINAPP_UNLOCKED:
                        DisplayHelper::displaySetState(EM_DISP_UNLOCKSCR);
                        delay(2000);
                        readListFromEeprom();                        
                        DisplayHelper::displaySetState(EM_DISP_LIST);
                        mainAppState = EM_MAINAPP_IDEAL;
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
