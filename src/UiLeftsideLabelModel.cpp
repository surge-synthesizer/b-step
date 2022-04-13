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

#include "AppStyles.h"

#include "UiMainWindow.h"

#include "UiLeftsideLabelModel.h"

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

    _style = nullptr;

#ifdef DO_NEVER_DEFINE_THIS

    setSize(170, 50);

#endif
    setOpaque(true);
}

UiLeftsideLabelModel::~UiLeftsideLabelModel()
{
    bg_button = nullptr;
    model = nullptr;
}

//==============================================================================
void UiLeftsideLabelModel::paint(juce::Graphics &g)
{
    if (_style)
        g.fillAll(juce::Colour(_style->get_foreground_color()));
    // g.fillAll(Colour(0xffffffff));

    AppStyle::paint_outline_label(g, *this, _text, _style, juce::Justification::centred, 0.0588f,
                                  0.1000f, 0.6177f, 0.8000f);
    return;

    g.fillAll(juce::Colours::white);
}

void UiLeftsideLabelModel::resized()
{

    bg_button->setBounds(0, 0, 168, 48);
    model->setBounds(proportionOfWidth(0.7059f), proportionOfHeight(0.1000f),
                     proportionOfWidth(0.2353f), proportionOfHeight(0.8000f));
}

void UiLeftsideLabelModel::buttonClicked(juce::Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == bg_button.get())
    {
        _app_insteance_store->editor->open_chord_editor();
    }
}
