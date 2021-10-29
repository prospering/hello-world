/*
    This file sets up default environment const for the program. 
    Please do not change it. 
    If you want to use your own you can create a const.h with your own const, and modify the #include "const.local.h" in:
    - api_controller.cpp
    - main.cpp
    - wifi_setup.cpp
    (a condition to select automaticaly const.h if it exists will be added in the futur, this is a temporary solution).
*/

//Device id and api key for BAG Tower
#define X_API_KEY "i265LU6FHY7RgRXwbAXKJ5MKODhLKvVlF8q29Wv5"
#define DEVICE_ID "6f34c9b0-1791-1:d425bb60-3657-11ec-9"

//WiFi connection info
#define SSID "iPhone de bapti"
#define PASS "0633447891"

//ntp server
#define NTP_SERVER "fr.pool.ntp.org"