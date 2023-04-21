#include <Arduino.h>
// #include "../libraries/blink.h"

const int LED_PIN = 11;

void blinkSetup()
{
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
}

void setup()
{
    blinkSetup();
}

void loop()
{
    digitalWrite(LED_PIN, HIGH);
    Serial.println("HIGH");
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    Serial.println("LOW");
}