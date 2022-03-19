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

#ifndef __JUCE_HEADER_49E9D35AC14A2530__
#define __JUCE_HEADER_49E9D35AC14A2530__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"

class ModelBase;
class UiLabel;
class AppInstanceStore;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiChordEditorChordOffset : public juce::Component
{
  public:
    //==============================================================================
    UiChordEditorChordOffset(AppInstanceStore *const app_instance_store_, std::uint8_t chord_id_);
    ~UiChordEditorChordOffset();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;

    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_);
    std::int8_t last_refreshed_offset_value;
    bool is_your_value_changed_since_last_request();
    //[/UserMethods]

    void paint(juce::Graphics &g);
    void resized();

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<UiLabel> label;
    juce::ScopedPointer<ModelBase> slider;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiChordEditorChordOffset)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_49E9D35AC14A2530__
