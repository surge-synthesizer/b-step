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

#ifndef __JUCE_HEADER_D69BC9044BC344F4__
#define __JUCE_HEADER_D69BC9044BC344F4__

#include "App.h"
#include "UIEditorToolbar.h"
#include <juce_audio_utils/juce_audio_utils.h>

class AppInstanceStore;

class UiEditorKeyboard : public UiEditor
{
  public:
    //==============================================================================
    UiEditorKeyboard(AppInstanceStore *const app_instance_store_);
    ~UiEditorKeyboard();

    //==============================================================================
    AppInstanceStore *const _app_instance_store;

    void paint(juce::Graphics &g);
    void resized();

  private:
    //==============================================================================
    std::unique_ptr<juce::MidiKeyboardComponent> keyboard;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorKeyboard)
};

#endif // __JUCE_HEADER_D69BC9044BC344F4__
