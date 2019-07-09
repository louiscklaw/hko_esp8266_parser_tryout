#ifndef GLOBAL_C
    #define GLOBAL_C

    char * current_time;


    #define RSS_BUFFER_LEN 10*1024
    char rss_buffer[RSS_BUFFER_LEN];

    int i_hko_temperature;
    int i_hko_humidity;

    char str_hko_temp[2];
    char str_hko_humid[2];

#endif
