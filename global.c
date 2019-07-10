#ifndef GLOBAL_C
    #define GLOBAL_C

    char * current_time;


    #define RSS_BUFFER_LEN 10*1024
    char rss_buffer[RSS_BUFFER_LEN];

    int i_hko_temperature;
    int i_hko_humidity;

    char str_hko_temp[2];
    char str_hko_humid[2];
    char str_last_update[30];

    // weather station i_hko_temperature

    char str_ws_hong_kong_observatory[2];
    char str_ws_kings_park[2];
    char str_ws_wong_chuk_hang[2];
    char str_ws_ta_kwu_ling[2];
    char str_ws_lau_fau_shan[2];
    char str_ws_tai_po[2];
    char str_ws_sha_tin[2];
    char str_ws_tuen_mun[2];
    char str_ws_tseung_kwan_o[2];
    char str_ws_sai_kung[2];
    char str_ws_chek_lap_kok[2];
    char str_ws_tsing_yi[2];
    char str_ws_shek_kong[2];
    char str_ws_tsuen_wan_ho_koon[2];
    char str_ws_tsuen_wan_shing_mun_valley[2];
    char str_ws_hong_kong_park[2];
    char str_ws_shau_kei_wan[2];
    char str_ws_kowloon_city[2];
    char str_ws_happy_valley[2];
    char str_ws_wong_tai_sin[2];
    char str_ws_stanley[2];
    char str_ws_kwun_tong[2];
    char str_ws_sham_shui_po[2];
    char str_ws_kai_tak_runway_park[2];
    char str_ws_yuen_long_park[2];
    char str_ws_tai_mei_tuk[2];

    char* STR_HONG_KONG_OBSERVATORY="Hong Kong Observatory";
    char* STR_KINGS_PARK="King's Park";
    char* STR_WONG_CHUK_HANG="Wong Chuk Hang";
    char* STR_TA_KWU_LING="Ta Kwu Ling";
    char* STR_LAU_FAU_SHAN="Lau Fau Shan";
    char* STR_TAI_PO="Tai Po";
    char* STR_SHA_TIN="Sha Tin";
    char* STR_TUEN_MUN="Tuen Mun";
    char* STR_TSEUNG_KWAN_O="Tseung Kwan O";
    char* STR_SAI_KUNG="Sai Kung";
    char* STR_CHEK_LAP_KOK="Chek Lap Kok";
    char* STR_TSING_YI="Tsing Yi";
    char* STR_SHEK_KONG="Shek Kong";
    char* STR_TSUEN_WAN_HO_KOON="Tsuen Wan Ho Koon";
    char* STR_TSUEN_WAN_SHING_MUN_VALLEY="Tsuen Wan Shing Mun Valley";
    char* STR_HONG_KONG_PARK="Hong Kong Park";
    char* STR_SHAU_KEI_WAN="Shau Kei Wan";
    char* STR_KOWLOON_CITY="Kowloon City";
    char* STR_HAPPY_VALLEY="Happy Valley";
    char* STR_WONG_TAI_SIN="Wong Tai Sin";
    char* STR_STANLEY="Stanley";
    char* STR_KWUN_TONG="Kwun Tong";
    char* STR_SHAM_SHUI_PO="Sham Shui Po";
    char* STR_KAI_TAK_RUNWAY_PARK="Kai Tak Runway Park";
    char* STR_YUEN_LONG_PARK="Yuen Long Park";
    char* STR_TAI_MEI_TUK="Tai Mei Tuk";


#endif
