#include <Arduino.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT11

void SetupDHT();
float ReadHumi();
float ReadTemp();