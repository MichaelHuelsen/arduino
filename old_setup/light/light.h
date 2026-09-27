#include "/Users/micha/Development/projects/arduino/libraries/led/led.h"
#include "/Users/micha/Development/projects/arduino/libraries/display/seven-segment.h"
const int LED_PIN_RED = 13;
const int LED_PIN_YELLOW = 12;
const int LED_PIN_BLUE = 11;

int counter = 0;
int delayMs = 100;

void setupLight()
{
    initLedOutput(LED_PIN_RED);
    initLedOutput(LED_PIN_YELLOW);
    initLedOutput(LED_PIN_BLUE);
    initSevenSegment(9, 10, 4, 5, 6, 8, 7, 3);
    displayDigit(counter);
}

void loopLight()
{
    digitalWrite(LED_PIN_BLUE, HIGH);
    delay(delayMs);
    digitalWrite(LED_PIN_YELLOW, HIGH);
    delay(delayMs);
    digitalWrite(LED_PIN_RED, HIGH);
    delay(delayMs);
    digitalWrite(LED_PIN_BLUE, LOW);
    delay(delayMs);
    digitalWrite(LED_PIN_YELLOW, LOW);
    delay(delayMs);
    digitalWrite(LED_PIN_RED, LOW);
    delay(delayMs);
    if (counter < 9)
    {
        counter += 1;
    }
    else
    {
        counter = 0;
    }
    displayDigit(counter);
}