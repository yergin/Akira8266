#include "Animation.h"

#include "LedStrip.h"

int Animation::Transition::stripLength() const {
  return _strip->length();
}

uint8_t* Animation::Transition::mask() {
  return _strip->mask();
}

Animation::Shader::Shader(LedStrip* strip)
    : _strip(strip), _transition(NULL_TRANSITION) {}

void Animation::Shader::jumpTo(Animation* animation) {
  transitionTo(animation, NULL_TRANSITION);
}

void Animation::Shader::transitionTo(Animation* animation) {
  transitionTo(animation, animation ? animation->transition() : NULL_TRANSITION);
}

void Animation::Shader::transitionTo(Animation* animation, Transition& transition) {
  if (_from) {
    delete _from;
  }

  _transition = transition;
  _transition.reset();

  if (_transition.isFinished()) {
    delete _to;
    _to = 0;
  }

  _from = _to;
  _to = animation;
}

void Animation::Shader::render() {
  if (!_transition.isFinished()) {
    _transition.render();

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

Animation::NullTransition Animation::NULL_TRANSITION;

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
  return _strip->length();
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
      for (int i = 0; i < _strip->length(); ++i) {
        _strip->preBlendLed(i, color);
      }
      break;

    case OVERLAY:
      for (int i = 0; i < _strip->length(); ++i) {
        _strip->overlayLed(i, color);
      }
      break;

    case OVERWRITE:
      for (int i = 0; i < _strip->length(); ++i) {
        _strip->overwriteLed(i, color);
      }
  }
}

