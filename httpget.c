
#include "espressif/esp_common.h"
#include "esp/uart.h"

#include <unistd.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#include "global.c"
extern int i_hko_temperature;
extern int i_hko_humidity;

extern char str_hko_temp[2];
extern char str_hko_humid[2];

#include "test/currentweather.c"

#include "hko_rss.c"

#define WEB_SERVER "rss.weather.gov.hk"
#define WEB_PORT "80"
#define WEB_PATH "/rss/CurrentWeather.xml"

void extractDistrictWeather(char str_input[])
{
    getTemperatureByDistrict(str_input, str_ws_hong_kong_observatory, STR_HONG_KONG_OBSERVATORY, "99");
    getTemperatureByDistrict(str_input, str_ws_kings_park, STR_KINGS_PARK, "99");
    getTemperatureByDistrict(str_input, str_ws_kwun_tong, STR_KWUN_TONG, "99");


}

void http_get_task(void *pvParameters)
{
    printf("http_get_task:start");

    while(1)
    {
        const struct addrinfo hints = {
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM,
        };
        struct addrinfo *res;

        printf("dns lookup \n");
        int err = getaddrinfo(WEB_SERVER, WEB_PORT, &hints, &res);

        if (err !=0||res==NULL)
        {
            printf("dns lookup failed\n");
            if (res)
                freeaddrinfo(res);
            vTaskDelay(1000/portTICK_PERIOD_MS);
            continue;
        }

        struct sockaddr *sa = res->ai_addr;
        if(sa->sa_family == AF_INET)
        {
            printf("dns lookup ok IP%s", inet_ntoa(((struct sockaddr_in *)sa)->sin_addr));
        }

        int s = socket(res->ai_family, res->ai_socktype,0);
        if (s<0)
        {
            printf("Failed to allocate socket\n");
            freeaddrinfo(res);
            vTaskDelay(1000/portTICK_PERIOD_MS);
            continue;
        }

        printf("allocated socket\n");

        if(connect(s, res->ai_addr, res->ai_addrlen) != 0)
        {
            close(s);
            freeaddrinfo(res);
            printf("socket connect failed\n");
            vTaskDelay(4000 / portTICK_PERIOD_MS);
            continue;
        }

        printf("connected\n");
        freeaddrinfo(res);

        const char *req =
            "GET "WEB_PATH" HTTP/1.1\r\n"
            "Host: "WEB_SERVER"\r\n"
            "User-Agent: esp-open-rtos/0.1 esp8266\r\n"
            "Connection: close\r\n"
            "\r\n";

        if (write(s, req, strlen(req)) < 0)
        {
            printf("socket send failed\n");
            close(s);
            vTaskDelay(4000/ portTICK_PERIOD_MS);
            continue;
        }
        printf("socket send ok\n");

        rss_buffer[0]='\0';
        static char recv_buf[128];
        int r;

        do{
            bzero(recv_buf, 128);
            r=read(s,recv_buf, 127);
            strcat(rss_buffer, recv_buf);

        } while(r>0);

        printf("done reading from socket\n");

        close(s);

        char str_temp1[10];
        getAirTemperature_2_digit(rss_buffer, str_hko_temp);
        fixIf1Digit(str_hko_temp,str_temp1);
        printf("temperature:'%s'\n", str_temp1);

        getHumidityTemperature_2_digit(rss_buffer, str_hko_humid);
        fixIf1Digit(str_hko_humid,str_temp1);
        printf("humidity:'%s'\n", str_temp1);

        getLastUpdate(rss_buffer, str_last_update);
        printf("last update:'%s'\n", str_last_update);

        extractDistrictWeather(rss_buffer);

        for(int i=11;i>1;i--)
        {
            printf("countdown to refresh->%d\n", i);
            vTaskDelay(1000/portTICK_PERIOD_MS);
        }

    }
}

void httpget_start(void)
{
    printf("starting httpget\n");

    xTaskCreate(http_get_task, "http_get_task", 512, NULL, 2, NULL);
}
