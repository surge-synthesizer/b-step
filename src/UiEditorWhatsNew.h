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

#ifndef __JUCE_HEADER_3018A0895B3D780C__
#define __JUCE_HEADER_3018A0895B3D780C__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"

class AppInstanceStore;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorWhatsNew : public UiEditor, public juce::Timer, public juce::Button::Listener
{
  public:
    //==============================================================================
    UiEditorWhatsNew(AppInstanceStore *const app_instance_store_);
    ~UiEditorWhatsNew();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;
    void refresh_ui();
    void timerCallback();

  private:
    //[/UserMethods]

    void paint(juce::Graphics &g);
    void resized();
    void buttonClicked(juce::Button *buttonThatWasClicked);

    // Binary resources:
    static const char *demobg_png2;
    static const int demobg_png2Size;
    static const char *colourstyles_png;
    static const int colourstyles_pngSize;
    static const char *filemanager_png;
    static const int filemanager_pngSize;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> label22;
    std::unique_ptr<juce::ToggleButton> dont_show_again;
    std::unique_ptr<juce::Label> label9;
    std::unique_ptr<juce::Label> label2;
    std::unique_ptr<juce::TextButton> close;
    std::unique_ptr<juce::Label> label3;
    std::unique_ptr<juce::Label> label4;
    std::unique_ptr<juce::Label> label5;
    std::unique_ptr<juce::Label> label6;
    std::unique_ptr<juce::Label> label7;
    std::unique_ptr<juce::Label> label10;
    std::unique_ptr<juce::Label> label11;
    std::unique_ptr<juce::TextButton> open_styler;
    std::unique_ptr<juce::Label> label12;
    std::unique_ptr<juce::Label> label13;
    std::unique_ptr<juce::Label> label8;
    std::unique_ptr<juce::TextButton> open_filemanager;
    std::unique_ptr<juce::Label> label15;
    std::unique_ptr<juce::Label> label16;
    std::unique_ptr<juce::Label> label17;
    std::unique_ptr<juce::Label> label18;
    std::unique_ptr<juce::Label> label19;
    std::unique_ptr<juce::Label> label20;
    std::unique_ptr<juce::TextButton> open_log;
    std::unique_ptr<juce::Label> label21;
    std::unique_ptr<juce::Label> label14;
    std::unique_ptr<juce::Label> label23;
    juce::Image cachedImage_demobg_png2;
    juce::Image cachedImage_colourstyles_png;
    juce::Image cachedImage_filemanager_png;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorWhatsNew)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_3018A0895B3D780C__
