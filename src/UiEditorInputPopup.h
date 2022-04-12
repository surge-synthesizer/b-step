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

#ifndef JUCE_HEADER_606E9AAF0379D62A_
#define JUCE_HEADER_606E9AAF0379D62A_

#include "App.h"

class UiEditor;

// TODO RENAME CLASS, ISNT A UI THING ANYMORE
class UiEditorInputPopup
{
  public:
    UiEditorInputPopup();
    ~UiEditorInputPopup();

  private:
    UiEditor *parent_editor;
    juce::TextEditor *captured_editor;

    void capture_editor(juce::TextEditor *source_);
    void release_editor();

  public:
    void refresh_ui();

  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorInputPopup)
};
#endif