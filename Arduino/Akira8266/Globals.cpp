#include "Globals.h"

int FastLedFps::delay(int ms) {
  FastLED.delay(ms);
  return 0;
}

FastLedFps Fps;
LedStrip Strip;
Animation::Shader Shader(&Strip);
