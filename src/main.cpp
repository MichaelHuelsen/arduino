#include "config.h"
#include <Arduino.h>
#include <Led.h>

Led led(LED_PIN);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);

  led.begin();
}
void loop() {
  // START PROGRAM
  //  // Pulse built-in LED briefly

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(900);

  digitalWrite(8, HIGH);
  delay(1000);

  digitalWrite(8, LOW);
  delay(1000);

  /*
  led.on();
  delay(1000);

  led.off();
  delay(1000);*/

  // END OF PROGRAM// Pulse built-in LED briefly again
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  delay(900);
}
