#include <Arduino.h>
#include "InfoWifiMQTT.h"

#include <WiFi.h>
#include <MQTT.h>

#define DEN1 12
#define DEN2 14
#define DEN3 27
#define DEN4 26

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() 
{
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect(CLIENT_ID, USER_NAME, PASS_MQTT)) 
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("cmd1");
  client.subscribe("cmd2");
  client.subscribe("cmd3");
  client.subscribe("cmd4");
  // client.unsubscribe("/hello");
}

void MakeTopic(String topic, String payload, String cmd, String status, uint8_t light)
{
  if(topic.compareTo(cmd) == 0)
  {
    if(payload.compareTo("on") == 0)
    {
      digitalWrite(light,LOW);
      client.publish(status,"on");
    }
    else if(payload.compareTo("off") == 0)
    {
      digitalWrite(light,HIGH);
      client.publish(status,"off");
    }
  }
}

void MakeAction(String topic, String payload)
{
  MakeTopic(topic, payload,"cmd1","status1",DEN1);
  MakeTopic(topic, payload,"cmd2","status2",DEN2);
  MakeTopic(topic, payload,"cmd3","status3",DEN3);
  MakeTopic(topic, payload,"cmd4","status4",DEN4);
}

void messageReceived(String &topic, String &payload) 
{
  Serial.println("incoming: " + topic + " - " + payload);
  MakeAction(topic,payload);
}

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(NAME_WIFI_1, PASS_WIFI_1);

  client.begin(HOST_NAME,PORT, net);
  client.onMessage(messageReceived);

  connect();

  pinMode(DEN1,OUTPUT);
  pinMode(DEN2,OUTPUT);
  pinMode(DEN3,OUTPUT);
  pinMode(DEN4,OUTPUT);
}

void loop() 
{
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) 
  {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 10000) 
  {
    lastMillis = millis();
    float temp = temperatureRead();
    client.publish("temp",String(temp));
    int sensorHall = hallRead();
    client.publish("hall",String(sensorHall));
  }
}

