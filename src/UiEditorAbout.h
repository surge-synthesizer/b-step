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
#ifdef DEVELOPMENT
class Parser;
#endif

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
#ifdef DEVELOPMENT
  private:
    ScopedPointer<Parser> debug_parser;
    bool is_on_shutdown;

  public:
    void print_debug(String text);
#endif
  private:
    juce::URL url_facebook;
    juce::URL url_youtube;
    juce::URL url_digg;
    juce::URL url_deli;
    juce::URL url_twitter;
    juce::URL url_pinit;
    juce::URL url_google;

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;

    // Binary resources:
    static const char *b_logo_png;
    static const int b_logo_pngSize;
    static const char *vst_logo_100x_png;
    static const int vst_logo_100x_pngSize;
    static const char *au_logo_100x_png;
    static const int au_logo_100x_pngSize;
    static const char *aboutbox_png;
    static const int aboutbox_pngSize;

  private:
    //==============================================================================
    std::unique_ptr<juce::ImageButton> au_button;
    std::unique_ptr<juce::ImageButton> vst_button;
    std::unique_ptr<juce::HyperlinkButton> hyperlinkButton8;
    std::unique_ptr<juce::HyperlinkButton> video_1;
    std::unique_ptr<juce::HyperlinkButton> video_2;
    std::unique_ptr<juce::HyperlinkButton> video_3;
    std::unique_ptr<juce::HyperlinkButton> video_4;
    std::unique_ptr<juce::HyperlinkButton> video_5;
    std::unique_ptr<juce::TextEditor> debug_out;
    std::unique_ptr<UiEditorToolbar> toolbar;
    std::unique_ptr<juce::ImageButton> open_debug;

    std::unique_ptr<juce::Label> buildInfo;

    juce::Image cachedImage_aboutbox_png;
    juce::Image cachedImage_b_logo_png;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorAbout)
};

#endif // __JUCE_HEADER_F24D3F196EED8940__
