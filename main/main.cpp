#include <stdio.h>
#include "SevenSegment.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

SevenSegment s1(0);
SevenSegment s2(4);

// create counter as global variable
uint8_t counter = 0;

// create task handle for LED display task
TaskHandle_t xSevenSegmentHandle = NULL;

// create task and move code into it
void vTaskScanSevenSegment(void *Parameters)
{
    while (1)
    {
        s1.DisplayNumber(counter / 10);
        s1.DisplayOn();
        vTaskDelay(10 / portTICK_PERIOD_MS);
        s1.DisplayOff();

        s2.DisplayNumber(counter % 10);
        s2.DisplayOn();
        vTaskDelay(10 / portTICK_PERIOD_MS);
        s2.DisplayOff();
    }
}


// in main, create display task
extern "C" void app_main(void)
{
    xTaskCreate(vTaskScanSevenSegment, 
      "Seven Seg", 1024, NULL, 
      10 , &xSevenSegmentHandle);
}