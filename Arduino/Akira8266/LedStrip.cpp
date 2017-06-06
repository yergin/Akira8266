#include "LedStrip.h"

#include "Pallette.h"

LedStrip::LedStrip() {
  FastLED.addLeds<APA102, LED_STRIP_DATA_PIN, LED_STRIP_CLOCK_PIN, BGR, DATA_RATE_MHZ(LED_STRIP_MHZ)>(_buffer, LED_STRIP_COUNT);
  for (int i = 0; i < count(); ++i) {
    _mask[i] = 0xFF;
  }
}

void LedStrip::preBlendLed(int led, const CRGB& color) {
  Pallette::colorScale(_buffer + led, color, 255 - _mask[led]);
}

void LedStrip::overlayLed(int led, const CRGB& color) {
  Pallette::colorScaleSum(_buffer + led, color, _mask[led]);
}

void LedStrip::overwriteLed(int led, const CRGB& color) {
  Pallette::colorScale(_buffer + led, color, _mask[led]);
}

void LedStrip::writeColor(const CRGB& color) {
  for (int i = 0; i < count(); ++i) {
    writeLed(i, color);
  }
}
