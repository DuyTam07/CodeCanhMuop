#include "configDHT.h"

DHT dht(DHTPIN,DHTTYPE);

void SetupDHT()
{
    dht.begin();
}

float ReadHumi()
{
    float humi = dht.readHumidity();
    if(isnan(humi)){
      Serial.println(F("Failed to read humidyty from DHT sensor!"));
        return -1;
    }
    else{
        Serial.print(F("Humidity: "));
        Serial.print(humi);
        Serial.println(F("%"));
        return humi;
    }
}

float ReadTemp()
{
    float temp = dht.readTemperature();
    if(isnan(temp)){
      Serial.println(F("Failed to read temperature from DHT sensor!"));
        return -1;
    }
    else{
        Serial.print(F("Temperature: "));
        Serial.print(temp);
        Serial.println(F("C "));
        return temp;
    }
}