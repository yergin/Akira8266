#pragma once

class FpsProfiler {
public:
  FpsProfiler() {}
  
  FpsProfiler(int targetFps) { setTargetFps(targetFps); }

  virtual ~FpsProfiler() {}

  void setTargetFps(int fps);
  void setFrameSlipThreshold(int frames);
  void wait();
  void reset();
  
  int getFps(bool clearDirty);
  int getTotalUsage(bool clearDirty);
  int getBackgroundUsage(bool clearDirty);

  bool isDirty() const { return _isDirty; }

protected:
  virtual void delay(int ms);
  
  void addBackgroundProcessTime(int ms);

private:
  static constexpr unsigned long ONE_SECOND = 1000ul;

  unsigned long trackDelta(unsigned long t);

  unsigned long _targetPeriod = 0;
  unsigned long _lastFrameTarget = 0;
  int _targetFps = 0;
  int _fps = 0;
  int _frameCount = 0;
  int _frameSlipThreshold = 5;
  unsigned long _lastReportTarget = 0;
  unsigned long _totalProcessTime = 0;
  unsigned long _backgroundProcessTime = 0;
  int _totalProcessPercentage = 0;
  int _backgroundProcessPercentage = 0;
  bool _isDirty = false;
};
