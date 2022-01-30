/*
 * File: displayHelper.cpp
 * Project: picoKey
 * File Created: Wednesday, 12th January 2022 10:36:21 pm
 * Author: Dhananjay Khairnar (khairnardm@gmail.com)
 * -----
 * Last Modified: Wednesday, 12th January 2022 10:36:37 pm
 * Modified By: 8-DK (khairnardm@gmail.com>)
 * -----
 * Copyright 2021 - 2022 https://github.com/8-DK
 */

#include "displayHelper.h"
#include "pico/stdlib.h"
#include "images.h"

DisplayHelper *DisplayHelper::instance = nullptr;
vector<string> DisplayHelper::dispList;
uint8_t DisplayHelper::ucBuffer[1024] = {0};
picoSSOLED DisplayHelper::myOled(OLED_128x64, 0x3c, 0, 0, PICO_I2C, SDA_PIN, SCL_PIN, I2C_SPEED);
uint8_t DisplayHelper::raspberry26x32[] = {0x0, 0x0, 0xe, 0x7e, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7e, 0x1e, 0x0, 0x0, 0x0, 0x80, 0xe0, 0xf8, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xf8, 0xe0, 0x80, 0x0, 0x0, 0x1e, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1e, 0x0, 0x0, 0x0, 0x3, 0x7, 0xf, 0x1f, 0x1f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f, 0xf, 0x7, 0x3, 0x0, 0x0};
int DisplayHelper::curretScrollerIndex = 0;
int DisplayHelper::totalListCount = 0;
DISP_STATS DisplayHelper::dispState =  EM_DISP_IDEAL;

DisplayHelper::DisplayHelper()
{
}

