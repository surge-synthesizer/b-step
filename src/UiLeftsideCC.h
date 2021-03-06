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

#ifndef __JUCE_HEADER_E48326D9C43DBCF0__
#define __JUCE_HEADER_E48326D9C43DBCF0__

#include "App.h"
#include "Controller.h"
#include "UiColumnWrapper.h"
#include "MIDICC.h"

class UiLabel;
class UiLeftsideCC : public SubeditorBase
{
  public:
    //==============================================================================
    UiLeftsideCC();
    ~UiLeftsideCC();

    //==============================================================================
  public:
    void on_style_set(AppStyle *const style_) override;

    void set_cc_chooser_controller(MONO_Controller *const controller_)
    {
        cc_type->set_controller(controller_);
    }

    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_) override;

    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    MIDICC midi_cc;

    //==============================================================================
    std::unique_ptr<ModelBase> cc_type;
    std::unique_ptr<UiLabel> cc_label;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiLeftsideCC)
};

#endif // __JUCE_HEADER_E48326D9C43DBCF0__
