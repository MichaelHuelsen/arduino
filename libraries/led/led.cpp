#include "/Users/micha/Development/projects/arduino/libraries/led/led.h"
void initLedOutput(int pin)
{
    pinMode(pin, OUTPUT);
}

void initLedInput(int pin)
{
    pinMode(pin, INPUT);
}
