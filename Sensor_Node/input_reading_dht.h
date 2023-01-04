#ifndef __INPUT_READING_DHT_H__
#define __INPUT_READING_DHT_H__

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

#include "wifi_connection.h"
#include "global.h"

#define DHTTYPE       DHT11 // DHT 11
#define DHT_PIN       D4


void DHT_Reading();
#endif