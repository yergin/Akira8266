#include "TransitionPresets.h"

void Blinds::render(unsigned long frame) {
  for (unsigned long i = 0; i < stripLength(); ++i) {
    mask()[i] = (i % 20) <= (frame >> 1) ? 255 : 0;
  }
}
