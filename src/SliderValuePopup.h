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

#ifndef __JUCE_HEADER_D1021F64E2F7918__
#define __JUCE_HEADER_D1021F64E2F7918__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
class ModelBase;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SliderValuePopup  : public Component
{
public:
    //==============================================================================
    SliderValuePopup (const ModelBase*const model_);
    ~SliderValuePopup();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
private:
    String _text;
    const ModelBase*const _model;
public:
    void set_text( String& value_ );
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderValuePopup)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_D1021F64E2F7918__
