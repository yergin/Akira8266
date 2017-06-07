#pragma once

#include <FastLED.h>

class LedStrip;

class Animation
{
public:
  enum RenderMode {
    PRE_BLEND,
    OVERLAY,
    OVERWRITE
  };

  class Transition {
  public:
    explicit Transition(LedStrip* strip);

    virtual void render() = 0;
    virtual void reset() = 0;
    virtual bool isFinished() const;

  protected:
    int stripLength() const;
    uint8_t* mask();

  private:
    LedStrip* _strip;
  };

  class Shader {
  public:
    explicit Shader(LedStrip* strip) : _strip(strip) {}
    
    void transitionTo(Animation* animation);
    void jumpTo(Animation* animation);
    void render();

  private:
    void transitionTo(Animation* animation, Transition* transition);

    LedStrip* _strip;
    Animation* _to = 0;
    Animation* _from = 0;
    Transition* _transition = 0;
  };
  
  explicit Animation(LedStrip* strip) : _strip(strip) {}

  void preBlend();
  void overlay();
  void overwrite();

  virtual void render() = 0;
  virtual void reset() {}
  virtual Transition* transition() const { return 0; }

protected:
  void writeLed(int led, const CRGB& color);
  void writeColor(const CRGB& color);
  int stripLength() const;

private:
  LedStrip* _strip;
  RenderMode _mode = OVERWRITE;
};
