#include "output_processing.h"

void OUT_Init(){
  pinMode(HUMI_RELAY_PIN, OUTPUT);
  pinMode(TEMP_RELAY_PIN, OUTPUT);

  digitalWrite(HUMI_RELAY_PIN, 1);
  digitalWrite(TEMP_RELAY_PIN, 1);
}

void OUT_Controller(){
    if(cmd == "TOO_HUMID"){
      myData.humiRelayState = true;
      digitalWrite(HUMI_RELAY_PIN, 0);
    }
    else if(cmd == "TOO_DRY"){
      myData.humiRelayState = false;
      digitalWrite(HUMI_RELAY_PIN, 1);
    }
    else if(cmd == "TOO_HOT"){
      myData.tempRelayState = true;
      digitalWrite(TEMP_RELAY_PIN, 0);
    }
    else if(cmd == "TOO_COLD"){
      myData.tempRelayState = false;
      digitalWrite(TEMP_RELAY_PIN, 1); 
    }
    else {
      myData.tempRelayState = false;
      myData.humiRelayState = false;
      digitalWrite(HUMI_RELAY_PIN, 1);
      digitalWrite(TEMP_RELAY_PIN, 1);
    }
}
