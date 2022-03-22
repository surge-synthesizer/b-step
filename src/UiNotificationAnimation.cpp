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
//[/Headers]

#include "UiNotificationAnimation.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
void UiNotificationAnimation::timerCallback()
{
    if (alpha >= 255)
        is_rising = false;

    if (is_rising)
        alpha += 5;
    else
        alpha -= 5;

    if (alpha <= 0)
    {
        stopTimer();
        text->setColour(juce::Label::textColourId, root_color.withAlpha(std::uint8_t(0)));
    }
    else
        text->setColour(juce::Label::textColourId, root_color.withAlpha(std::uint8_t(alpha)));
}

void UiNotificationAnimation::set_text_and_run(const char *text_,
                                               int state_ /* 0=fail,1=ok,2=neutral*/)
{
    juce::String text(text_);
    set_text_and_run(text, state_);
}

void UiNotificationAnimation::set_text_and_run(juce::String &text_,
                                               int state_ /* 0=fail,1=ok,2=neutral*/)
{
    stopTimer();

    alpha = 0;
    is_rising = true;

    juce::MessageManagerLock mmLock;

    root_color = state_ ? (state_ == 1 ? juce::Colours::chartreuse : juce::Colours::blue)
                        : juce::Colours::red;
    text->setColour(juce::Label::textColourId, root_color.withAlpha(std::uint8_t(0)));
    text->setText(text_, juce::dontSendNotification);

    startTimer(15);
}
//[/MiscUserDefs]

//==============================================================================
UiNotificationAnimation::UiNotificationAnimation()
{
    text = std::make_unique<juce::Label>(juce::String(), TRANS("OK"));
    addAndMakeVisible(*text);
    text->setFont(juce::Font("Oswald", 230.00f, juce::Font::bold));
    text->setJustificationType(juce::Justification::centred);
    text->setEditable(false, false, false);
    text->setColour(juce::Label::textColourId, juce::Colours::chartreuse);
    text->setColour(juce::TextEditor::textColourId, juce::Colour(0x00000000));
    text->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xff161616));
    text->setColour(juce::TextEditor::highlightColourId, juce::Colour(0x001111ee));

    //[UserPreSize]
    text->setColour(juce::Label::textColourId, juce::Colour(0x00000000));
    //[/UserPreSize]

    setSize(400, 200);

    //[Constructor] You can add your own custom stuff here..
    setInterceptsMouseClicks(false, false);
    //[/Constructor]
}

UiNotificationAnimation::~UiNotificationAnimation()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    stopTimer();
    //[/Destructor_pre]

    text = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiNotificationAnimation::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UiNotificationAnimation::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    text->setBounds(0, 0, proportionOfWidth(1.0000f), proportionOfHeight(1.0000f));
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

<JUCER_COMPONENT documentType="Component" className="UiNotificationAnimation"
                 componentName="" parentClasses="public Component, public Timer"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="400"
                 initialHeight="200">
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="" id="ea2c4041da5df62c" memberName="text" virtualName=""
         explicitFocusOrder="0" pos="0 0 100% 100%" textCol="ff7fff00"
         edTextCol="0" edBkgCol="0" hiliteCol="1111ee" labelText="OK"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="230" bold="1" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
