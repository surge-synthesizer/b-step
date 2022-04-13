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

#include "PluginProcessor.h"

#include "UiEditorKeyboard.h"

//==============================================================================
UiEditorKeyboard::UiEditorKeyboard(AppInstanceStore *const app_instance_store_)
    : UiEditor("B-MIDI-Keyboard"), _app_instance_store(app_instance_store_)
{
    keyboard = std::make_unique<juce::MidiKeyboardComponent>(
        *_app_instance_store->audio_processor, juce::MidiKeyboardComponent::horizontalKeyboard);
    addAndMakeVisible(*keyboard);

    setSize(1280, 200);

    // keyboard->setKeyWidth(getWidth()/25);
    // keyboard->setKeyWidth(getWidth()/128);
    keyboard->setLowestVisibleKey(0);
    keyboard->setAvailableRange(0, 127);
}

UiEditorKeyboard::~UiEditorKeyboard() { keyboard = nullptr; }

//==============================================================================
void UiEditorKeyboard::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colour(0xff161616));

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    ResizableWindow::moved();
}

void UiEditorKeyboard::resized()
{
    keyboard->setBounds(2, 2, getWidth() - 4, getHeight() - 4);
    keyboard->setKeyWidth(float(getWidth()) / (float(128.0f / 12) * 7.5));
    ResizableWindow::resized();
}
