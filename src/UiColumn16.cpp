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
//[/Headers]

#include "UiColumn16.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
void UiColumn16::refresh_ui(juce::Array<Component *> &components_to_repaint_)
{
    for (unsigned int i = 0; i != 16; ++i)
    {
        models.getUnchecked(i)->get_components_to_repaint(components_to_repaint_);
    }
}

void UiColumn16::get_controllers_for_paint_popup(
    juce::Array<MONO_Controller *> &controllers_with_popup_)
{
    for (unsigned int i = 0; i != 16; ++i)
    {
        models.getUnchecked(i)->get_controllers_for_paint_popup(controllers_with_popup_);
    }
}

void UiColumn16::on_style_set(AppStyle *const style_)
{
    if (style_)
        setOpaque(_style->is_wrapper_opaque());

    ModelBase *model;
    for (unsigned int i = 0; i != 16; ++i)
    {
        model = models.getUnchecked(i);
        model->set_style(style_);
    }
}
void UiColumn16::set_background_style(AppStyle *const style_)
{
    ModelBase *model;
    for (unsigned int i = 0; i != 16; ++i)
    {
        model = models.getUnchecked(i);
        model->set_background_style(style_);
    }
}

//[/MiscUserDefs]

//==============================================================================
UiColumn16::UiColumn16()
{
    addAndMakeVisible(elem_0 = new ModelBase());

    addAndMakeVisible(elem_1 = new ModelBase());

    addAndMakeVisible(elem_2 = new ModelBase());

    addAndMakeVisible(elem_3 = new ModelBase());

    addAndMakeVisible(elem_4 = new ModelBase());

    addAndMakeVisible(elem_5 = new ModelBase());

    addAndMakeVisible(elem_6 = new ModelBase());

    addAndMakeVisible(elem_7 = new ModelBase());

    addAndMakeVisible(elem_8 = new ModelBase());

    addAndMakeVisible(elem_9 = new ModelBase());

    addAndMakeVisible(elem_10 = new ModelBase());

    addAndMakeVisible(elem_11 = new ModelBase());

    addAndMakeVisible(elem_12 = new ModelBase());

    addAndMakeVisible(elem_13 = new ModelBase());

    addAndMakeVisible(elem_14 = new ModelBase());

    addAndMakeVisible(elem_15 = new ModelBase());

    //[UserPreSize]
    _style = nullptr;

    const_cast<juce::Array<ModelBase *> &>(models).add(elem_0.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_1.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_2.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_3.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_4.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_5.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_6.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_7.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_8.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_9.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_10.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_11.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_12.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_13.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_14.get());
    const_cast<juce::Array<ModelBase *> &>(models).add(elem_15.get());
    const_cast<juce::Array<ModelBase *> &>(models).minimiseStorageOverheads();

#ifdef DO_NEVER_DEFINE_THIS
    //[/UserPreSize]

    setSize(815, 50);

    //[Constructor] You can add your own custom stuff here..
#endif
    //[/Constructor]
}

UiColumn16::~UiColumn16()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    elem_0 = nullptr;
    elem_1 = nullptr;
    elem_2 = nullptr;
    elem_3 = nullptr;
    elem_4 = nullptr;
    elem_5 = nullptr;
    elem_6 = nullptr;
    elem_7 = nullptr;
    elem_8 = nullptr;
    elem_9 = nullptr;
    elem_10 = nullptr;
    elem_11 = nullptr;
    elem_12 = nullptr;
    elem_13 = nullptr;
    elem_14 = nullptr;
    elem_15 = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiColumn16::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    if (_style)
        if (_style->is_wrapper_opaque())
            g.fillAll(juce::Colour(_style->get_foreground_color()));
    return;
    //[/UserPrePaint]

    g.fillAll(juce::Colours::white);

    //[UserPaint] Add your own custom painting code here..

    //[/UserPaint]
}

