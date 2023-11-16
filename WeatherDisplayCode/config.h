// Members :  Nick Stites
//         :  Danny Restrepo
//         :  Caleb Monti
//         :  Jake Milroy
// School  :  Portland State University
// Course  :  ECE 211 Intro to Design Processes
// Project :  Team 08 Sprint Project
// Title   :  Configuration Header for WWD Device
// Date    :  11th November 2023

#ifndef config_h
#define config_h



/************************ Adafruit IO Config *******************************/

#define IO_USERNAME    "danny_dev"
#define IO_KEY         "aio_KdPt61fGAfVTgXFzUo4pAdGIDYlI"



/******************************* WIFI **************************************/

#define WIFI_SSID       "Violet"
#define WIFI_PASS       "dcuor3526znzk"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);



#endif