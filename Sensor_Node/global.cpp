#include "global.h"


WiFiClient espClient = WiFiClient();
PubSubClient client(espClient);

struct_message myData = {1, 0, 0, false, false};

uint8_t broadcastAddress[] = {0x3C, 0x61, 0x05, 0xD0, 0x8F, 0xD2};

String cmd;
