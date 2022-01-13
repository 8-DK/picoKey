/*
 * File: usbHelper.h
 * Project: picoKey
 * File Created: Tuesday, 11th January 2022 9:51:37 pm
 * Author: Dhananjay Khairnar (khairnardm@gmail.com)
 * -----
 * Last Modified: Wednesday, 12th January 2022 12:08:37 am
 * Modified By: 8-DK (khairnardm@gmail.com>)
 * -----
 * Copyright 2021 - 2022 https://github.com/8-DK
 */

#ifndef __USBHELPER__
#define __USBHELPER__

#include "common.h"

using namespace std;

#include "usb_descriptors.h"

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

class USBHelper
{

public:
    static uint32_t blink_interval_ms;
    USBHelper();
    static void send_hid_report(uint8_t report_id, uint32_t btn);
    static void usbMainTask( void * pvParameters );
    static void usbLoop();
};


#endif