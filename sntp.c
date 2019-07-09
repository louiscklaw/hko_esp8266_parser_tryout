
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "espressif/esp_common.h"
#include "esp/uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "esp8266.h"

#include <lwip/err.h>
#include <lwip/sockets.h>
#include <lwip/sys.h>
#include <lwip/netdb.h>
#include <lwip/dns.h>

#include <sntp.h>
#include <time.h>

#include "global.c"

#include <ssid_config.h>

#define SNTP_SERVERS 	"stdtime.gov.hk"


extern char* current_time;

void sntp_task(void * pvParameters)
{
    const char *sntp_servers[] = {SNTP_SERVERS};

    while(sdk_wifi_station_get_connect_status() != STATION_GOT_IP)
    {
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }

    printf("sntp:IP got\n");

    sntp_set_update_delay(5*60000);

    const struct timezone tz = {8*60, 0};
    sntp_initialize(&tz);
    sntp_set_servers(sntp_servers, sizeof(sntp_servers)/sizeof(char*));
    printf("DONE\n");

    while(1)
    {
        time_t ts = time(NULL);
        current_time = ctime(&ts);

        printf("sntp:TIME: %s\n", current_time);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void sntp_start(void)
{
    xTaskCreate(sntp_task, "sntp_task", 1024, NULL, 2, NULL);
}
