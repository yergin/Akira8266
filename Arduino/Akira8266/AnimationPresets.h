#pragma once

#include "Animation.h"
#include "Globals.h"

enum ColorPreset {
  PRESET_COL_WHITE = 0,
  PRESET_COL_PINK,
  PRESET_COL_RED,
  PRESET_COL_ORANGE,
  PRESET_COL_YELLOW,
  PRESET_COL_LIME,
  PRESET_COL_GREEN,
  PRESET_COL_AQUA,
  PRESET_COL_BLUE,
  PRESET_COL_VIOLET,
  PRESET_COL_FUCHSIA,
  PRESET_COL_MAGENTA,
  PRESET_COL_RAINBOW_OR_BLACK,
  PRESET_COL_COUNT
};

constexpr uint32_t Colors[] = { 0x5f5f5f, // white
                                0xff1f1f, // pink
                                0xff0000, // red
                                0xff2700, // orange
                                0xdf7700, // yellow
                                0x8fcf00, // lime
                                0x00ff00, // green
                                0x00cf6f, // aqua
                                0x0000ff, // blue
                                0x3f00ff, // violet
                                0x8f008f, // fuchsia
                                0xcf005f, // magenta
                                0x000000, // rainbow / black
                              };

class LoopingAnimation : public Animation {
public:
  LoopingAnimation() : Animation(&Strip) {}

  void render() override;
  void reset() override { _frame = 0; }

protected:
  virtual void draw(unsigned long frame) = 0;
  virtual unsigned long duration() const { return 0; }

private:
  unsigned long _frame = 0;
};

class WaveAnimation : public LoopingAnimation {
protected:
  void draw(unsigned long frame) override;
};

class StrobeAnimation : public LoopingAnimation
{
protected:
  void draw(unsigned long frame) override;
  unsigned long duration() const override { return 6; }
};

