#include <espnow.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

#include "scheduler.h"
#include "timer.h"
#include "global.h"
#include "input_reading_dht.h"
#include "wifi_connection.h"
#include "output_processing.h"


#define SERIAL_DEBUG_BAUD   9600



void setup() {
  // put your setup code here, to run once:


  Serial.begin(SERIAL_DEBUG_BAUD);
  WF_Init();
  TM_Init();
  SCH_Init();
  OUT_Init();

  SCH_Add_Task(WF_CheckConnection, 0, 1);   //10ms
  SCH_Add_Task(OUT_Controller, 0, 1);
  SCH_Add_Task(DHT_Reading, 0, 200);        //2s
}

void loop() {
  // put your main code here, to run repeatedly:
  SCH_Dispatch_Tasks();
}
