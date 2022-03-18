/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_F24D3F196EED8940__
#define __JUCE_HEADER_F24D3F196EED8940__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"

class AppInstanceStore;
#ifdef DEVELOPMENT
class Parser;
#endif
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorAbout : public UiEditor, public juce::Button::Listener
{
  public:
    //==============================================================================
    UiEditorAbout(AppInstanceStore *const app_instance_store_);
    ~UiEditorAbout();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;

    bool is_demo;

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
    //[/UserMethods]

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
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::ImageButton> au_button;
    juce::ScopedPointer<juce::ImageButton> vst_button;
    juce::ScopedPointer<juce::HyperlinkButton> hyperlinkButton8;
    juce::ScopedPointer<juce::HyperlinkButton> video_1;
    juce::ScopedPointer<juce::HyperlinkButton> video_2;
    juce::ScopedPointer<juce::HyperlinkButton> video_3;
    juce::ScopedPointer<juce::HyperlinkButton> video_4;
    juce::ScopedPointer<juce::HyperlinkButton> video_5;
    juce::ScopedPointer<juce::TextEditor> debug_out;
    juce::ScopedPointer<UiEditorToolbar> toolbar;
    juce::ScopedPointer<juce::ImageButton> open_debug;

    std::unique_ptr<juce::Label> buildInfo;

    juce::Image cachedImage_aboutbox_png;
    juce::Image cachedImage_b_logo_png;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorAbout)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_F24D3F196EED8940__
