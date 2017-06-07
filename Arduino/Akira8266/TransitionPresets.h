#pragma once

#include "Animation.h"
#include "Globals.h"

class LedStrip;

class FixedLengthTransition : public Animation::Transition {
public:
  explicit FixedLengthTransition(unsigned long duration)
      : Animation::Transition(&Strip), _duration(duration)
  {}

  void render() override { render(_frame++); }
  void reset() { _frame = 0; }
  bool isFinished() const { return _frame >= _duration; }

protected:
  virtual void render(unsigned long frame) = 0;

private:
  unsigned long _frame = 0;
  const unsigned long _duration;
};

class Blinds : public FixedLengthTransition
{
public:
  Blinds() : FixedLengthTransition(40) {}
  
protected:
  void render(unsigned long frame) override;
};
