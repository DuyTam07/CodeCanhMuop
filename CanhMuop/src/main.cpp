#include <Arduino.h>
#include "InfoWifiMQTT.h"
#include "configDHT.h"
#include "configHardware.h"
#include "configMQTT.h"

unsigned long lastMillis = 0;

void setup() 
{
  SetupHardware();
  SetupMQTT();
  SetupDHT();
}

void loop() 
{
  ClientLoop();

  // publish a message roughly every second.
  if (millis() - lastMillis > 10000) 
  {
    lastMillis = millis();
    
    float temp = ReadTemp();
    float humi = ReadHumi();

    MQTTPublish(TOPIC_PUB_TEMP,String(temp));
    MQTTPublish(TOPIC_PUB_HUMI,String(humi));

  }
}

