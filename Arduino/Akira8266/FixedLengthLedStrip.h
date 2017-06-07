#pragma once

#include "LedStrip.h"

class FixedLengthLedStrip : public LedStrip {
public:
  FixedLengthLedStrip(int length);
  ~FixedLengthLedStrip();

  void writeLed(int led, const CRGB& color) override { _buffer[led] = color; }
  
  void preBlendLed(int led, const CRGB& color) override;
  void overlayLed(int led, const CRGB& color) override;
  void overwriteLed(int led, const CRGB& color) override;
  void writeColor(const CRGB& color) override;
  int length() const override { return _length; }
  uint8_t* mask() override { return _mask; }

protected:
  const int _length;
  CRGB* _buffer;
  uint8_t* _mask;
};
