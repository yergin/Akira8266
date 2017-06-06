#pragma once

#include <FastLED.h>
#include <cinttypes>

class Pallette {
public:
  static void colorScale(CRGB* out, const CRGB& color, int scale);
  static void colorScaleSum(CRGB* out, const CRGB& color, int scale);

  Pallette();
  Pallette(const uint32_t* colors, uint8_t count) { setColors(colors, count); }

  void setColors(const uint32_t* colors, uint8_t count);
  
  CRGB color(uint8_t index) const { return _colors[index % _count]; }
  CRGB interpolateCircular(uint8_t first, uint8_t last, uint8_t offset, uint8_t fract) const;
  CRGB blend(uint8_t index1, uint8_t index2, uint8_t alpha) const;
  CRGB randomInterpolate(uint8_t first, uint8_t last) const;

private:
  const uint32_t* _colors = 0;
  uint8_t _count = 0;
};