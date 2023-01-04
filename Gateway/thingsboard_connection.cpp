#include "thingsboard_connection.h"

// The callback for when a PUBLISH message is received from the server.
void on_message(const char* topic, byte* payload, unsigned int length) {
  Serial.println("On message");
  char json[length + 1];
  strncpy (json, (char*)payload, length);
  json[length] = '\0';

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(json);

  // Decode JSON request
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject((char*)json);

  if (!data.success())
  {
    Serial.println("parseObject() failed");
    return;
  }


  // uint8_t dataSend[100];
  
  // memcpy(&dataSend[0], ((const char *)data["method"]), sizeof(dataSend[0]));

  String methodName = String((const char*)data["method"]);
  String paramsName = String((const char*)data["params"]);

  uint8_t *buffer = (uint8_t*) paramsName.c_str();
  size_t sizeBuff = sizeof(buffer) * paramsName.length();

  if(methodName == "TEMP_1" || methodName == "HUMI_1"){
      esp_now_send(broadcastAddress_1, buffer, sizeBuff);
  }
  else if(methodName == "TEMP_2" || methodName == "HUMI_2"){
      esp_now_send(broadcastAddress_2, buffer, sizeBuff);
  }
  Serial.println(methodName);

  String responseTopic = String(topic);
  responseTopic.replace("request", "response");
  
} 

void TB_Init(){
  client.setServer(THINGSBOARD_SERVER, 1883);
  client.setCallback(on_message);

}



void TB_CheckConnection(){
    if ( !client.connected() ) {
      Serial.print("Connecting to ThingsBoard node ...");
      // Attempt to connect (clientId, username, password)
      if ( client.connect("ESP8266 Device", TOKEN, NULL) ) {
        Serial.println( "[DONE]" );
        // Subscribing to receive RPC requests
        client.subscribe("v1/devices/me/rpc/request/+");

        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& data = jsonBuffer.createObject();
        data["active"] = true;

        char payload[256];
        data.printTo(payload, sizeof(payload));
        String strPayload = String(payload);
        Serial.println(strPayload);
        client.publish("v1/devices/me/attributes", strPayload.c_str());
  
      } else {
        Serial.print( "[FAILED] [ rc = " );
        Serial.print( client.state() );
        Serial.println( " : retrying in 5 seconds]" );
        // Wait 5 seconds before retrying
        delay( 5000 );
      }
    }

    client.loop();
}

void TB_SendmyData(){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  data["ID"] = myData.sensor_node_id;
  data["TEMP_" + String(myData.sensor_node_id)] = myData.temp;
  data["HUMI_" + String(myData.sensor_node_id)] = myData.humi;
  data["TEMP_RELAY_STATE_" + String(myData.sensor_node_id)] = myData.tempRelayState;
  data["HUMI_RELAY_STATE_" + String(myData.sensor_node_id)] = myData.humiRelayState;

  char payload[256];
  data.printTo(payload, sizeof(payload));
  String strPayload = String(payload);
  Serial.println(strPayload);
  client.publish("v1/devices/me/telemetry", strPayload.c_str());
  
}
