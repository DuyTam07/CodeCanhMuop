#include <Arduino.h>
#include "InfoWifiMQTT.h"
#include "configHardware.h"

#include <WiFi.h>
#include <MQTT.h>

void CheckWifi(const char * NameWifi, const char * PassWifi);
void Connect();
void PublishTopic();
void SubscribeTopic();
void OnAndOff(String payload,uint8_t light, String status);
void MakeAction(String topic, String payload);
void MakeAction(String topic, String payload);
void messageReceived(String &topic, String &payload);
void SetupMQTT();
void ClientLoop();
void MQTTPublish(String topic, String data);