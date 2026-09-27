#include "config.h"
#include <Arduino.h>
#include <Led.h>

Led led(LED_PIN);

void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println("Program started");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  led.begin();
}
void loop() {
  // START PROGRAM
  //  // Pulse built-in LED briefly

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(900);

  Serial.println("D8 ON");
  digitalWrite(LED_PIN, HIGH);
  delay(1000);

  Serial.println("D8 OFF");
  digitalWrite(LED_PIN, LOW);
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