void UiColumn16::resized()
{
    //[UserPreResized] Add your own custom resize handling here..
#if !JUCE_IOS
    //[/UserPrePaint]
    elem_0->setBounds(proportionOfWidth(0.0061f), proportionOfHeight(0.1000f),
                      proportionOfWidth(0.0491f), proportionOfHeight(0.8000f));
    elem_1->setBounds(proportionOfWidth(0.0675f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_2->setBounds(proportionOfWidth(0.1288f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_3->setBounds(proportionOfWidth(0.1902f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_4->setBounds(proportionOfWidth(0.2577f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_5->setBounds(proportionOfWidth(0.3190f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_6->setBounds(proportionOfWidth(0.3804f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_7->setBounds(proportionOfWidth(0.4417f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_8->setBounds(proportionOfWidth(0.5092f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_9->setBounds(proportionOfWidth(0.5706f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_10->setBounds(proportionOfWidth(0.6319f),
                       (proportionOfHeight(0.1000f)) +
                           juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                       juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                       juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_11->setBounds(proportionOfWidth(0.6933f),
                       (proportionOfHeight(0.1000f)) +
                           juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                       juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                       juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_12->setBounds(proportionOfWidth(0.7607f),
                       (proportionOfHeight(0.1000f)) +
                           juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                       juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                       juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_13->setBounds(proportionOfWidth(0.8221f),
                       (proportionOfHeight(0.1000f)) +
                           juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                       juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                       juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_14->setBounds(proportionOfWidth(0.8834f),
                       (proportionOfHeight(0.1000f)) +
                           juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                       juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                       juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_15->setBounds(proportionOfWidth(0.9448f),
                       (proportionOfHeight(0.1000f)) +
                           juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                       juce::roundToInt((proportionOfWidth(0.0491f)) * 1.0000f),
                       juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));

    //[UserResized] Add your own custom resize handling here..
#else
    elem_0->setBounds(proportionOfWidth(0.0061f), proportionOfHeight(0.1000f),
                      proportionOfWidth(0.0531f), proportionOfHeight(0.8000f));
    elem_1->setBounds(proportionOfWidth(0.0675f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_2->setBounds(proportionOfWidth(0.1288f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_3->setBounds(proportionOfWidth(0.1902f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_4->setBounds(proportionOfWidth(0.2577f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_5->setBounds(proportionOfWidth(0.3190f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_6->setBounds(proportionOfWidth(0.3804f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_7->setBounds(proportionOfWidth(0.4417f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_8->setBounds(proportionOfWidth(0.5092f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_9->setBounds(proportionOfWidth(0.5706f),
                      (proportionOfHeight(0.1000f)) +
                          juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                      juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                      juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_10->setBounds(proportionOfWidth(0.6319f),
                       (proportionOfHeight(0.1000f)) +
                           juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                       juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                       juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_11->setBounds(proportionOfWidth(0.6933f),
                       (proportionOfHeight(0.1000f)) +
                           juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                       juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                       juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_12->setBounds(proportionOfWidth(0.7607f),
                       (proportionOfHeight(0.1000f)) +
                           juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                       juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                       juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_13->setBounds(proportionOfWidth(0.8221f),
                       (proportionOfHeight(0.1000f)) +
                           juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                       juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                       juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_14->setBounds(proportionOfWidth(0.8834f),
                       (proportionOfHeight(0.1000f)) +
                           juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                       juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                       juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
    elem_15->setBounds(proportionOfWidth(0.9448f),
                       (proportionOfHeight(0.1000f)) +
                           juce::roundToInt((proportionOfHeight(0.8000f)) * 0.0000f),
                       juce::roundToInt((proportionOfWidth(0.0531f)) * 1.0000f),
                       juce::roundToInt((proportionOfHeight(0.8000f)) * 1.0000f));
#endif
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

<JUCER_COMPONENT documentType="Component" className="UiColumn16" componentName=""
                 parentClasses="public SubeditorBase" constructorParams="" variableInitialisers=""
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="815" initialHeight="50">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="" id="7df349b1fad40eac" memberName="elem_0" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="0.613% 10% 4.908% 80%" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="" id="21a109360ea83a21" memberName="elem_1" virtualName=""
                    explicitFocusOrder="0" pos="6.748% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="d000ffe9140d00d5" memberName="elem_2" virtualName=""
                    explicitFocusOrder="0" pos="12.883% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="5d131475b5fc772a" memberName="elem_3" virtualName=""
                    explicitFocusOrder="0" pos="19.018% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="8a1caebae295d6a2" memberName="elem_4" virtualName=""
                    explicitFocusOrder="0" pos="25.767% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="6ebf5b7360841b9d" memberName="elem_5" virtualName=""
                    explicitFocusOrder="0" pos="31.902% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="efac3412ab6bbb4e" memberName="elem_6" virtualName=""
                    explicitFocusOrder="0" pos="38.037% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="1935bd49dead785c" memberName="elem_7" virtualName=""
                    explicitFocusOrder="0" pos="44.172% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="d192e82f735f80c3" memberName="elem_8" virtualName=""
                    explicitFocusOrder="0" pos="50.92% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="48014e2241dfc5e9" memberName="elem_9" virtualName=""
                    explicitFocusOrder="0" pos="57.055% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="5174c6e85aab41ef" memberName="elem_10" virtualName=""
                    explicitFocusOrder="0" pos="63.19% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="4327bd1745d3be4a" memberName="elem_11" virtualName=""
                    explicitFocusOrder="0" pos="69.325% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="2b1e4b7dbf2ef91" memberName="elem_12" virtualName=""
                    explicitFocusOrder="0" pos="76.074% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="258138253a12fa97" memberName="elem_13" virtualName=""
                    explicitFocusOrder="0" pos="82.209% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="60eb5f3968f1b6bc" memberName="elem_14" virtualName=""
                    explicitFocusOrder="0" pos="88.344% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
  <GENERICCOMPONENT name="" id="e6cbe4abe0854180" memberName="elem_15" virtualName=""
                    explicitFocusOrder="0" pos="94.479% 0% 100% 100%" posRelativeY="7df349b1fad40eac"
                    posRelativeW="7df349b1fad40eac" posRelativeH="7df349b1fad40eac"
                    class="ModelBase" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
