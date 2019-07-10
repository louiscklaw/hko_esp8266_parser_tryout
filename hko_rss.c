
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
    strcpy(str_output, str_input);

    pch = strchr(str_output, ' ');
    if (pch==NULL)
    {
        printf("2 digit\n");
    }else{
        printf("1 digit\n");
        str_output[1]='\0';
    }
}

void getTemperatureByDistrict(char str_input[], char str_output[], char district[], char last_know_good_value[])
{
    str_output[0]='\0';

    char* pch;
    char formatted_district[20];
    sprintf(formatted_district, ">%s<", district);
    int len_formatted_district = strlen(formatted_district);

    pch = strstr(str_input, formatted_district);
    if (pch==NULL)
    {
        strcpy(str_output, last_know_good_value);
    }else{
        strncpy(str_output, pch+len_formatted_district+57,2);
    }
}
