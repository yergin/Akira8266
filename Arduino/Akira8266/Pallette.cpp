#include "Pallette.h"

void Pallette::colorScale(CRGB* out, const CRGB& color, int scale)
{
  // Optimized color scaling by 0-255
  // Source: https://research.swtch.com/divmult
  int prescale = (scale << 8) + scale;
  out->r = (color.r * prescale + 0x101) >> 16;
  out->g = (color.g * prescale + 0x101) >> 16;
  out->b = (color.b * prescale + 0x101) >> 16;
}

void Pallette::colorScaleSum(CRGB* out, const CRGB& color, int scale) {
  // Optimized color scaling by 0-255
  // Source: https://research.swtch.com/divmult
  int prescale = (scale << 8) + scale;
  out->r += (color.r * prescale + 0x101) >> 16;
  out->g += (color.g * prescale + 0x101) >> 16;
  out->b += (color.b * prescale + 0x101) >> 16;
}

void Pallette::setColors(const uint32_t* colors, uint8_t count) {
  _colors = colors;
  _count = count;
}

CRGB Pallette::interpolateCircular(uint8_t first, uint8_t last, uint8_t offset, uint8_t fract) const {
  uint8_t index = offset % (last - first + 1) + first;
  return blend(index, index == last ? first : index + 1, fract);
}

CRGB Pallette::blend(uint8_t index1, uint8_t index2, uint8_t alpha) const {
  CRGB out = {};
  CRGB col1 = _colors[index1];
  CRGB col2 = _colors[index2];
  colorScale(&out, col1, 255 - alpha);
  colorScaleSum(&out, col2, alpha);
  return out;
}

CRGB Pallette::randomInterpolate(uint8_t first, uint8_t last) const {
  uint8_t index = static_cast<uint8_t>(random(first, last));
  uint8_t alpha = static_cast<uint8_t>(random(256));
  return blend(index, index + 1, alpha);
}
