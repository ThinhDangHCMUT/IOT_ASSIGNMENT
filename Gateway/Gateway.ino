#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h> 

#include "scheduler.h"
#include "timer.h"
#include "global.h"
#include "global.h"
#include "wifi_connection.h"
#include "thingsboard_connection.h"


// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD   9600
void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_DEBUG_BAUD);
  WF_Init();
  TB_Init();
  TM_Init();
  SCH_Init();

  SCH_Add_Task(WF_CheckConnection, 0, 1);
  SCH_Add_Task(TB_CheckConnection, 0, 1);
}


void loop() {
  // put your main code here, to run repeatedly:
  SCH_Dispatch_Tasks();
}