void DisplayHelper::displayTask(void *pvParameters)
{
    for(;;)
    {
        displayLoop();
    }
}
void DisplayHelper::scrnWithLockMsg(string message)
{
    myOled.fill(0, 1);
    while(1)
    {
        myOled.fill(0, 0);
        myOled.draw_rectangle(0,0,127,63,1,0);
        myOled.draw_rectangle(1,1,126,62,1,0);
        myOled.dump_buffer(ucBuffer);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        myOled.write_string(0, 5, 2, (char *)"Please set new", FONT_8x8, 0, 0);
        myOled.write_string(0, 3, 3, (char *)"Unlock sequence", FONT_8x8, 0, 0);
        myOled.dump_buffer(ucBuffer);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void DisplayHelper::showlist(string message)
{
    dispList.push_back("1facebook");
    dispList.push_back("2Gmail");
    dispList.push_back("3Twiter1");
    dispList.push_back("4Twit2");
    dispList.push_back("5Twir3");
    dispList.push_back("6Twite4");
    dispList.push_back("7Twi5");
    dispList.push_back("8Twit6");
    dispList.push_back("9facebook");
    dispList.push_back("10Gmail");
    dispList.push_back("11Twiter1");
    dispList.push_back("12Twit2");

    int listDispCount  = 4;
    int scrollerPosn = 0;  
    int minScrollerH = 4;     
    
    int scrollerH = 0;
    int scrollerPosition = 0;
    int curretScrollerIndex = 0;
    int totalListCount = 0;


    myOled.fill(0, 1);

    int mstart = 0;
    int m = 1;
    while(1)
    {
        totalListCount = (int)dispList.size(); 

        if((totalListCount!=0) && (listDispCount!=0))
        {
            scrollerH = (int) (totalListCount/listDispCount); //eg total = 20 , disp cnt = 4,  scroller height = 20/4 = 5px
            scrollerH = (int)63/scrollerH;
            if(scrollerH < 4 )
                scrollerH = 4;
            else if(scrollerH > 63)
                scrollerH = 63;
        }
        if((mstart+4) < dispList.size())
        {
            // for (int i = mstart ; i < (mstart+3) ; i++)
            {
                curretScrollerIndex =  mstart;
                if((curretScrollerIndex!=0) && (totalListCount!=0))
                    scrollerPosition =(int)((curretScrollerIndex*100)/totalListCount);

                scrollerPosition = Utils.mapInt(scrollerPosition,0,100,0,63);

                //trim scroller goin out display
                if((scrollerPosition+scrollerH) > 63)
                {
                    scrollerH = 63-scrollerPosition;
                }

                myOled.fill(0, 0);
                char buff[100];
                sprintf(buff,"sp%d",scrollerPosition);
                // myOled.write_string(0, 0, 0, buff, FONT_12x16, 0, 0);
                myOled.write_string(0, 12, 0, (char *)dispList.at(mstart).c_str(), FONT_12x16, 0, 0);
                myOled.write_string(0, 12, 2, (char *)dispList.at(mstart+1).c_str(), FONT_12x16, 0, 0);
                myOled.write_string(0, 12, 4, (char *)dispList.at(mstart+2).c_str(),  FONT_12x16, 0, 0);
                myOled.write_string(0, 12, 6, (char *)dispList.at(mstart+3).c_str(),  FONT_12x16, 0, 0);
                
                myOled.draw_rectangle(118,scrollerPosition,127,scrollerPosition+scrollerH,1,0);
                myOled.draw_rectangle(121,0,121,63,1,0);

                myOled.write_string(0, 0, 0, (char *)" ", FONT_12x16, 0, 0);
                myOled.write_string(0, 0, 2, (char *)" ", FONT_12x16, 0, 0);
                myOled.write_string(0, 0, 4, (char *)" ",  FONT_12x16, 0, 0);
                myOled.write_string(0, 0, 6, (char *)" ",  FONT_12x16, 0, 0);

                myOled.write_string(0, 0, (curretScrollerIndex%4)*2, (char *)">",  FONT_12x16, 0, 0);
                
                myOled.dump_buffer(ucBuffer);
            }
        }
        else
        {
                curretScrollerIndex ++;
                myOled.write_string(0, 0, 0, (char *)" ", FONT_12x16, 0, 0);
                myOled.write_string(0, 0, 2, (char *)" ", FONT_12x16, 0, 0);
                myOled.write_string(0, 0, 4, (char *)" ",  FONT_12x16, 0, 0);
                myOled.write_string(0, 0, 6, (char *)" ",  FONT_12x16, 0, 0);

                myOled.write_string(0, 0, (curretScrollerIndex%4)*2, (char *)">",  FONT_12x16, 0, 0);
                
                myOled.dump_buffer(ucBuffer);
        }
        
        mstart = m + mstart;
        if(((mstart+4) > dispList.size()) && (curretScrollerIndex>=4))
        {
            m = -1;
            mstart = m+mstart;
        }
        else if(mstart < 0)
        {
            m = 1;            
            mstart = 0;
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }        
}

void DisplayHelper::updateList(vector<string> m_dispList)
{
    dispList.clear();
    dispList = m_dispList;
    totalListCount = (int)dispList.size();  
}

void DisplayHelper::showlist1(vector<string> m_dispList)
{    
    dispList = m_dispList;
    int listDispCount  = 4;
    int scrollerPosn = 0;  
    int minScrollerH = 4;
    
    int scrollerH = 0;
    int scrollerPosition = 0;
    
    int pageStart = 0;
    // while(1)
    {
        totalListCount = (int)dispList.size(); 
        if(totalListCount <= 0) 
            return;
        myOled.fill(0, 0);
        float divn = (float)curretScrollerIndex/(float)listDispCount; 
        pageStart = (int)divn*listDispCount;   
     
        if((curretScrollerIndex!=0) && (totalListCount!=0))
            scrollerPosition =(int)((curretScrollerIndex*100)/totalListCount);

        scrollerPosition = Utils.mapInt(scrollerPosition,0,100,0,63);

        //trim scroller goin out display
        if((scrollerPosition+scrollerH) > 63)
        {
            scrollerH = 63-scrollerPosition;
        }
        else
        {
            scrollerH = (int) (totalListCount/listDispCount); //eg total = 20 , disp cnt = 4,  scroller height = 20/4 = 5px
            scrollerH = (int)63/scrollerH;
            if(scrollerH < 4 )
                scrollerH = 4;
            else if(scrollerH > 63)
                scrollerH = 63; 
        }
        if(totalListCount > pageStart)
            myOled.write_string(0, 12, 0, (char *)dispList.at(pageStart).c_str(), FONT_12x16, 0, 0);
        if(totalListCount > pageStart+1)
            myOled.write_string(0, 12, 2, (char *)dispList.at(pageStart+1).c_str(), FONT_12x16, 0, 0);
        if(totalListCount > pageStart+2)
            myOled.write_string(0, 12, 4, (char *)dispList.at(pageStart+2).c_str(),  FONT_12x16, 0, 0);
        if(totalListCount > pageStart+3)
            myOled.write_string(0, 12, 6, (char *)dispList.at(pageStart+3).c_str(),  FONT_12x16, 0, 0);

        myOled.draw_rectangle(118,scrollerPosition,127,scrollerPosition+scrollerH,1,0);
        myOled.draw_rectangle(123,0,123,63,1,0);

        myOled.write_string(0, 0, 0, (char *)" ", FONT_12x16, 0, 0);
        myOled.write_string(0, 0, 2, (char *)" ", FONT_12x16, 0, 0);
        myOled.write_string(0, 0, 4, (char *)" ",  FONT_12x16, 0, 0);
        myOled.write_string(0, 0, 6, (char *)" ",  FONT_12x16, 0, 0);

        myOled.write_string(0, 0, (curretScrollerIndex%4)*2, (char *)">",  FONT_12x16, 0, 0);
        
        myOled.dump_buffer(ucBuffer);

        curretScrollerIndex++;

        curretScrollerIndex = (curretScrollerIndex%totalListCount);

        // vTaskDelay(2000 / portTICK_PERIOD_MS);
    }        
}

void DisplayHelper::displaySetState(DISP_STATS mDispState)
{
    dispState = mDispState;
}

void DisplayHelper::displayLoop()
{
    uint8_t uc[8];
    int i, j, rc;   

    rc = myOled.init();
    myOled.set_back_buffer(ucBuffer);

    while (1)
    {
        // if (rc != OLED_NOT_FOUND)
        // {
        //     myOled.fill(0, 1);
        //     myOled.set_contrast(127);
        //     myOled.write_string(0, 0, 0, (char *)"**************** ", FONT_8x8, 0, 1);
        //     myOled.write_string(0, 4, 1, (char *)"Pi Pico SS_OLED", FONT_8x8, 0, 1);
        //     myOled.write_string(0, 8, 2, (char *)"running on the", FONT_8x8, 0, 1);
        //     myOled.write_string(0, 8, 3, (char *)"SSD1306 128x64", FONT_8x8, 0, 1);
        //     myOled.write_string(0, 4, 4, (char *)"monochrome OLED", FONT_8x8, 0, 1);
        //     myOled.write_string(0, 0, 5, (char *)"Written by L BANK", FONT_8x8, 0, 1);
        //     myOled.write_string(0, 4, 6, (char *)"Pico by M KOOIJ", FONT_8x8, 0, 1);
        //     myOled.write_string(0, 0, 7, (char *)"**************** ", FONT_8x8, 0, 1);
        //     vTaskDelay(1000 / portTICK_PERIOD_MS);
        // }

        // myOled.fill(0, 1);
        // myOled.write_string(0, 0, 0, (char *)"Now with 5 font sizes", FONT_6x8, 0, 1);
        // myOled.write_string(0, 0, 1, (char *)"6x8 8x8 16x16", FONT_8x8, 0, 1);
        // myOled.write_string(0, 0, 2, (char *)"16x32 and a new", FONT_8x8, 0, 1);
        // myOled.write_string(0, 0, 3, (char *)"Stretched", FONT_12x16, 0, 1);
        // myOled.write_string(0, 0, 5, (char *)"from 6x8", FONT_12x16, 0, 1);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);

        // int x, y;
        // myOled.fill(0, 1);
        // myOled.write_string(0, 0, 0, (char *)"Backbuffer Test", FONT_NORMAL, 0, 1);
        // myOled.write_string(0, 0, 1, (char *)"96 lines", FONT_NORMAL, 0, 1);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        // for (x = 0; x < OLED_WIDTH - 1; x += 2)
        // {
        //     myOled.draw_line(x, 0, OLED_WIDTH - x, OLED_HEIGHT - 1, 1);
        // };
        // for (y = 0; y < OLED_HEIGHT - 1; y += 2)
        // {
        //     myOled.draw_line(OLED_WIDTH - 1, y, 0, OLED_HEIGHT - 1 - y, 1);
        // };
        // myOled.write_string(0, 0, 1, (char *)"Without backbuffer", FONT_SMALL, 0, 1);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        // myOled.fill(0, 1);
        // for (x = 0; x < OLED_WIDTH - 1; x += 2)
        // {
        //     myOled.draw_line(x, 0, OLED_WIDTH - 1 - x, OLED_HEIGHT - 1, 0);
        // }
        // for (y = 0; y < OLED_HEIGHT - 1; y += 2)
        // {
        //     myOled.draw_line(OLED_WIDTH - 1, y, 0, OLED_HEIGHT - 1 - y, 0);
        // }
        // myOled.dump_buffer(ucBuffer);
        // myOled.write_string(0, 0, 1, (char *)"With backbuffer", FONT_SMALL, 0, 1);
         myOled.fill(0, 1);
        
        while (1)
        {       
            switch(dispState)
            {
                case EM_DISP_INIT:
                dispState = EM_DISP_IDEAL;
                break;
                
                case EM_DISP_IDEAL:
                break;

                case EM_DISP_WLCM:
                myOled.load_bmp((uint8_t*)&dkLog,true,0);
                myOled.dump_buffer(ucBuffer);
                dispState = EM_DISP_IDEAL;
                break;

                case EM_DISP_NEWLOCKSCR:
                myOled.load_bmp((uint8_t*)&screen1,true,0);
                myOled.dump_buffer(ucBuffer);
                break;

                case EM_DISP_LOCKSCR:
                myOled.load_bmp((uint8_t*)&screen3,true,0);
                myOled.dump_buffer(ucBuffer);
                dispState = EM_DISP_IDEAL;
                break;

                case EM_DISP_UNLOCKSCR:
                myOled.load_bmp((uint8_t*)&screen2,true,0);
                myOled.dump_buffer(ucBuffer);                
                dispState = EM_DISP_IDEAL;
                break;

                case EM_DISP_FAILED:
                myOled.load_bmp((uint8_t*)&screen3,true,0);
                myOled.dump_buffer(ucBuffer);                
                dispState = EM_DISP_IDEAL;
                break;

                case EM_DISP_SUCCESS:
                myOled.load_bmp((uint8_t*)&screen4,true,0);
                myOled.dump_buffer(ucBuffer);
                dispState = EM_DISP_IDEAL;
                break;

                case EM_DISP_TYPE_USER:
                myOled.load_bmp((uint8_t*)&screen5,true,0);
                myOled.dump_buffer(ucBuffer);
                dispState = EM_DISP_IDEAL;
                break;

                case EM_DISP_TYPE_PASS:
                dispState = EM_DISP_IDEAL;
                break;

                case EM_DISP_LIST:
                showlist1(dispList);
                delay(2000);
                dispState = EM_DISP_IDEAL;
                break;
            }
            delay(10);
        }
    }
}
