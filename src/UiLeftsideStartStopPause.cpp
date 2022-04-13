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
#include "PluginProcessor.h"
#include "CoreSequencer.h"

#include "UiLeftsideStartStopPause.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
void UiLeftsideStartStopPause::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_)
{
    button_play->get_components_to_repaint(components_to_repaint_);
    button_pause->get_components_to_repaint(components_to_repaint_);
    button_stop->get_components_to_repaint(components_to_repaint_);
}

//==============================================================================
UiLeftsideStartStopPause::UiLeftsideStartStopPause()
{
    button_play = std::make_unique<ModelBase>();
    addAndMakeVisible(*button_play);

    button_pause = std::make_unique<ModelBase>();
    addAndMakeVisible(*button_pause);

    button_stop = std::make_unique<ModelBase>();
    addAndMakeVisible(*button_stop);

    _style = nullptr;

#ifdef DO_NEVER_DEFINE_THIS

    setSize(170, 50);

#endif
}

UiLeftsideStartStopPause::~UiLeftsideStartStopPause()
{
    button_play = nullptr;
    button_pause = nullptr;
    button_stop = nullptr;
}

//==============================================================================
void UiLeftsideStartStopPause::paint(juce::Graphics &g)
{
    return;

    g.fillAll(juce::Colours::white);
}

void UiLeftsideStartStopPause::resized()
{
    button_play->setBounds(0, proportionOfHeight(0.1000f), proportionOfWidth(0.2353f),
                           proportionOfHeight(0.8000f));
    button_pause->setBounds(proportionOfWidth(0.2647f), proportionOfHeight(0.1000f),
                            proportionOfWidth(0.2353f), proportionOfHeight(0.8000f));
    button_stop->setBounds(proportionOfWidth(0.5294f), proportionOfHeight(0.1000f),
                           proportionOfWidth(0.2353f), proportionOfHeight(0.8000f));
}

//==============================================================================
