#include "Globals.h"
#include "AnimationPresets.h"

void setup() {
  SERIAL_INIT()

  FastLED.setBrightness(7);
  
  pinMode(STATUS_LED_PIN, OUTPUT);

  Shader.jumpTo(new StrobeAnimation);
}

void loop() {
  static unsigned int counter = 0;
  Fps.wait();
  Shader.render();
  FastLED.show();
  if (Fps.isDirty()) {
    SERIAL_PRINT("Usage:")
    SERIAL_PRINT(Fps.getTotalUsage(true))
    SERIAL_PRINT("% FPS:")
    SERIAL_PRINT(Fps.getFps(true))
    SERIAL_PRINTLN("/sec")
  }
}
