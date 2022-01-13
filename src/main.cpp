#include "common.h"
#include "mainApp.h"
#include "ledHelper.h"
#include "usbHelper.h"
#include "keyHelper.h"
#include "displayHelper.h"
  
BaseType_t xReturned;
TaskHandle_t xLedTaskHandle = NULL;
TaskHandle_t xUsbTaskHandle = NULL;
TaskHandle_t xKeyTaskHandle = NULL;
TaskHandle_t xDispTaskHandle = NULL;

LedHelper *m_ledHlpr = LedHelper::getInstance();
KeyHelper *m_keyHlpr = KeyHelper::getInstance();


int main() {

  board_init();    
/* Create the task, storing the handle. */
    xReturned = xTaskCreate(
                  m_ledHlpr->ledTask,       /* Function that implements the task. */
                  "Ledtask",   /* Text name for the task. */
                  512,             /* Stack size in words, not bytes. */
                  ( void * ) 1,    /* Parameter passed into the task. */
                  tskIDLE_PRIORITY,/* Priority at which the task is created. */
                  &xLedTaskHandle );   
    
    xReturned = xTaskCreate(
                USBHelper::usbMainTask,       /* Function that implements the task. */
                "USBtask",   /* Text name for the task. */
                8196,             /* Stack size in words, not bytes. */
                ( void * ) 1,    /* Parameter passed into the task. */
                tskIDLE_PRIORITY,/* Priority at which the task is created. */
                &xUsbTaskHandle );   

    // xReturned = xTaskCreate(
    //             KeyHelper::keyTask,       /* Function that implements the task. */
    //             "key task",   /* Text name for the task. */
    //             512,             /* Stack size in words, not bytes. */
    //             ( void * ) 1,    /* Parameter passed into the task. */
    //             tskIDLE_PRIORITY,/* Priority at which the task is created. */
    //             &xKeyTaskHandle );   

    // xReturned = xTaskCreate(
    //             DisplayHelper::displayTask,       /* Function that implements the task. */
    //             "disp task",   /* Text name for the task. */
    //             4096,             /* Stack size in words, not bytes. */
    //             ( void * ) 1,    /* Parameter passed into the task. */
    //             tskIDLE_PRIORITY,/* Priority at which the task is created. */
    //             &xDispTaskHandle );   
    
    // xReturned = xTaskCreate(
    //         MainApp::mainApp,       /* Function that implements the task. */
    //         "USB",   /* Text name for the task. */
    //         512,             /* Stack size in words, not bytes. */
    //         ( void * ) 1,    /* Parameter passed into the task. */
    //         tskIDLE_PRIORITY,/* Priority at which the task is created. */
    //         &xDispTaskHandle );   

                
    // while(1)
    // {
    //     tud_task();
    //     hid_task();
    // }
    vTaskStartScheduler();
    while(1)
    {
        configASSERT(0);    /* We should never get here */
    }

}
