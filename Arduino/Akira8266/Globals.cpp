#include "Globals.h"

#include "Config.h"
#include "FixedLengthLedStrip.h"

class FastLedFps : public FpsProfiler {
public:
  FastLedFps() : FpsProfiler(FPS) {}

protected:
  void delay(int ms) { FastLED.delay(ms); }
} FpsGlobalInstance;

class FastLedStrip : public FixedLengthLedStrip {
public:
  FastLedStrip() : FixedLengthLedStrip(LED_STRIP_COUNT) {
    FastLED.addLeds<APA102, LED_STRIP_DATA_PIN, LED_STRIP_CLOCK_PIN, BGR, DATA_RATE_MHZ(LED_STRIP_MHZ)>(_buffer, LED_STRIP_COUNT);
  }
} StripGlobalInstance;

FpsProfiler& Fps = FpsGlobalInstance;
LedStrip& Strip = StripGlobalInstance;
Animation::Shader Shader(&StripGlobalInstance);
