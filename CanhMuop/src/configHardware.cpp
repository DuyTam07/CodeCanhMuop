#include "configHardware.h"

void SetupHardware()
{
    pinMode(DEN1,OUTPUT);
    pinMode(DEN2,OUTPUT);
    pinMode(DEN3,OUTPUT);
    pinMode(DEN4,OUTPUT);

    TurnOff(DEN1);
    TurnOff(DEN2);
    TurnOff(DEN3);
    TurnOff(DEN4);

    Serial.begin(115200);
}

void TurnOn(uint8_t light)
{
    digitalWrite(light,ON);
}

void TurnOff(uint8_t light)
{
    digitalWrite(light,OFF);
}

