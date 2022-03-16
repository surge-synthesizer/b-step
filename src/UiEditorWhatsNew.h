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
class UiEditorWhatsNew  : public UiEditor,
    public Timer,
    public Button::Listener
{
public:
    //==============================================================================
    UiEditorWhatsNew (AppInstanceStore* const app_instance_store_);
    ~UiEditorWhatsNew();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore*const _app_instance_store;
    void refresh_ui();
    void timerCallback();
private:
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* demobg_png2;
    static const int demobg_png2Size;
    static const char* colourstyles_png;
    static const int colourstyles_pngSize;
    static const char* filemanager_png;
    static const int filemanager_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label22;
    ScopedPointer<ToggleButton> dont_show_again;
    ScopedPointer<Label> label9;
    ScopedPointer<Label> label2;
    ScopedPointer<TextButton> close;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<Label> label5;
    ScopedPointer<Label> label6;
    ScopedPointer<Label> label7;
    ScopedPointer<Label> label10;
    ScopedPointer<Label> label11;
    ScopedPointer<TextButton> open_styler;
    ScopedPointer<Label> label12;
    ScopedPointer<Label> label13;
    ScopedPointer<Label> label8;
    ScopedPointer<TextButton> open_filemanager;
    ScopedPointer<Label> label15;
    ScopedPointer<Label> label16;
    ScopedPointer<Label> label17;
    ScopedPointer<Label> label18;
    ScopedPointer<Label> label19;
    ScopedPointer<Label> label20;
    ScopedPointer<TextButton> open_log;
    ScopedPointer<Label> label21;
    ScopedPointer<Label> label14;
    ScopedPointer<Label> label23;
    Image cachedImage_demobg_png2;
    Image cachedImage_colourstyles_png;
    Image cachedImage_filemanager_png;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UiEditorWhatsNew)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_3018A0895B3D780C__
