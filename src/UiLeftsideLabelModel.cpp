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

#include "UiMainWindow.h"
//[/Headers]

#include "UiLeftsideLabelModel.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
void UiLeftsideLabelModel::set_text(const juce::String &text_) { _text = text_; }

void UiLeftsideLabelModel::on_style_set(AppStyle *const style_)
{
    if (_style)
    {
        setOpaque(style_->is_opaque());
    }

    model->set_style(style_);
}

void UiLeftsideLabelModel::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_)
{
    model->get_components_to_repaint(components_to_repaint_);

    if (_text != _last_painted_text)
    {
        components_to_repaint_.add(this);
        _last_painted_text = _text;
    }
}

void UiLeftsideLabelModel::get_controllers_for_paint_popup(
    juce::Array<MONO_Controller *> &controllers_with_popup_)
{
    model->get_controllers_for_paint_popup(controllers_with_popup_);
}
//[/MiscUserDefs]

//==============================================================================
UiLeftsideLabelModel::UiLeftsideLabelModel(AppInstanceStore *const app_insteance_store_)
    : _app_insteance_store(app_insteance_store_)
{
    bg_button = std::make_unique<juce::ImageButton>(juce::String());
    addAndMakeVisible(*bg_button);
    bg_button->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                                 juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    bg_button->addListener(this);

    bg_button->setImages(false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000),
                         juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(), 1.000f,
                         juce::Colour(0x00000000));
    model = std::make_unique<ModelBase>();
    addAndMakeVisible(*model);

    //[UserPreSize]
    _style = nullptr;

#ifdef DO_NEVER_DEFINE_THIS
    //[/UserPreSize]

    setSize(170, 50);

    //[Constructor] You can add your own custom stuff here..
#endif
    setOpaque(true);
    //[/Constructor]
}

UiLeftsideLabelModel::~UiLeftsideLabelModel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    bg_button = nullptr;
    model = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiLeftsideLabelModel::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    if (_style)
        g.fillAll(juce::Colour(_style->get_foreground_color()));
    // g.fillAll(Colour(0xffffffff));

    AppStyle::paint_outline_label(g, *this, _text, _style, juce::Justification::centred, 0.0588f,
                                  0.1000f, 0.6177f, 0.8000f);
    return;
    //[/UserPrePaint]

    g.fillAll(juce::Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UiLeftsideLabelModel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    bg_button->setBounds(0, 0, 168, 48);
    model->setBounds(proportionOfWidth(0.7059f), proportionOfHeight(0.1000f),
                     proportionOfWidth(0.2353f), proportionOfHeight(0.8000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void UiLeftsideLabelModel::buttonClicked(juce::Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == bg_button.get())
    {
        //[UserButtonCode_bg_button] -- add your button handler code here..
        _app_insteance_store->editor->open_chord_editor();
        //[/UserButtonCode_bg_button]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UiLeftsideLabelModel" componentName=""
                 parentClasses="public SubeditorBase" constructorParams="AppInstanceStore*const app_insteance_store_"
                 variableInitialisers="_app_insteance_store(app_insteance_store_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="170" initialHeight="50">
  <BACKGROUND backgroundColour="ffffffff"/>
  <IMAGEBUTTON name="" id="b7e388be6cd00d8d" memberName="bg_button" virtualName=""
               explicitFocusOrder="0" pos="0 0 168 48" buttonText="" connectedEdges="15"
               needsCallback="1" radioGroupId="0" keepProportions="1" resourceNormal=""
               opacityNormal="1" colourNormal="0" resourceOver="" opacityOver="1"
               colourOver="0" resourceDown="" opacityDown="1" colourDown="0"/>
  <GENERICCOMPONENT name="" id="7624cdf1c7b5baa9" memberName="model" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="70.588% 10% 23.529% 80%" class="Component"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
