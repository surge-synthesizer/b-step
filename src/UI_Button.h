#ifndef __UI_BUTTON_H__
#define __UI_BUTTON_H__

#include "UI_Base.h"

class UiButton :
    public UIBase,
    public DragAndDropTarget,
    public DragAndDropContainer,
    public Component,
    public Timer
{
    bool is_mouse_down;
    bool is_simple_drag_valid;
    bool is_multi_drag_valid;
    bool was_dragging;

    ScopedPointer<Component> drop_source;
    
public:
    void mouseDown(const MouseEvent&) override;
    void mouseUp(const MouseEvent& e_ ) override;
    void mouseMove (const MouseEvent& e_ ) override;
    void mouseEnter (const MouseEvent& e_ ) override;
    void mouseExit (const MouseEvent& e_ ) override;
    void mouseDrag (const MouseEvent& e_ ) override;
    void mouseDoubleClick (const MouseEvent& e_ ) override;
    void mouseWheelMove (const MouseEvent &e_, const MouseWheelDetails &wheel_ ) override;

private:
    bool isInterestedInDragSource ( const SourceDetails& sd_ ) override;
    void itemDropped ( const SourceDetails& sd_ ) override;
    void timerCallback( ) override;
    void dragOperationEnded(const DragAndDropTarget::SourceDetails &) override;

public:
    void triggerClick();
    void clicked();

private:
    void resized( int w_, int h_ ) override;

    uint32 _foreground_color_1;
    uint32 _foreground_color_2;
    uint32 _outline_color;
    bool refresh_foreground() override;
    void paint ( Graphics& ) override {};
    void cache_paint ( Graphics& g_, uint32 background_colour_ ) override;

    Component* get_top_level_component() override;
    void* get_top_level_impl() override;

public:
    UiButton();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR ( UiButton )
};

#endif // __UI_BUTTON_H__



