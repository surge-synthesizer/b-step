#ifndef __UI_SLIDER_H__
#define __UI_SLIDER_H__

#include "App.h"
#include "UI_Base.h"

class UISlider;
class SliderWrapper;
class SliderWrapper : public Slider, public Timer
{
    UISlider *const _owner;

  public:
    void mouseDown(const MouseEvent &e_) override;
    bool is_a_long_mouse_down_event;
    void mouseUp(const MouseEvent &) override;
    void mouseMove(const MouseEvent &) override {}
    void mouseExit(const MouseEvent &) override {}
    void mouseDrag(const MouseEvent &) override;
    void mouseDoubleClick(const MouseEvent &) override {}
    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;

  private:
    void paint(Graphics &) override {}

  public:
    void cache_paint(Graphics &g_, uint32 background_colour_);

  private:
    MouseEvent *mouse_up_fake;
    // simulate mouse up on mouseweel move
    void timerCallback() override;

  public:
    SliderWrapper(UISlider *const owner_);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SliderWrapper)
};

class MONO_UISliderController;
class UISlider : public Component,
                 public UIBase,
                 public Slider::Listener,
                 public DragAndDropTarget,
                 public DragAndDropContainer
{
    friend class MONO_UISliderController;

    SliderWrapper *const slider;

    bool is_mouse_down;

    bool use_long_mouse_down();
    void on_mouse_drag(const MouseEvent &);
    bool isInterestedInDragSource(const SourceDetails &sd_) override;
    void itemDropped(const SourceDetails &sd_) override;

    void on_mouse_down(const MouseEvent &e_);
    void on_long_mouse_down();
    void on_mouse_up(const MouseEvent &e_);
    void sliderValueChanged(Slider *s_) override;

    void set_value(int value_, NotificationType n_type_);
    int get_value() const;
    void setRange(int min_, int max_, int interval_);
    void setTextBoxStyle(Slider::TextEntryBoxPosition box_pos_, bool is_read_only,
                         int text_box_width, int text_box_height);
    void setSliderStyle(Slider::SliderStyle style_);
    void setDragSensitivity(int sensitivity_);

    int last_painted_value;

    void resized(int w_, int h_) override;

    friend class SliderWrapper;
    uint32 _slider_fill_color;
    uint32 _slider_outline_color;
    uint32 _slider_knob_color;
    int _last_painted_value;
    bool refresh_foreground() override;
    void paint(Graphics &) override {}
    void cache_paint(Graphics &g_, uint32 background_colour_) override;

    Component *get_top_level_component() override;
    void *get_top_level_impl() override;

  public:
    UISlider();
    ~UISlider();

    void mouseDown(const MouseEvent &e_) { slider->mouseDown(e_); }
    void mouseUp(const MouseEvent &e_) { slider->mouseUp(e_); }
    void mouseMove(const MouseEvent &e_) { slider->mouseMove(e_); }
    void mouseEnter(const MouseEvent &e_) { slider->mouseEnter(e_); }
    void mouseExit(const MouseEvent &e_) { slider->mouseExit(e_); }
    void mouseDrag(const MouseEvent &e_) { slider->mouseDrag(e_); }
    void mouseDoubleClick(const MouseEvent &e_) { slider->mouseDoubleClick(e_); }
    void mouseWheelMove(const MouseEvent &e_, const MouseWheelDetails &w_)
    {
        slider->mouseWheelMove(e_, w_);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UISlider)
};

#endif // __UI_SLIDER_H__
