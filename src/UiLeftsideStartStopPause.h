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

#ifndef __JUCE_HEADER_F22A8E5894AEDD70__
#define __JUCE_HEADER_F22A8E5894AEDD70__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "Controller.h"
#include "UiColumnWrapper.h"
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiLeftsideStartStopPause : public SubeditorBase
{
  public:
    //==============================================================================
    UiLeftsideStartStopPause();
    ~UiLeftsideStartStopPause();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
  public:
    void set_controllers(MONO_Controller *start_, MONO_Controller *pause_, MONO_Controller *stop_)
    {
        button_play->set_controller(start_);
        button_pause->set_controller(pause_);
        button_stop->set_controller(stop_);
    }
    void init_styles(AppInstanceStore *const store_)
    {
        if (!bstepIsStandalone)
        {
            button_play->set_style(store_->style_global_area_stop.get());
            button_pause->set_style(store_->style_global_area_stop.get());
            button_stop->set_style(store_->style_global_area_stop.get());
        }
        else
        {
            button_play->set_style(store_->style_global_area_chord.get());
            button_pause->set_style(store_->style_global_area_octave.get());
            button_stop->set_style(store_->style_global_area_stop.get());
        }
    }

    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_) override;
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ModelBase> button_play;
    std::unique_ptr<ModelBase> button_pause;
    std::unique_ptr<ModelBase> button_stop;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiLeftsideStartStopPause)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_F22A8E5894AEDD70__
