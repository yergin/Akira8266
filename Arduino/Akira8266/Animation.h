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
    explicit Transition(LedStrip* strip) : _strip(strip) {}

    virtual void render() = 0;
    virtual void reset() = 0;
    virtual bool isFinished() const = 0;

  protected:
    int stripLength() const;
    uint8_t* mask();

  private:
    LedStrip* _strip;
  };

  class Shader {
  public:
    explicit Shader(LedStrip* strip);
    
    void transitionTo(Animation* animation);
    void jumpTo(Animation* animation);
    void render();

  private:
    void transitionTo(Animation* animation, Transition& transition);

    LedStrip* _strip;
    Animation* _to = 0;
    Animation* _from = 0;
    Transition& _transition;
  };
  
  explicit Animation(LedStrip* strip) : _strip(strip) {}

  void preBlend();
  void overlay();
  void overwrite();

  virtual void render() = 0;
  virtual void reset() {}
  virtual Transition& transition() const { return NULL_TRANSITION; }

protected:
  void writeLed(int led, const CRGB& color);
  void writeColor(const CRGB& color);
  int stripLength() const;

private:
  class NullTransition : public Transition {
  public:
    explicit NullTransition() : Animation::Transition(0) {}

    void render() override {}
    void reset() override {}
    bool isFinished() const override { return true; }
  };

  static NullTransition NULL_TRANSITION;

  LedStrip* _strip;
  RenderMode _mode = OVERWRITE;
};
