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

#ifndef __JUCE_HEADER_FF56F54DD22FFD62__
#define __JUCE_HEADER_FF56F54DD22FFD62__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"

class ModelBase;
class UiLabel;
class AppInstanceStore;
class MONO_Controller;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiChordEditorStringOffset  : public Component
{
public:
    //==============================================================================
    UiChordEditorStringOffset (AppInstanceStore* const app_instance_store_,uint8 chord_id_, uint8 barstring_id_);
    ~UiChordEditorStringOffset();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore*const _app_instance_store;

    void refresh_ui( Array< Component* >& components_to_repaint_ );
    void get_controllers_for_paint_popup( Array< MONO_Controller* >& controllers_that_need_a_popup );

    void repaint_label();
    void set_style( AppStyle*const );
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label;
    ScopedPointer<ModelBase> slider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UiChordEditorStringOffset)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_FF56F54DD22FFD62__
