/*
  ==============================================================================

    AppStyles.h
    Created: 27 May 2014 5:53:57pm
    Author:  monotomy

  ==============================================================================
*/

#ifndef APPSTYLES_H_INCLUDED
#define APPSTYLES_H_INCLUDED

#include "App.h"
#include <cstdint>

struct AppStyle
{
    std::uint32_t default_colour;
    virtual std::uint32_t &get_background_color();
    virtual std::uint32_t &get_foreground_color();
    virtual std::uint32_t &get_border_color();
    virtual std::uint32_t &get_font_color();
    virtual std::uint32_t &get_element_border_color();
    virtual std::uint32_t &get_slider_knob_color();
    virtual std::uint32_t &get_slider_outline_color();

    std::uint32_t button_border_color;
    virtual std::uint32_t &get_button_border_color();

    virtual std::uint32_t &get_state_on_1_color();
    virtual std::uint32_t &get_state_on_2_color();
    virtual std::uint32_t &get_state_off_1_color();
    virtual std::uint32_t &get_state_off_2_color();

    virtual bool is_opaque() const;
    virtual bool is_wrapper_opaque() const;

    virtual const juce::Font &get_font() const;

  private:
    juce::Font _font;

  public:
    void set_font(juce::Font font_);

    AppStyle();

  public:
    virtual ~AppStyle() {}

  public:
    static void paint_outline_label(juce::Graphics &g_, const juce::Component &owner_,
                                    const juce::String &text_, AppStyle *const style_,
                                    const juce::Justification justification_, float x_, float y_,
                                    float w_, float h_, bool heigh_else_with_prop = true);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppStyle)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct ColorTheme
{
    std::uint32_t main_border;
    std::uint32_t main_bg;
    std::uint32_t main_step_bg;

    std::uint32_t bar_area_border;
    std::uint32_t bar_area_bg;
    std::uint32_t bar_step_bg;

    std::uint32_t step_area_border;
    std::uint32_t step_area_bg;
    std::uint32_t step_step_bg;

    std::uint32_t elem_color_1;  // step_button_on
    std::uint32_t elem_color_2;  // step_button_off
    std::uint32_t elem_color_3;  // step_button_onMute
    std::uint32_t elem_color_4;  // step_button_offMute
    std::uint32_t elem_color_5;  // run_light
    std::uint32_t elem_color_6;  // solo
    std::uint32_t elem_color_7;  // octave_rotary
    std::uint32_t elem_color_8;  // chord_rotary
    std::uint32_t elem_color_9;  // duration_rotary
    std::uint32_t elem_color_10; // velocity_rotary

    std::uint32_t main_step_border;
    std::uint32_t bar_step_border;
    std::uint32_t step_step_border;

    std::uint32_t slider_knob_color;
    std::uint32_t slider_outline;

    juce::Array<std::uint32_t *> color_list;

  public:
    void set_theme(juce::String color_list);

    const juce::String get_color_list() const;

  private:
    friend class AppInstanceStore;
    ColorTheme();

  public:
    EMPTY_D_CTOR_OUT_WRITE(ColorTheme);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColorTheme)
};

#endif // APPSTYLES_H_INCLUDED
