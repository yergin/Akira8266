#pragma once

#include "Config.h"

#include "LedStrip.h"
#include "FpsProfiler.h"
#include "Animation.h"

class FastLedFps : public FpsProfiler {
public:
  FastLedFps() : FpsProfiler(FPS) {}

protected:
  int delay(int ms);
};

extern FastLedFps Fps;
extern LedStrip Strip;
extern Animation::Shader Shader;
