#include <Arduino.h>
#include "constants.h"

// Aktueller Status, boolean kann nur false/0 oder true/1 sein
// d.h. "not 0" = 1 und "not 1" = 0
// statt "not" kann man auch "!" schreiben
boolean redLedStatus = true;
boolean yellowLedStatus = false;
boolean blueLedStatus = false;

// Wie lange warten nach Ton?
const int pauseDelay = 200;

int counter = 0;

// display Pins
const int LED_SEG_A_PIN = 9;
const int LED_SEG_B_PIN = 10;
const int LED_SEG_C_PIN = 4;
const int LED_SEG_D_PIN = 5;
const int LED_SEG_E_PIN = 6;
const int LED_SEG_F_PIN = 8;
const int LED_SEG_G_PIN = 7;
const int LED_SEG_DOT_PIN = 3;

boolean isDotActive = false;

void setup()
{
    // Pins konfigurieren und LEDs auf Start setzen
    Serial.begin(9600);
    pinMode(soundPin, INPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(redPin, OUTPUT);

    digitalWrite(bluePin, blueLedStatus);
    digitalWrite(yellowPin, yellowLedStatus);
    digitalWrite(redPin, redLedStatus);

    // display Setup
    isDotActive = false;
    pinMode(LED_SEG_A_PIN, OUTPUT);
    pinMode(LED_SEG_B_PIN, OUTPUT);
    pinMode(LED_SEG_C_PIN, OUTPUT);
    pinMode(LED_SEG_D_PIN, OUTPUT);
    pinMode(LED_SEG_E_PIN, OUTPUT);
    pinMode(LED_SEG_F_PIN, OUTPUT);
    pinMode(LED_SEG_G_PIN, OUTPUT);
    pinMode(LED_SEG_DOT_PIN, OUTPUT);

    displayDigit(counter);
}

void switchLed()
{

    if (redLedStatus)
    {
        redLedStatus = false;
        yellowLedStatus = true;
        writeLedStatus();
        return;
    }

    if (yellowLedStatus)
    {
        yellowLedStatus = false;
        blueLedStatus = true;
        writeLedStatus();
        return;
    }
    if (blueLedStatus)
    {
        blueLedStatus = false;
        redLedStatus = true;
        writeLedStatus();
        return;
    }
}

void writeLedStatus()
{

    digitalWrite(bluePin, blueLedStatus);
    digitalWrite(yellowPin, yellowLedStatus);
    digitalWrite(redPin, redLedStatus);

    counter = counter + 1;
    if (counter > 9)
    {
        counter = 0;
    }
    // displayDigit(counter);
}

void testDisplay()
{

    for (byte i = 0; i < 10; i++)
    {
        displayDigit(i);
        for (byte d = 0; d < 4; d++)
        {
            toggleDot();
            delay(250);
        }
    };
    // digitalWrite(LED_SEG_A_PIN, HIGH);
}

void toggleDot()
{
    if (isDotActive == true)
    {
        digitalWrite(LED_SEG_DOT_PIN, HIGH);
        isDotActive = false;
    }
    else
    {
        digitalWrite(LED_SEG_DOT_PIN, LOW);
        isDotActive = true;
    }
}

void displayDigit(byte digit)
{
    turnOffDisplay();
    if (digit > 9)
    {
        return;
    }

    // Conditions for displaying segment a
    if (digit != 1 && digit != 4)
    {
        digitalWrite(LED_SEG_A_PIN, HIGH);
    }

    // Conditions for displaying segment b
    if (digit != 5 && digit != 6)
    {
        digitalWrite(LED_SEG_B_PIN, HIGH);
    }

    // Conditions for displaying segment c
    if (digit != 2)
    {
        digitalWrite(LED_SEG_C_PIN, HIGH);
    }

    // Conditions for displaying segment d
    if (digit != 1 && digit != 4 && digit != 7)
    {
        digitalWrite(LED_SEG_D_PIN, HIGH);
    }

    // Conditions for displaying segment e
    if (digit == 2 || digit == 6 || digit == 8 || digit == 0)
    {
        digitalWrite(LED_SEG_E_PIN, HIGH);
    }

    // Conditions for displaying segment f
    if (digit != 1 && digit != 2 && digit != 3 && digit != 7)
    {
        digitalWrite(LED_SEG_F_PIN, HIGH);
    }

    if (digit != 0 && digit != 1 && digit != 7)
    {
        digitalWrite(LED_SEG_G_PIN, HIGH);
    }
}

void turnOffDisplay()
{
    digitalWrite(LED_SEG_A_PIN, LOW);
    digitalWrite(LED_SEG_B_PIN, LOW);
    digitalWrite(LED_SEG_C_PIN, LOW);
    digitalWrite(LED_SEG_D_PIN, LOW);
    digitalWrite(LED_SEG_E_PIN, LOW);
    digitalWrite(LED_SEG_F_PIN, LOW);
    digitalWrite(LED_SEG_G_PIN, LOW);
}

void showSensitivity(int i)
{
    if (i <= 550)
    {
        displayDigit(1);
    }
    if (i > 500 && i <= 525)
    {
        displayDigit(2);
    }
    if (i > 525 && i <= 550)
    {
        displayDigit(3);
    }
    if (i > 550 && i <= 575)
    {
        displayDigit(4);
    }
    if (i > 575 && i <= 600)
    {
        displayDigit(5);
    }
    if (i > 600)
    {
        displayDigit(9);
    }
}

void loop()
{
    // Digitalpin 7 auslesen und bei LOW umschalten
    int din = digitalRead(soundPin);
    int sensorValue = analogRead(analogPin);

    if (!din)
    {
        switchLed();
        showSensitivity(sensorValue);

        /*
        redLedStatus = !redLedStatus;
        digitalWrite(redPin, !redLedStatus);
        digitalWrite(yellowPin, redLedStatus);
        */
        delay(pauseDelay);
    }

    // testDisplay();
}