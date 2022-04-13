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

#include "UiColumn16.h"
#include "AppStyles.h"

#include "UiColumnWrapper.h"

void UiColumnWrapper::set_leftside_subeditor(SubeditorBase *const leftside_editor_)
{
    if (leftside_subeditor.get())
    {
        leftside_editor_->setBounds(leftside_subeditor->getX(), leftside_subeditor->getY(),
                                    leftside_subeditor->getWidth(),
                                    leftside_subeditor->getHeight());
    }

    leftside_subeditor = std::unique_ptr<SubeditorBase>(leftside_editor_);
    addAndMakeVisible(*leftside_subeditor);
}
void UiColumnWrapper::set_colum_editor(UiColumn16 *const column_editor_)
{
    if (column_editor.get())
    {
        column_editor_->setBounds(column_editor->getX(), column_editor->getY(),
                                  column_editor->getWidth(), column_editor->getHeight());
    }

    column_editor = std::unique_ptr<UiColumn16>(column_editor_);
    addAndMakeVisible(*column_editor);
}

void UiColumnWrapper::refresh_ui(juce::Array<Component *> &components_to_repaint_)
{
    if (column_editor)
        column_editor->refresh_ui(components_to_repaint_);
    if (leftside_subeditor)
        leftside_subeditor->refresh_ui(components_to_repaint_);
}

void UiColumnWrapper::get_controllers_for_paint_popup(
    juce::Array<MONO_Controller *> &controllers_with_popup_)
{
    if (column_editor)
        column_editor->get_controllers_for_paint_popup(controllers_with_popup_);
    if (leftside_subeditor)
        leftside_subeditor->get_controllers_for_paint_popup(controllers_with_popup_);
}

void UiColumnWrapper::set_style(AppStyle *const style_)
{
    if (_style != style_)
    {
        _style = style_;

        if (_style)
            setOpaque(_style->is_wrapper_opaque());
    }

    if (leftside_subeditor)
        leftside_subeditor->set_style(_style);
    if (column_editor)
        column_editor->set_style(_style);
}

//==============================================================================
UiColumnWrapper::UiColumnWrapper()
{
    leftside_subeditor = std::make_unique<SubeditorBase>();
    addAndMakeVisible(*leftside_subeditor);

    column_editor = std::make_unique<UiColumn16>();
    addAndMakeVisible(*column_editor);

    _style = nullptr;

#ifdef DO_NEVER_DEFINE_THIS

    setSize(985, 50);

#endif // DO_NEVER_DEFINE_THIS
}

UiColumnWrapper::~UiColumnWrapper()
{
    leftside_subeditor = nullptr;
    column_editor = nullptr;
}

//==============================================================================
void UiColumnWrapper::paint(juce::Graphics &g)
{
    if (_style)
        if (_style->is_wrapper_opaque())
            g.fillAll(juce::Colour(_style->get_foreground_color()));
    return;

    g.fillAll(juce::Colours::white);
}

void UiColumnWrapper::resized()
{
    leftside_subeditor->setBounds(0, 0, proportionOfWidth(0.1726f), proportionOfHeight(1.0000f));
    column_editor->setBounds(proportionOfWidth(0.1726f), 0, proportionOfWidth(0.8274f),
                             proportionOfHeight(1.0000f));
}
