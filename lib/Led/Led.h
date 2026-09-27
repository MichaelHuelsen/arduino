#pragma once
#include <Arduino.h>

#include <stdint.h>

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
