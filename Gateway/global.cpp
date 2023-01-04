#include "global.h"


WiFiClient espClient = WiFiClient();
PubSubClient client(espClient);

struct_message myData = {0, 0, 0, false, false};

uint8_t broadcastAddress_1[] = {0x48, 0x3F, 0xDA, 0x68, 0x13, 0xC5};
uint8_t broadcastAddress_2[] = {0x48, 0x3F, 0xDA, 0x67, 0xB5, 0x0A};
