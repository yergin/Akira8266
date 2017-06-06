#pragma once

#include "Config.h"

#include <FastLED.h>

class LedStrip {
public:
  LedStrip();

  void writeLed(int led, const CRGB& color) { _buffer[led] = color; }
  void preBlendLed(int led, const CRGB& color);
  void overlayLed(int led, const CRGB& color);
  void overwriteLed(int led, const CRGB& color);
  
  void writeColor(const CRGB& color);

  int count() const { return LED_STRIP_COUNT; }
  uint8_t* mask() { return _mask; }

private:
  CRGB _buffer[LED_STRIP_COUNT] = {};
  uint8_t _mask[LED_STRIP_COUNT] = {};
};
