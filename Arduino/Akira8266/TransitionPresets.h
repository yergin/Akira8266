#pragma once

#include "Animation.h"

class LedStrip;

class Blinds : public Animation::Transition
{
public:
  Blinds(LedStrip* strip) : Animation::Transition(strip) {}

  void render() { render(_frame++); }
  void reset() { _frame = 0; }
  bool isFinished() const { return _frame >= duration(); }
  unsigned long duration() const { return 40; }
  
private:
  void render(unsigned long frame);
  
  unsigned long _frame = 0;
};
