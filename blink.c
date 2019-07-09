/* The classic "blink" example
 *
 * This sample code is in the public domain.
 */
#include <stdlib.h>
#include "espressif/esp_common.h"
#include "esp/uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "esp8266.h"

#include "ssd1306_simple.c"

const int gpio = 2;

/* This task uses the high level GPIO API (esp_gpio.h) to blink an LED.
 *
 */
void blinkenTask(void *pvParameters)
{
    gpio_enable(gpio, GPIO_OUTPUT);
    while(1) {
        printf("helloworld\r\n");
        gpio_write(gpio, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_write(gpio, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}


void user_init(void)
{
    uart_set_baud(0, 115200);

    ssd1306_start();
    xTaskCreate(blinkenTask, "blinkenTask", 256, NULL, 2, NULL);
}
