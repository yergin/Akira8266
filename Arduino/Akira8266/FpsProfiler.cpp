#include "FpsProfiler.h"

#include <Arduino.h>

void FpsProfiler::setTargetFps(int fps) {
  _targetFps = fps;
  _targetPeriod = ONE_SECOND / fps;
  reset();
}

void FpsProfiler::reset() {
  _lastFrameTarget = millis();
  _lastReportTarget = _lastFrameTarget;
  _frameCount = 0;
  _fps = 0;
  _totalProcessTime = 0;
  _totalProcessPercentage = 0;
  _backgroundProcessTime = 0;
  _backgroundProcessPercentage = 0;
  _isDirty = false;
}

void FpsProfiler::wait() {
  unsigned long delta = trackDelta(millis());
  if (delta >= _targetPeriod) {
    delay(0);
  }
  else {
    _backgroundProcessTime += delay(_targetPeriod - delta);
  }
}

int FpsProfiler::getFps(bool clearDirty) {
  if (clearDirty) {
    _isDirty = false;
  }
  return _fps;
}

int FpsProfiler::getTotalUsage(bool clearDirty) {
  if (clearDirty) {
    _isDirty = false;
  }
  return _totalProcessPercentage;
}

int FpsProfiler::getBackgroundUsage(bool clearDirty) {
  if (clearDirty) {
    _isDirty = false;
  }
  return _backgroundProcessPercentage;
}

int FpsProfiler::delay(int ms) {
  ::delay(ms);
  return 0;
}

unsigned long FpsProfiler::trackDelta(unsigned long ms) {
  unsigned long frameDelta = ms - _lastFrameTarget;
  unsigned long reportDelta = ms - _lastReportTarget;

  _totalProcessTime += frameDelta;
  _frameCount++;

  if (reportDelta >= ONE_SECOND) {
    _totalProcessPercentage = static_cast<int>((_totalProcessTime * 100 - 1) / ONE_SECOND + 1);
    _totalProcessTime = 0;
    _backgroundProcessPercentage = static_cast<int>((_backgroundProcessTime * 100 - 1) / ONE_SECOND + 1);
    _backgroundProcessTime = 0;
    _fps = _frameCount;
    _frameCount = 0;
    _lastReportTarget += ONE_SECOND;
    _isDirty = true;
  }

  // Allow the frame rate to slip if we are behind by 'frameSlipThreshold' frames.
  if (frameDelta > _frameSlipThreshold * _targetPeriod) {
    _lastFrameTarget = millis();
  }

  _lastFrameTarget += _targetPeriod;

  return frameDelta;
}
