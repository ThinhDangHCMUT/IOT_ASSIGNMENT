#include "input_reading_dht.h"

DHT dht(DHT_PIN, DHTTYPE);     // Initialize DHT sensor




void DHT_Reading(){
  myData.humi = dht.readHumidity();
  myData.temp = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(myData.humi) || isnan(myData.temp)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else {
    Serial.print("HUMI: "); Serial.println(myData.humi);
    Serial.print("TEMP: "); Serial.println(myData.temp);   
    
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  }
}
