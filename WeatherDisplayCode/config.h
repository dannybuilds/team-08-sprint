/************************ Adafruit IO Config *******************************/

#define IO_USERNAME    "danny_dev"
#define IO_KEY         "aio_txaP75N7iWrM5AZcxfmfYzGNp3RU"



/******************************* WIFI **************************************/

#define WIFI_SSID       "poobahs (x)"
#define WIFI_PASS       "still->pepper5palace"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);