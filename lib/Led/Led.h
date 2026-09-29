#ifndef _LED_H_
#define _LED_H_

#pragma once
#include <Arduino.h>
#include <stdint.h>

// LED OUTPUTFUNCTION

void initLedOutput(int pin);
void initLedInput(int pin);

class Led {
public:
  explicit Led(uint8_t pin);

  void begin();
  void on();
  void off();
  void toggle();

private:
  uint8_t _pin;
  bool _state;
};

#endif
