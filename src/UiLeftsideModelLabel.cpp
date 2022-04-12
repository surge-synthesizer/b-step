/*
** B-Step is Free and Open Source Software
**
** B-Step is made available under the Gnu General Public License, v3.0
** https://www.gnu.org/licenses/gpl-3.0.en.html; The authors of the code
** reserve the right to re-license their contributions under the MIT license in the
** future at the discretion of the project maintainers.
**
** Copyright 2014-2022 by various individuals as described by the git transaction log
**
** All source at: https://github.com/surge-synthesizer/b-step.git
**
** B-Step was a commercial product from 2014-2022, with copyright and ownership
** in that period held by Thomas Arndt at Monoplugs. Thomas made B-Step
** open source in March 2022.
*/

//[Headers] You can add your own extra header files here...
#include "AppStyles.h"
//[/Headers]

#include "UiLeftsideModelLabel.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
void UiLeftsideModelLabel::set_text(const juce::String &text_) { _text = text_; }

void UiLeftsideModelLabel::on_style_set(AppStyle *const style_)
{
    if (_style)
    {
        setOpaque(style_->is_opaque());
    }

    model->set_style(style_);
}

void UiLeftsideModelLabel::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_)
{
    model->get_components_to_repaint(components_to_repaint_);
}

void UiLeftsideModelLabel::get_controllers_for_paint_popup(
    juce::Array<MONO_Controller *> &controllers_with_popup_)
{
    model->get_controllers_for_paint_popup(controllers_with_popup_);
}
//[/MiscUserDefs]

//==============================================================================
UiLeftsideModelLabel::UiLeftsideModelLabel()
{
    model = std::make_unique<ModelBase>();
    addAndMakeVisible(*model);

    //[UserPreSize]
    _style = nullptr;

#ifdef DO_NEVER_DEFINE_THIS
    //[/UserPreSize]

    setSize(170, 50);

    //[Constructor] You can add your own custom stuff here..
#endif
    //[/Constructor]
}

UiLeftsideModelLabel::~UiLeftsideModelLabel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    model = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiLeftsideModelLabel::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    if (_style)
        if (_style->is_opaque())
            g.fillAll(juce::Colour(_style->get_foreground_color()));
    AppStyle::paint_outline_label(g, *this, _text, _style, juce::Justification::left, 0.3235f,
                                  0.1000f, 0.6177f, 0.8000f);
    return;
    //[/UserPrePaint]

    g.fillAll(juce::Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UiLeftsideModelLabel::resized()
{
    model->setBounds(proportionOfWidth(0.0588f), proportionOfHeight(0.1000f),
                     proportionOfWidth(0.2353f), proportionOfHeight(0.8000f));
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

<JUCER_COMPONENT documentType="Component" className="UiLeftsideModelLabel" componentName=""
                 parentClasses="public SubeditorBase" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="170" initialHeight="50">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="" id="7624cdf1c7b5baa9" memberName="model" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="5.882% 10% 23.529% 80%" class="Component"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
