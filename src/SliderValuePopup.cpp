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

//[Headers] You can add your own extra header files here...
#include "AppStyles.h"
#include "Controller.h"
//[/Headers]

#include "SliderValuePopup.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
void SliderValuePopup::set_text( String& text_ )
{
    if( _text.compare(text_) != 0 )
    {
        if( text_ == HAS_NO_TEXT_VALUE )
            _text = "";
        else
            _text = text_;
        repaint(0,0,getWidth(),getHeight());
    }
}
//[/MiscUserDefs]

//==============================================================================
SliderValuePopup::SliderValuePopup (const ModelBase*const model_)
    : _model( model_ )
{
    //[UserPreSize]
    //[/UserPreSize]

    setSize (60, 40);


    //[Constructor] You can add your own custom stuff here..
#ifdef JUCE_IOS
    setOpaque(true);
#endif
    //[/Constructor]
}

SliderValuePopup::~SliderValuePopup()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SliderValuePopup::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    g.setColour (Colour (0xff111111));
    g.fillRoundedRectangle (1.0f, 1.0f, static_cast<float> (getWidth() - 2), static_cast<float> (getHeight() - 2), 5.000f);

    if( _model )
        if( _model->get_style() )
            g.setColour (Colour(_model->get_style()->get_font_color()));

    g.drawRoundedRectangle (1.0f, 1.0f, static_cast<float> (getWidth() - 2), static_cast<float> (getHeight() - 2), 5.000f, 2.000f);

    AppStyle::paint_outline_label( g, *this, _text, _model->get_style(), Justification::centred, 0.0588f, 0.1000f, 0.8824f, 0.8000f );

    return;
    //[/UserPrePaint]

    g.setColour (Colour (0xff111111));
    g.fillRoundedRectangle (1.0f, 1.0f, static_cast<float> (getWidth() - 2), static_cast<float> (getHeight() - 2), 5.000f);

    g.setColour (Colours::yellow);
    g.drawRoundedRectangle (1.0f, 1.0f, static_cast<float> (getWidth() - 2), static_cast<float> (getHeight() - 2), 5.000f, 2.000f);

    g.setColour (Colours::yellow);
    g.setFont (Font (22.00f, Font::bold));
    g.drawText (TRANS("XXX"),
                0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f),
                Justification::centred, true);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SliderValuePopup::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SliderValuePopup" componentName=""
                 parentClasses="public Component" constructorParams="const ModelBase*const model_"
                 variableInitialisers="_model( model_ )" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="60"
                 initialHeight="40">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="1 1 2M 2M" cornerSize="5" fill="solid: ff111111" hasStroke="1"
               stroke="2, mitered, butt" strokeColour="solid: ffffff00"/>
    <TEXT pos="0 0 100% 100%" fill="solid: ffffff00" hasStroke="0" text="XXX"
          fontname="Default font" fontsize="22" bold="1" italic="0" justification="36"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
