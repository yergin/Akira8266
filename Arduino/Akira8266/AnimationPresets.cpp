#include "AnimationPresets.h"

#include "Pallette.h"

static Pallette Pal(Colors, PRESET_COL_COUNT);

void LoopingAnimation::render() {
  draw(_frame);

  _frame = duration() ? (_frame + 1) % duration() : _frame + 1;
}

void WaveAnimation::draw(unsigned long frame) {
  static const unsigned long first = PRESET_COL_RED;
  static const unsigned long last = PRESET_COL_MAGENTA;
  static const unsigned long maxHue = (last - first + 1) << 8;

  for (unsigned long i = 0; i < stripLength(); ++i) {
    uint32_t hue = (0xFFFF0000ul + (i << 5) - (frame << 5)) % maxHue;
    writeLed(i, Pal.interpolateCircular(first, last, hue >> 8, static_cast<uint8_t>(hue)));
  }
}

void StrobeAnimation::draw(unsigned long frame) {
  writeColor(frame == 0 ? CRGB::Red : (frame == 1 ? CRGB::Blue : CRGB::Green));
}
