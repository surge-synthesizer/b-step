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
#include "_H_UiElements.h"

#include "UiLeftsideCC.h"

void UiLeftsideCC::on_style_set(AppStyle *const)
{
    if (_style)
    {
        setOpaque(_style->is_opaque());
    }

    cc_type->set_style(_style);
    cc_label->set_style(_style);
}
void UiLeftsideCC::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_)
{
    cc_type->get_components_to_repaint(components_to_repaint_);

    if (cc_label->is_repaint_required())
        components_to_repaint_.add(cc_label.get());

    const MONO_Controller *constroller = cc_type->get_controller();
    if (constroller)
        cc_label->set_text(juce::String("CC ") + juce::String(constroller->get_value()));
}

//==============================================================================
UiLeftsideCC::UiLeftsideCC()
{
    cc_type = std::make_unique<ModelBase>();
    addAndMakeVisible(*cc_type);

    cc_label = std::make_unique<UiLabel>();
    addAndMakeVisible(*cc_label);

    _style = nullptr;

#ifdef DO_NEVER_DEFINE_THIS

    setSize(170, 50);

#endif
}

UiLeftsideCC::~UiLeftsideCC()
{
    cc_type = nullptr;
    cc_label = nullptr;
}

//==============================================================================
void UiLeftsideCC::paint(juce::Graphics &g)
{
    if (_style)
        if (_style->is_wrapper_opaque())
            g.fillAll(juce::Colour(_style->get_foreground_color()));

    return;

    g.fillAll(juce::Colours::white);
}

void UiLeftsideCC::resized()
{
    cc_type->setBounds(proportionOfWidth(0.0588f), proportionOfHeight(0.1000f),
                       proportionOfWidth(0.2353f), proportionOfHeight(0.8000f));
    cc_label->setBounds(proportionOfWidth(0.3529f), proportionOfHeight(0.1000f),
                        proportionOfWidth(0.5882f), proportionOfHeight(0.8000f));
}
