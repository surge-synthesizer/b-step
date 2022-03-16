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

#ifndef __JUCE_HEADER_BCB71CADC7231BAE__
#define __JUCE_HEADER_BCB71CADC7231BAE__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiNotificationAnimation  : public Component,
    public Timer
{
public:
    //==============================================================================
    UiNotificationAnimation ();
    ~UiNotificationAnimation();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
private:
    int alpha;
    bool is_rising;
    Colour root_color;
    void timerCallback();

public:
    void set_text_and_run( const char* text_, int state_ /* 0=fail,1=ok,2=neutral*/ );
    void set_text_and_run( String& text_, int state_ /* 0=fail,1=ok,2=neutral*/ );

private:
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> text;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UiNotificationAnimation)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_BCB71CADC7231BAE__
