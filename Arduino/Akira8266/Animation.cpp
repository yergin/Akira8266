#include "Animation.h"

#include "LedStrip.h"

int Animation::Transition::stripLength() const {
  return _strip->count();
}

uint8_t* Animation::Transition::mask() {
  return _strip->mask();
}

void Animation::Shader::jumpTo(Animation* animation) {
  transitionTo(animation, 0);
}

void Animation::Shader::transitionTo(Animation* animation) {
  transitionTo(animation, animation ? animation->transition() : 0);
}

void Animation::Shader::transitionTo(Animation* animation, Transition* transition) {
  if (_from) {
    delete _from;
  }

  _from = _to;
  _to = animation;
  _transition = transition;

  if (_transition) {
    _transition->reset();
  }
}

void Animation::Shader::render() {
  if (_transition) {
    _transition->render();
  }

  if (_transition && !_transition->isFinished()) {
    if (_from) {
      _from->preBlend();
    }

    if (_to) {
      _to->overlay();
    }
  }
  else if (_to) {
    _to->overwrite();
  }
}

void Animation::preBlend() {
  _mode = PRE_BLEND;
  render();
}

void Animation::overlay() {
  _mode = OVERLAY;
  render();
}

void Animation::overwrite() {
  _mode = OVERWRITE;
  render();
}

int Animation::stripLength() const {
  return _strip->count();
}


void Animation::writeLed(int led, const CRGB& color) {
  switch (_mode) {
    case PRE_BLEND:
      _strip->preBlendLed(led, color);
      break;

    case OVERLAY:
      _strip->overlayLed(led, color);
      break;

    case OVERWRITE:
      _strip->overwriteLed(led, color);
  }
}

void Animation::writeColor(const CRGB& color) {
  switch (_mode) {
    case PRE_BLEND:
      for (int i = 0; i < _strip->count(); ++i) {
        _strip->preBlendLed(i, color);
      }
      break;

    case OVERLAY:
      for (int i = 0; i < _strip->count(); ++i) {
        _strip->overlayLed(i, color);
      }
      break;

    case OVERWRITE:
      for (int i = 0; i < _strip->count(); ++i) {
        _strip->overwriteLed(i, color);
      }
  }
}

