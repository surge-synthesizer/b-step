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

#ifndef __JUCE_HEADER_95878E45237598F4__
#define __JUCE_HEADER_95878E45237598F4__

#include "App.h"
#include "UiColumnWrapper.h"
#include "_H_UiElements.h"

//==============================================================================

class UiLeftsideLabel : public SubeditorBase
{
  public:
    //==============================================================================
    UiLeftsideLabel();
    ~UiLeftsideLabel();

    //==============================================================================
  public:
    void set_text(const juce::String &text_) override;
    void on_style_set(AppStyle *const style_) override;

    std::uint32_t last_painted_bg;

    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_) override;

    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    UiLabel label;

    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiLeftsideLabel)
};

#endif // __JUCE_HEADER_95878E45237598F4__
