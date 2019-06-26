#include <Arduino.h>

#define DEN1 16
#define DEN2 4
#define DEN3 0
#define DEN4 2

#define ON HIGH
#define OFF LOW

void SetupHardware();
void TurnOn(uint8_t light);
void TurnOff(uint8_t light);