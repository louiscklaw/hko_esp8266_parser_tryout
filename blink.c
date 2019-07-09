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

#include "global.c"
#include "ssd1306_simple.c"
#include "sntp.c"
#include "httpget.c"

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


    struct sdk_station_config config = {
        .ssid = WIFI_SSID,
        .password = WIFI_PASS,
    };

    /* required to call wifi_set_opmode before station_set_config */
    sdk_wifi_set_opmode(STATION_MODE);
    sdk_wifi_station_set_config(&config);


    ssd1306_start();
    sntp_start();
    httpget_start();

    xTaskCreate(blinkenTask, "blinkenTask", 256, NULL, 2, NULL);
}
