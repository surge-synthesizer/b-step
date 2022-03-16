/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#include "UIEditorToolbar.h"
#include "UiEditorInputPopup.h"

void UiEditorInputPopup::capture_editor(TextEditor *source_)
{
    release_editor();

    captured_editor = source_;

    Component *parent_component = source_->getParentComponent();
    parent_editor = nullptr;
    while (parent_component)
    {
        parent_editor = dynamic_cast<UiEditor *>(parent_component);
        if (parent_editor)
        {
            int desktop_height =
                Desktop::getInstance().getDisplays().getMainDisplay().userArea.getHeight();
            Rectangle<int> child_screen_bounds = source_->getScreenBounds();
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
    Component *focus_component = Component::getCurrentlyFocusedComponent();
    if (focus_component)
    {
        TextEditor *editor = dynamic_cast<TextEditor *>(focus_component);
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
