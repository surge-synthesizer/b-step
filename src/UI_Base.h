/*
** B-Step is Free and Open Source Software
**
** B-Step is made available under the Gnu General Public License, v3.0
** https://www.gnu.org/licenses/gpl-3.0.en.html; The authors of the code
** reserve the right to re-license their contributions under the MIT license in the
** future at the discretion of the project maintainers.
**
** Copyright 2014-2022 by various individuals as described by the git transaction log
**
** All source at: https://github.com/surge-synthesizer/b-step.git
**
** B-Step was a commercial product from 2014-2022, with copyright and ownership
** in that period held by Thomas Arndt at Monoplugs. Thomas made B-Step
** open source in March 2022.
*/

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
    juce::String _text;

  private: // THIS CAN BE USED BY MODEL
    void set_controller(MONO_Controller *const controller_, ModelBase *model_);
    virtual void resized(int, int) {}
    virtual juce::Component *get_top_level_component() = 0;
    virtual void *get_top_level_impl() = 0;
    virtual void cache_paint(juce::Graphics &g_, std::uint32_t background_colour_) = 0;

    virtual bool refresh_foreground() { return false; };

  protected:
    UIBase();

  public:
    virtual ~UIBase();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIBase)
};

#endif // __UI_BASE_H__
