#pragma once

#include <FastLED.h>

class LedStrip {
public:
  virtual ~LedStrip() {}
  virtual void preBlendLed(int led, const CRGB& color) = 0;
  virtual void overlayLed(int led, const CRGB& color) = 0;
  virtual void overwriteLed(int led, const CRGB& color) = 0;
  virtual void writeColor(const CRGB& color) = 0;
  virtual int length() const = 0;
  virtual uint8_t* mask() = 0;
};
