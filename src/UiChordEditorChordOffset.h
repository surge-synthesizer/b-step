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

#ifndef __JUCE_HEADER_49E9D35AC14A2530__
#define __JUCE_HEADER_49E9D35AC14A2530__

#include "App.h"

class ModelBase;
class UiLabel;
class AppInstanceStore;

class UiChordEditorChordOffset : public juce::Component
{
  public:
    //==============================================================================
    UiChordEditorChordOffset(AppInstanceStore *const app_instance_store_, std::uint8_t chord_id_);
    ~UiChordEditorChordOffset();

    //==============================================================================
    AppInstanceStore *const _app_instance_store;

    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_);
    std::int8_t last_refreshed_offset_value;
    bool is_your_value_changed_since_last_request();

    void paint(juce::Graphics &g);
    void resized();

  private:
    //==============================================================================
    std::unique_ptr<UiLabel> label;
    std::unique_ptr<ModelBase> slider;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiChordEditorChordOffset)
};

#endif // __JUCE_HEADER_49E9D35AC14A2530__
