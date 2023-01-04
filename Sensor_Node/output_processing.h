#ifndef  __SYNC_OUTPUT_PROCESSING_H__
#define   __SYNC_OUTPUT_PROCESSING_H__


#include <ESP8266WiFi.h>
#include "global.h"
#include <espnow.h>


#define HUMI_RELAY_PIN      D5
#define TEMP_RELAY_PIN      D6

void OUT_Init();
void OUT_Controller();
#endif