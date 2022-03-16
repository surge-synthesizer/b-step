#ifndef __UI_BASE_H__
#define __UI_BASE_H__

#include "App.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class MONO_Controller;
class ModelBase;
class AppStyle;
class UIBase
{
    friend class ModelBase;

  protected:
    MONO_Controller *_controller;
    ModelBase *_model;
    String _text;

  private: // THIS CAN BE USED BY MODEL
    void set_controller(MONO_Controller *const controller_, ModelBase *model_);
    virtual void resized(int, int) {}
    virtual Component *get_top_level_component() = 0;
    virtual void *get_top_level_impl() = 0;
    virtual void cache_paint(Graphics &g_, uint32 background_colour_) = 0;

    virtual bool refresh_foreground() { return false; };

  protected:
    UIBase();

  public:
    virtual ~UIBase();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIBase)
};

#endif // __UI_BASE_H__
