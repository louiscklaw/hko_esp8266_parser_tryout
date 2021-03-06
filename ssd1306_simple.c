
#include <string.h>


#include <espressif/esp_common.h>
#include <esp/uart.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <ssd1306/ssd1306.h>

#include <i2c/i2c.h>

#include "global.c"
extern char* current_time;
extern char str_hko_temp[2];
extern char str_hko_humid[2];

#include "fonts/fonts.h"
const font_info_t *font = NULL; // current font
font_face_t font_face = 0;

#define DISPLAY_WIDTH  128
#define DISPLAY_HEIGHT 64

#define PROTOCOL SSD1306_PROTO_I2C
#define ADDR     SSD1306_I2C_ADDR_0
#define I2C_BUS  0
#define SCL_PIN  5
#define SDA_PIN  4

/* Declare device descriptor */
static const ssd1306_t dev = {
    .protocol = PROTOCOL,
    .i2c_dev.bus      = I2C_BUS,
    .i2c_dev.addr     = ADDR,
    .width    = DISPLAY_WIDTH,
    .height   = DISPLAY_HEIGHT
};

/* Local frame buffer */
static uint8_t buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];
// TimerHandle_t scrol_timer_handle = NULL; // Timer handler

#define SECOND (1000 / portTICK_PERIOD_MS)

void ssd1306_start(void);

void ssd1306_task(void * pvParameters)
{
    printf("%s: Started user interface task\n", __FUNCTION__);
    vTaskDelay(1000/portTICK_PERIOD_MS);

    ssd1306_set_whole_display_lighting(&dev, false);

    int i =0;

    while(1)
    {
        font = font_builtin_fonts[0];

        ssd1306_fill_rectangle(&dev, buffer, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT/2, OLED_COLOR_BLACK);

        ssd1306_draw_string(&dev, buffer, font, 0, 0, current_time, OLED_COLOR_WHITE, OLED_COLOR_BLACK);

        ssd1306_draw_string(&dev, buffer, font, 0, 35, str_hko_temp, OLED_COLOR_WHITE, OLED_COLOR_BLACK);

        ssd1306_draw_string(&dev, buffer, font, 0, 45, str_hko_humid, OLED_COLOR_WHITE, OLED_COLOR_BLACK);

        ssd1306_draw_string(&dev, buffer, font, 0, 55, str_last_update, OLED_COLOR_WHITE, OLED_COLOR_BLACK);

        // district weather
        ssd1306_draw_string(&dev, buffer, font, 15, 35, str_ws_hong_kong_observatory, OLED_COLOR_WHITE, OLED_COLOR_BLACK);

        ssd1306_draw_string(&dev, buffer, font, 30, 35, str_ws_kings_park, OLED_COLOR_WHITE, OLED_COLOR_BLACK);

        ssd1306_draw_string(&dev, buffer, font, 45, 35, str_ws_kwun_tong, OLED_COLOR_WHITE, OLED_COLOR_BLACK);

        ssd1306_load_frame_buffer(&dev, buffer);

        if (i > 10){
            i = 0;
            printf("ssd1306 running \n");
        }
        i=i+1;

        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}

void ssd1306_start(void)
{
    printf("ssd1306_start");

    i2c_init(I2C_BUS, SCL_PIN, SDA_PIN, I2C_FREQ_400K);

    while (ssd1306_init(&dev) != 0)
    {
        printf("%s: failed to init SSD1306 lcd\n", __func__);
        vTaskDelay(SECOND);
    }

    ssd1306_set_whole_display_lighting(&dev, true);
    vTaskDelay(SECOND);

    xTaskCreate(ssd1306_task, "ssd1306_task", 256, NULL, 2, NULL);
}
