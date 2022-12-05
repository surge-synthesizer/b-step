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

#ifndef __JUCE_HEADER_F24D3F196EED8940__
#define __JUCE_HEADER_F24D3F196EED8940__

#include "App.h"
#include "UIEditorToolbar.h"

class AppInstanceStore;

class UiEditorAbout : public UiEditor, public juce::Button::Listener
{
  public:
    //==============================================================================
    UiEditorAbout(AppInstanceStore *const app_instance_store_);
    ~UiEditorAbout();

    //==============================================================================
    AppInstanceStore *const _app_instance_store;

  public:
    void on_close_clicked() override;

  private:
    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;

    // Binary resources:
    static const char *b_logo_png;
    static const int b_logo_pngSize;

  private:
    //==============================================================================
    std::unique_ptr<juce::HyperlinkButton> bstep_gh_link;
    std::unique_ptr<juce::HyperlinkButton> link_to_manual;
    std::unique_ptr<juce::HyperlinkButton> video_4;
    std::unique_ptr<UiEditorToolbar> toolbar;
    struct AboutInfo
    {
        std::string value;
    };
    std::vector<AboutInfo> info;
    std::unique_ptr<juce::TextButton> copy_button;
    std::unique_ptr<juce::Label> buildInfo;

    juce::Image cachedImage_b_logo_png;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorAbout)
};

#endif // __JUCE_HEADER_F24D3F196EED8940__
