#include "FixedLengthLedStrip.h"

#include "Pallette.h"

FixedLengthLedStrip::FixedLengthLedStrip(int length)
    : _length(length) {
  _buffer = new CRGB[length];
  _mask = new uint8_t[length];
  for (int i = 0; i < length; ++i) {
    _mask[i] = 0xFF;
  }
}

FixedLengthLedStrip::~FixedLengthLedStrip() {
  delete[] _buffer;
  delete[] _mask;
}

void FixedLengthLedStrip::preBlendLed(int led, const CRGB& color) {
  Pallette::colorScale(_buffer + led, color, 255 - _mask[led]);  
}

void FixedLengthLedStrip::overlayLed(int led, const CRGB& color) {
  Pallette::colorScaleSum(_buffer + led, color, _mask[led]);
}

void FixedLengthLedStrip::overwriteLed(int led, const CRGB& color) {
  Pallette::colorScale(_buffer + led, color, _mask[led]);
}

void FixedLengthLedStrip::writeColor(const CRGB& color) {
  for (int i = 0; i < _length; ++i) {
    overwriteLed(i, color);
  }
}
