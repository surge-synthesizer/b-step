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

#ifndef __UI_SLIDER_H__
#define __UI_SLIDER_H__

#include "App.h"
#include "UI_Base.h"

class UISlider;
class SliderWrapper;
class SliderWrapper : public juce::Slider, public juce::Timer
{
    UISlider *const _owner;

  public:
    void mouseDown(const juce::MouseEvent &e_) override;
    bool is_a_long_mouse_down_event;
    void mouseUp(const juce::MouseEvent &) override;
    void mouseMove(const juce::MouseEvent &) override {}
    void mouseExit(const juce::MouseEvent &) override {}
    void mouseDrag(const juce::MouseEvent &) override;
    void mouseDoubleClick(const juce::MouseEvent &) override {}
    void mouseWheelMove(const juce::MouseEvent &event,
                        const juce::MouseWheelDetails &wheel) override;

  private:
    void paint(juce::Graphics &) override {}

  public:
    void cache_paint(juce::Graphics &g_, std::uint32_t background_colour_);

  private:
    juce::MouseEvent *mouse_up_fake;
    // simulate mouse up on mouseweel move
    void timerCallback() override;

  public:
    SliderWrapper(UISlider *const owner_);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SliderWrapper)
};

class MONO_UISliderController;
class UISlider : public juce::Component,
                 public UIBase,
                 public juce::Slider::Listener,
                 public juce::DragAndDropTarget,
                 public juce::DragAndDropContainer
{
    friend class MONO_UISliderController;

    SliderWrapper *const slider;

    bool is_mouse_down;

    bool use_long_mouse_down();
    void on_mouse_drag(const juce::MouseEvent &);
    bool isInterestedInDragSource(const SourceDetails &sd_) override;
    void itemDropped(const SourceDetails &sd_) override;

    void on_mouse_down(const juce::MouseEvent &e_);
    void on_long_mouse_down();
    void on_mouse_up(const juce::MouseEvent &e_);
    void sliderValueChanged(juce::Slider *s_) override;

    void set_value(int value_, juce::NotificationType n_type_);
    int get_value() const;
    void setRange(int min_, int max_, int interval_);
    void setTextBoxStyle(juce::Slider::TextEntryBoxPosition box_pos_, bool is_read_only,
                         int text_box_width, int text_box_height);
    void setSliderStyle(juce::Slider::SliderStyle style_);
    void setDragSensitivity(int sensitivity_);

    int last_painted_value;

    void resized(int w_, int h_) override;

    friend class SliderWrapper;
    std::uint32_t _slider_fill_color;
    std::uint32_t _slider_outline_color;
    std::uint32_t _slider_knob_color;
    int _last_painted_value;
    bool refresh_foreground() override;
    void paint(juce::Graphics &) override {}
    void cache_paint(juce::Graphics &g_, std::uint32_t background_colour_) override;

    juce::Component *get_top_level_component() override;
    void *get_top_level_impl() override;

  public:
    UISlider();
    ~UISlider();

    void mouseDown(const juce::MouseEvent &e_) override { slider->mouseDown(e_); }
    void mouseUp(const juce::MouseEvent &e_) override { slider->mouseUp(e_); }
    void mouseMove(const juce::MouseEvent &e_) override { slider->mouseMove(e_); }
    void mouseEnter(const juce::MouseEvent &e_) override { slider->mouseEnter(e_); }
    void mouseExit(const juce::MouseEvent &e_) override { slider->mouseExit(e_); }
    void mouseDrag(const juce::MouseEvent &e_) override { slider->mouseDrag(e_); }
    void mouseDoubleClick(const juce::MouseEvent &e_) override { slider->mouseDoubleClick(e_); }
    void mouseWheelMove(const juce::MouseEvent &e_, const juce::MouseWheelDetails &w_) override
    {
        slider->mouseWheelMove(e_, w_);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UISlider)
};

#endif // __UI_SLIDER_H__
