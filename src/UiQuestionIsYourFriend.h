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

#ifndef __JUCE_HEADER_7E5BDFC8AB7B8312__
#define __JUCE_HEADER_7E5BDFC8AB7B8312__

#include "App.h"
#include "UIEditorToolbar.h"

class UiQuestionIsYourFriend : public UiEditor, public juce::Button::Listener
{
  public:
    //==============================================================================
    UiQuestionIsYourFriend(AppInstanceStore *const app_instance_store_);
    ~UiQuestionIsYourFriend();

    //==============================================================================
    AppInstanceStore *const _app_instance_store;

    void on_close_clicked() override;

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;

    static const char *question_svg;
    static const int question_svgSize;

  private:
    //==============================================================================
    std::unique_ptr<juce::Label> label;
    std::unique_ptr<juce::TextButton> save;
    std::unique_ptr<juce::TextEditor> textEditor;
    std::unique_ptr<juce::Drawable> drawable1;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiQuestionIsYourFriend)
};

#endif // __JUCE_HEADER_7E5BDFC8AB7B8312__
