#include "simple_led/setup_led.h"
#include <Arduino.h>
#include <HardwareSerial.h>
#include <config.h>

// Select which setup to run by uncommenting one:
#define ACTIVE_SETUP_LED
// #define ACTIVE_SETUP_EXAMPLE2

void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println("Program started");

#ifdef ACTIVE_SETUP_LED
  setup_led_init();
#endif

  // #ifdef ACTIVE_SETUP_EXAMPLE2
  // setup_example2_init();
  // #endif
}

void loop() {
#ifdef ACTIVE_SETUP_LED
  setup_led_loop();
#endif

  // #ifdef ACTIVE_SETUP_EXAMPLE2
  // setup_example2_loop();
  // #endif
}
