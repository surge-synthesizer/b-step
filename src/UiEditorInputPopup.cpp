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

#include "UIEditorToolbar.h"
#include "UiEditorInputPopup.h"

void UiEditorInputPopup::capture_editor(juce::TextEditor *source_)
{
    release_editor();

    captured_editor = source_;

    juce::Component *parent_component = source_->getParentComponent();
    parent_editor = nullptr;
    while (parent_component)
    {
        parent_editor = dynamic_cast<UiEditor *>(parent_component);
        if (parent_editor)
        {
            int desktop_height = juce::Desktop::getInstance()
                                     .getDisplays()
                                     .getPrimaryDisplay()
                                     ->userArea.getHeight();
            juce::Rectangle<int> child_screen_bounds = source_->getScreenBounds();
            int top_y = desktop_height / 4 - source_->getHeight() / 2;

            parent_editor->animate_move(top_y - child_screen_bounds.getY());

            return;
        }
        else
            parent_component = parent_component->getParentComponent();
    }
}

void UiEditorInputPopup::release_editor()
{
    captured_editor = nullptr;

    if (parent_editor)
    {
        parent_editor->animate_move_back();
        parent_editor = nullptr;
    }
}

void UiEditorInputPopup::refresh_ui()
{
    juce::Component *focus_component = juce::Component::getCurrentlyFocusedComponent();
    if (focus_component)
    {
        juce::TextEditor *editor = dynamic_cast<juce::TextEditor *>(focus_component);
        if (editor)
        {
            if (editor != captured_editor)
                capture_editor(editor);
        }
        else
            release_editor();
    }
    else
        release_editor();
}

UiEditorInputPopup::UiEditorInputPopup()
{
    parent_editor = nullptr;
    captured_editor = nullptr;
}

UiEditorInputPopup::~UiEditorInputPopup() { release_editor(); }
