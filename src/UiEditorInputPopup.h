/*
  ==============================================================================

  This is an automatically generated class created by the Introjucer!

  ==============================================================================
*/

#ifndef __JUCE_HEADER_606E9AAF0379D62A__
#define __JUCE_HEADER_606E9AAF0379D62A__

#include "App.h"

class UiEditor;

// TODO RENAME CLASS, ISNT A UI THING ANYMORE
class UiEditorInputPopup
{
  public:
    UiEditorInputPopup();
    ~UiEditorInputPopup();

  private:
    UiEditor *parent_editor;
    TextEditor *captured_editor;

    void capture_editor(TextEditor *source_);
    void release_editor();

  public:
    void refresh_ui();

  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorInputPopup)
};

#endif
