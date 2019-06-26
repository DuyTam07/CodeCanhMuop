#include <configMQTT.h>

WiFiClient net;
MQTTClient client;

void CheckWifi(const char * NameWifi, const char * PassWifi)
{
  int time = 0;
  while(WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(NameWifi, PassWifi);
    Serial.print(".");
    delay(1000);
    time++;

    if(WiFi.status() == WL_CONNECTED){
      Serial.println(String("Connected ") + String(NameWifi));
    }

    if(time >=10){
      return;
    }
  }
}

void Connect() 
{
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) 
  {
    CheckWifi(NAME_WIFI_1,PASS_WIFI_1);
    CheckWifi(NAME_WIFI_2,PASS_WIFI_2);
    CheckWifi(NAME_WIFI_3,PASS_WIFI_3);
  }

  Serial.print("\nconnecting...");
  while (!client.connect(CLIENT_ID, USER_NAME, PASS_MQTT)) 
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");
 
}

void PublishTopic()
{
  client.publish(TOPIC_PUB_LIGHT_1,TOPIC_PUB_STATUS_OFF);
  client.publish(TOPIC_PUB_LIGHT_2,TOPIC_PUB_STATUS_OFF);
  client.publish(TOPIC_PUB_LIGHT_3,TOPIC_PUB_STATUS_OFF);
  client.publish(TOPIC_PUB_LIGHT_4,TOPIC_PUB_STATUS_OFF);
}

void SubscribeTopic()
{
  client.subscribe(TOPIC_SUB_LIGHT_1);
  client.subscribe(TOPIC_SUB_LIGHT_2);
  client.subscribe(TOPIC_SUB_LIGHT_3);
  client.subscribe(TOPIC_SUB_LIGHT_4);
}

void OnAndOff(String payload,uint8_t light, String status)
{
  if(payload.compareTo(TOPIC_PUB_STATUS_ON) == 0)
  {
    TurnOn(light);
    client.publish(status,TOPIC_PUB_STATUS_ON);
  }
  else if(payload.compareTo(TOPIC_PUB_STATUS_OFF) == 0)
  {
    TurnOff(light);
    client.publish(status,TOPIC_PUB_STATUS_OFF);
  }
}

void MakeAction(String topic, String payload)
{
  if(topic.compareTo(TOPIC_SUB_LIGHT_1) == 0)
  {
    OnAndOff(payload,DEN1,TOPIC_PUB_LIGHT_1);
  }
  else if(topic.compareTo(TOPIC_SUB_LIGHT_2) == 0)
  {
    OnAndOff(payload,DEN2,TOPIC_PUB_LIGHT_2);
  }
  else if(topic.compareTo(TOPIC_SUB_LIGHT_3) == 0)
  {
    OnAndOff(payload,DEN3,TOPIC_PUB_LIGHT_3);
  }
  else if (topic.compareTo(TOPIC_SUB_LIGHT_4) == 0)
  {
    OnAndOff(payload,DEN4,TOPIC_PUB_LIGHT_4);
  }
}

void messageReceived(String &topic, String &payload) 
{
  Serial.println("incoming: " + topic + " - " + payload);
  MakeAction(topic,payload);
}

void SetupMQTT()
{
    WiFi.begin(NAME_WIFI_1, PASS_WIFI_1);
    client.begin(HOST_NAME,PORT, net);
    client.onMessage(messageReceived);
    Connect();
    PublishTopic();
    SubscribeTopic();
}

void ClientLoop()
{
    client.loop();
    delay(10);  // <- fixes some issues with WiFi stability

    if (!client.connected()) 
    {
        Connect();
    }
}

void MQTTPublish(String topic, String data)
{
    client.publish(topic,data);
}