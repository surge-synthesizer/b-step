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

#ifndef __JUCE_HEADER_3F6EA32C251175BE__
#define __JUCE_HEADER_3F6EA32C251175BE__

#include "App.h"
#include "Controller.h"
#include "UiColumnWrapper.h"

//==============================================================================
class UiLeftsideModelLabel : public SubeditorBase
{
  public:
    //==============================================================================
    UiLeftsideModelLabel();
    ~UiLeftsideModelLabel();

    //==============================================================================
  private:
    juce::String _text;

  public:
    void set_text(const juce::String &text_) override;
    void on_style_set(AppStyle *const style_) override;

    void set_controller(MONO_Controller *const controller_) { model->set_controller(controller_); }

    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_) override;
    void get_controllers_for_paint_popup(
        juce::Array<MONO_Controller *> &controllers_with_popup_) override;
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    //==============================================================================
    std::unique_ptr<ModelBase> model;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiLeftsideModelLabel)
};

#endif // __JUCE_HEADER_3F6EA32C251175BE__
