#include <Arduino.h>
#include "/Users/micha/Development/projects/arduino/libraries/basics/basics.h"
#include "/Users/micha/Development/projects/arduino/libraries/led/led.h"
#include "light.h"

void setup()
{
    initBasics();
    setupLight();
}

void loop()
{
    loopLight();
}