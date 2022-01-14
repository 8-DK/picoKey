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
#include "ss_oled.hpp"

DisplayHelper *DisplayHelper::instance = nullptr;

uint8_t DisplayHelper::raspberry26x32[] = {0x0, 0x0, 0xe, 0x7e, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7e, 0x1e, 0x0, 0x0, 0x0, 0x80, 0xe0, 0xf8, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xf8, 0xe0, 0x80, 0x0, 0x0, 0x1e, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1e, 0x0, 0x0, 0x0, 0x3, 0x7, 0xf, 0x1f, 0x1f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f, 0xf, 0x7, 0x3, 0x0, 0x0};

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

void DisplayHelper::displayLoop()
{

    static uint8_t ucBuffer[1024];
    uint8_t uc[8];
    int i, j, rc;
    char szTemp[32];
    picoSSOLED myOled(OLED_128x64, 0x3c, 0, 0, PICO_I2C, SDA_PIN, SCL_PIN, I2C_SPEED);

    rc = myOled.init();
    myOled.set_back_buffer(ucBuffer);

    while (1)
    {
        if (rc != OLED_NOT_FOUND)
        {
            myOled.fill(0, 1);
            myOled.set_contrast(127);
            myOled.write_string(0, 0, 0, (char *)"**************** ", FONT_8x8, 0, 1);
            myOled.write_string(0, 4, 1, (char *)"Pi Pico SS_OLED", FONT_8x8, 0, 1);
            myOled.write_string(0, 8, 2, (char *)"running on the", FONT_8x8, 0, 1);
            myOled.write_string(0, 8, 3, (char *)"SSD1306 128x64", FONT_8x8, 0, 1);
            myOled.write_string(0, 4, 4, (char *)"monochrome OLED", FONT_8x8, 0, 1);
            myOled.write_string(0, 0, 5, (char *)"Written by L BANK", FONT_8x8, 0, 1);
            myOled.write_string(0, 4, 6, (char *)"Pico by M KOOIJ", FONT_8x8, 0, 1);
            myOled.write_string(0, 0, 7, (char *)"**************** ", FONT_8x8, 0, 1);
            sleep_ms(5000); //vTaskDelay(5000 / portTICK_PERIOD_MS);
        }

        myOled.fill(0, 1);
        myOled.write_string(0, 0, 0, (char *)"Now with 5 font sizes", FONT_6x8, 0, 1);
        myOled.write_string(0, 0, 1, (char *)"6x8 8x8 16x16", FONT_8x8, 0, 1);
        myOled.write_string(0, 0, 2, (char *)"16x32 and a new", FONT_8x8, 0, 1);
        myOled.write_string(0, 0, 3, (char *)"Stretched", FONT_12x16, 0, 1);
        myOled.write_string(0, 0, 5, (char *)"from 6x8", FONT_12x16, 0, 1);
        sleep_ms(5000);//vTaskDelay(5000 / portTICK_PERIOD_MS);

        int x, y;
        myOled.fill(0, 1);
        myOled.write_string(0, 0, 0, (char *)"Backbuffer Test", FONT_NORMAL, 0, 1);
        myOled.write_string(0, 0, 1, (char *)"96 lines", FONT_NORMAL, 0, 1);
       sleep_ms(2000);// vTaskDelay(2000 / portTICK_PERIOD_MS);
        for (x = 0; x < OLED_WIDTH - 1; x += 2)
        {
            myOled.draw_line(x, 0, OLED_WIDTH - x, OLED_HEIGHT - 1, 1);
        };
        for (y = 0; y < OLED_HEIGHT - 1; y += 2)
        {
            myOled.draw_line(OLED_WIDTH - 1, y, 0, OLED_HEIGHT - 1 - y, 1);
        };
        myOled.write_string(0, 0, 1, (char *)"Without backbuffer", FONT_SMALL, 0, 1);
        sleep_ms(2000);//vTaskDelay(2000 / portTICK_PERIOD_MS);
        myOled.fill(0, 1);
        for (x = 0; x < OLED_WIDTH - 1; x += 2)
        {
            myOled.draw_line(x, 0, OLED_WIDTH - 1 - x, OLED_HEIGHT - 1, 0);
        }
        for (y = 0; y < OLED_HEIGHT - 1; y += 2)
        {
            myOled.draw_line(OLED_WIDTH - 1, y, 0, OLED_HEIGHT - 1 - y, 0);
        }
        myOled.dump_buffer(ucBuffer);
        myOled.write_string(0, 0, 1, (char *)"With backbuffer", FONT_SMALL, 0, 1);
        sleep_ms(2000);//vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
