#ifndef __USBHELPER__
#define __USBHELPER__
#include <iostream>
#include "bsp/board.h"
#include "tusb.h"
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
    static void usbMainTask(void);
};


#endif