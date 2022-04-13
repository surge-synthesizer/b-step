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
#include "Controller.h"

#include "SliderValuePopup.h"

void SliderValuePopup::set_text(juce::String &text_)
{
    if (_text.compare(text_) != 0)
    {
        if (text_ == HAS_NO_TEXT_VALUE)
            _text = "";
        else
            _text = text_;
        repaint(0, 0, getWidth(), getHeight());
    }
}

//==============================================================================
SliderValuePopup::SliderValuePopup(const ModelBase *const model_) : _model(model_)
{
    setSize(60, 40);

#ifdef JUCE_IOS
    setOpaque(true);
#endif
}

SliderValuePopup::~SliderValuePopup() {}

//==============================================================================
void SliderValuePopup::paint(juce::Graphics &g)
{
    g.setColour(juce::Colour(0xff111111));
    g.fillRoundedRectangle(1.0f, 1.0f, static_cast<float>(getWidth() - 2),
                           static_cast<float>(getHeight() - 2), 5.000f);

    if (_model)
        if (_model->get_style())
            g.setColour(juce::Colour(_model->get_style()->get_font_color()));

    g.drawRoundedRectangle(1.0f, 1.0f, static_cast<float>(getWidth() - 2),
                           static_cast<float>(getHeight() - 2), 5.000f, 2.000f);

    AppStyle::paint_outline_label(g, *this, _text, _model->get_style(),
                                  juce::Justification::centred, 0.0588f, 0.1000f, 0.8824f, 0.8000f);

    return;

    g.setColour(juce::Colour(0xff111111));
    g.fillRoundedRectangle(1.0f, 1.0f, static_cast<float>(getWidth() - 2),
                           static_cast<float>(getHeight() - 2), 5.000f);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(1.0f, 1.0f, static_cast<float>(getWidth() - 2),
                           static_cast<float>(getHeight() - 2), 5.000f, 2.000f);

    g.setColour(juce::Colours::yellow);
    g.setFont(juce::Font(22.00f, juce::Font::bold));
    g.drawText(TRANS("XXX"), 0, 0, proportionOfWidth(1.0000f), proportionOfHeight(1.0000f),
               juce::Justification::centred, true);
}

void SliderValuePopup::resized() {}
