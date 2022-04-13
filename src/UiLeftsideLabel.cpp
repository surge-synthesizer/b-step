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

#include "UiLeftsideLabel.h"

void UiLeftsideLabel::set_text(const juce::String &text_) { label.set_text(text_); }

void UiLeftsideLabel::on_style_set(AppStyle *const style_)
{
    if (style_)
    {
        label.set_style(style_);
    }
}

void UiLeftsideLabel::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_)
{
    if (label.is_repaint_required())
    {
        // components_to_repaint_.add( this );
        // components_to_repaint_.add( &label );
    }
}

//==============================================================================
UiLeftsideLabel::UiLeftsideLabel()
{

    last_painted_bg = 0x00000000;
    _style = nullptr;

    label.justification = juce::Justification::right;
    addAndMakeVisible(&label);

#ifdef DO_NEVER_DEFINE_THIS

    setSize(170, 50);

#endif
}

UiLeftsideLabel::~UiLeftsideLabel() {}

//==============================================================================
void UiLeftsideLabel::paint(juce::Graphics &g) { g.fillAll(juce::Colour(0x00000000)); }

void UiLeftsideLabel::resized()
{
    label.setBounds(proportionOfWidth(0.0250f), proportionOfHeight(0.1000f),
                    proportionOfWidth(0.8824f), proportionOfHeight(0.8500f));
}
