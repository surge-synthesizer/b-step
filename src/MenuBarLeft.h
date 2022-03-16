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

#ifndef __JUCE_HEADER_A2547B656C4F7F86__
#define __JUCE_HEADER_A2547B656C4F7F86__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"

class AppInstanceStore;
class GstepAudioProcessorEditor;

class ModelBase;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MenuBarLeft  : public Component,
                    public Button::Listener
{
public:
    //==============================================================================
    MenuBarLeft (AppInstanceStore*const app_instance_store_, GstepAudioProcessorEditor*const main_window_);
    ~MenuBarLeft();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore*const _app_instance_store;
    GstepAudioProcessorEditor*const _main_window;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
public:
    void refresh_ui( Array< Component* >& components_to_repaint_ );
private:
    void set_user_mode();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* _5stars_svg;
    static const int _5stars_svgSize;
    static const char* _3stars_svg;
    static const int _3stars_svgSize;
    static const char* _1stars_svg;
    static const int _1stars_svgSize;
    static const char* _5starson_svg;
    static const int _5starson_svgSize;
    static const char* _3starson_svg;
    static const int _3starson_svgSize;
    static const char* _1starson_svg;
    static const int _1starson_svgSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ModelBase> button_layer_1;
    ScopedPointer<ModelBase> button_layer_2;
    ScopedPointer<ModelBase> button_layer_3;
    ScopedPointer<ModelBase> button_layer_4;
    ScopedPointer<ModelBase> button_layer_5;
    ScopedPointer<ModelBase> button_layer_6;
    ScopedPointer<ModelBase> button_layer_7;
    ScopedPointer<ImageButton> pb_lite_mode;
    ScopedPointer<ImageButton> pb_semi_mode;
    ScopedPointer<ImageButton> pb_pro_mode;
    ScopedPointer<Drawable> drawable1;
    ScopedPointer<Drawable> drawable2;
    ScopedPointer<Drawable> drawable3;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MenuBarLeft)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_A2547B656C4F7F86__
