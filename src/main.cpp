#include "common.h"
#include "mainApp.h"
#include "ledHelper.h"
#include "usbHelper.h"
#include "keyHelper.h"
#include "displayHelper.h"
  

LedHelper *m_ledHlpr = LedHelper::getInstance();
KeyHelper *m_keyHlpr = KeyHelper::getInstance();


static pico_cpp::GPIO_Pin ledPin(25,pico_cpp::PinType::Output);
void vTaskCode( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. 
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
    */
    for( ;; )
    {
            ledPin.set_high();
            vTaskDelay(1000);
            ledPin.set_low();
            vTaskDelay(1000);
    }
}

void vTaskCode1( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. 
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
    */
    for( ;; )
    {
      // USBHelper::usbMainTask((void*)0);
    }
}

int main() {

  board_init();
  
BaseType_t xReturned;
TaskHandle_t xLedTaskHandle = NULL;
TaskHandle_t xUsbTaskHandle = NULL;
TaskHandle_t xKeyTaskHandle = NULL;
TaskHandle_t xDispTaskHandle = NULL;
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

    xReturned = xTaskCreate(
                KeyHelper::keyTask,       /* Function that implements the task. */
                "Keytask",   /* Text name for the task. */
                512,             /* Stack size in words, not bytes. */
                ( void * ) 1,    /* Parameter passed into the task. */
                tskIDLE_PRIORITY,/* Priority at which the task is created. */
                &xKeyTaskHandle );   

    xReturned = xTaskCreate(
                DisplayHelper::displayTask,       /* Function that implements the task. */
                "disp task",   /* Text name for the task. */
                4096,             /* Stack size in words, not bytes. */
                ( void * ) 1,    /* Parameter passed into the task. */
                tskIDLE_PRIORITY,/* Priority at which the task is created. */
                &xDispTaskHandle );   
    
    xReturned = xTaskCreate(
            MainApp::mainApp,       /* Function that implements the task. */
            "USB",   /* Text name for the task. */
            512,             /* Stack size in words, not bytes. */
            ( void * ) 1,    /* Parameter passed into the task. */
            tskIDLE_PRIORITY,/* Priority at which the task is created. */
            &xDispTaskHandle );   
    vTaskStartScheduler();
    while(1)
    {
        configASSERT(0);    /* We should never get here */
    }

}
