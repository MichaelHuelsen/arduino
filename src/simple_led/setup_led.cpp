#include <Arduino.h>
#include <HardwareSerial.h>
#include <config.h>
#include <led.h>

Led led(LED_PIN);

void setup_led_init() {
  Serial.println("LED setup initialized");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  led.begin();
}

void setup_led_loop() {
  // Pulse built-in LED briefly
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

  // Pulse built-in LED briefly again
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  delay(900);
}
