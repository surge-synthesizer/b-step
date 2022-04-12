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

#ifndef __UI_BUTTON_H__
#define __UI_BUTTON_H__

#include "UI_Base.h"

class UiButton : public UIBase,
                 public juce::DragAndDropTarget,
                 public juce::DragAndDropContainer,
                 public juce::Component,
                 public juce::Timer
{
    bool is_mouse_down;
    bool is_simple_drag_valid;
    bool is_multi_drag_valid;
    bool was_dragging;

    std::unique_ptr<juce::Component> drop_source;

  public:
    void mouseDown(const juce::MouseEvent &) override;
    void mouseUp(const juce::MouseEvent &e_) override;
    void mouseMove(const juce::MouseEvent &e_) override;
    void mouseEnter(const juce::MouseEvent &e_) override;
    void mouseExit(const juce::MouseEvent &e_) override;
    void mouseDrag(const juce::MouseEvent &e_) override;
    void mouseDoubleClick(const juce::MouseEvent &e_) override;
    void mouseWheelMove(const juce::MouseEvent &e_, const juce::MouseWheelDetails &wheel_) override;

  private:
    bool isInterestedInDragSource(const SourceDetails &sd_) override;
    void itemDropped(const SourceDetails &sd_) override;
    void timerCallback() override;
    void dragOperationEnded(const juce::DragAndDropTarget::SourceDetails &) override;

  public:
    void triggerClick();
    void clicked();

  private:
    void resized(int w_, int h_) override;

    std::uint32_t _foreground_color_1;
    std::uint32_t _foreground_color_2;
    std::uint32_t _outline_color;
    bool refresh_foreground() override;
    void paint(juce::Graphics &) override{};
    void cache_paint(juce::Graphics &g_, std::uint32_t background_colour_) override;

    juce::Component *get_top_level_component() override;
    void *get_top_level_impl() override;

  public:
    UiButton();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiButton)
};

#endif // __UI_BUTTON_H__
