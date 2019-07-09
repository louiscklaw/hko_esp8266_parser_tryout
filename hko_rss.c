
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "espressif/esp_common.h"
#include "esp/uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "esp8266.h"

#include "re.h"


void getLastUpdate(char* str_input, char* str_output)
{

}


void getAirTemperature_2_digit(char* str_input, char* str_output)
{
    strcpy(str_output,"11");
}

void getHumidityTemperature_2_digit(char * str_input, char* str_output)
{
    strcpy(str_output,"12");
}
