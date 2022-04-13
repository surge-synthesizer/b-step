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

#include "UiLeftsideModelLabel.h"

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

//==============================================================================
UiLeftsideModelLabel::UiLeftsideModelLabel()
{
    model = std::make_unique<ModelBase>();
    addAndMakeVisible(*model);

    _style = nullptr;

#ifdef DO_NEVER_DEFINE_THIS

    setSize(170, 50);

#endif
}

UiLeftsideModelLabel::~UiLeftsideModelLabel() { model = nullptr; }

//==============================================================================
void UiLeftsideModelLabel::paint(juce::Graphics &g)
{
    if (_style)
        if (_style->is_opaque())
            g.fillAll(juce::Colour(_style->get_foreground_color()));
    AppStyle::paint_outline_label(g, *this, _text, _style, juce::Justification::left, 0.3235f,
                                  0.1000f, 0.6177f, 0.8000f);
    return;

    g.fillAll(juce::Colours::white);
}

void UiLeftsideModelLabel::resized()
{
    model->setBounds(proportionOfWidth(0.0588f), proportionOfHeight(0.1000f),
                     proportionOfWidth(0.2353f), proportionOfHeight(0.8000f));
}
