#include <Arduino.h>
#include <Led.h>

Led led(8);

void setup() {
  led.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // External LED ON
  led.on();

  // Pulse built-in LED briefly
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(900);

  // External LED OFF
  led.off();

  // Pulse built-in LED briefly again
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  delay(900);
}
