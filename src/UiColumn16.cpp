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

#include "UiColumn16.h"

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

//==============================================================================
UiColumn16::UiColumn16()
{
    elem_0 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_0);

    elem_1 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_1);

    elem_2 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_2);

    elem_3 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_3);

    elem_4 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_4);

    elem_5 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_5);

    elem_6 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_6);

    elem_7 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_7);

    elem_8 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_8);

    elem_9 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_9);

    elem_10 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_10);

    elem_11 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_11);

    elem_12 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_12);

    elem_13 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_13);

    elem_14 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_14);

    elem_15 = std::make_unique<ModelBase>();
    addAndMakeVisible(*elem_15);

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

    setSize(815, 50);

#endif
}

UiColumn16::~UiColumn16()
{
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
}

//==============================================================================
void UiColumn16::paint(juce::Graphics &g)
{
    if (_style)
        if (_style->is_wrapper_opaque())
            g.fillAll(juce::Colour(_style->get_foreground_color()));
    return;

    g.fillAll(juce::Colours::white);
}

void UiColumn16::resized()
{
#if !JUCE_IOS

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
}
