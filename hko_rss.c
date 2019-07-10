
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "espressif/esp_common.h"
#include "esp/uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "esp8266.h"

void getLastUpdate(char* str_input, char* str_output)
{
    char * pch;
    char str_temp_start[] = "<pubDate>";
    int len_str_temp_start = strlen(str_temp_start);

    pch=strstr(str_input, str_temp_start);

    strncpy(str_output, pch+len_str_temp_start, 29);

}

void getAirTemperature_2_digit(char* str_input, char* str_output)
{
    char * pch;
    char str_temp_start[] = "Air temperature : ";
    int len_str_temp_start = strlen(str_temp_start);

    pch=strstr(str_input, str_temp_start);

    strncpy(str_output, pch+len_str_temp_start, 2);

    // getReading(str_input, str_temp_start,.2, str_output);
}

void getHumidityTemperature_2_digit(char * str_input, char* str_output)
{
    char *pch;
    char str_humid_start[] = "Relative Humidity : ";
    int len_str_humid_start = strlen(str_humid_start);

    pch = strstr(str_input, str_humid_start);

    strncpy(str_output,pch+len_str_humid_start,2);

    // getReading(str_input, str_humid_start,.2, str_output);
}

void fixIf1Digit(char str_input[], char str_output[])
{
    char* pch;
    str_output[0]='\0';

    pch = strchr(str_input, ' ');
    if (pch != NULL){
        printf("single digit found");
        strncpy(str_output, str_input, 1);
        str_output[1]='\0';
    }else{
        printf("2 digit found");
        strcpy(str_output, str_input);
    }
}
