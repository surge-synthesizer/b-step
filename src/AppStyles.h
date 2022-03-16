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

struct AppStyle
{
    uint32 default_colour;
    virtual uint32& get_background_color();
    virtual uint32& get_foreground_color();
    virtual uint32& get_border_color() ;
    virtual uint32& get_font_color();
    virtual uint32& get_element_border_color();
    virtual uint32& get_slider_knob_color();
    virtual uint32& get_slider_outline_color();

    uint32 button_border_color;
    virtual uint32& get_button_border_color();

    virtual uint32& get_state_on_1_color() ;
    virtual uint32& get_state_on_2_color() ;
    virtual uint32& get_state_off_1_color() ;
    virtual uint32& get_state_off_2_color() ;

    virtual bool is_opaque() const;
    virtual bool is_wrapper_opaque() const;

    virtual const Font& get_font() const;

private:
    Font _font;
public:
    void set_font( Font font_ );

    AppStyle();

public:
    virtual ~AppStyle() {}

public:
    static void paint_outline_label (
        Graphics& g_,
        const Component& owner_,
        const String& text_,
        AppStyle*const style_,
        const Justification justification_,
        float x_,
        float y_,
        float w_,
        float h_,
        bool heigh_else_with_prop = true );

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AppStyle)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct ColorTheme
{
    uint32 main_border;
    uint32 main_bg;
    uint32 main_step_bg;

    uint32 bar_area_border;
    uint32 bar_area_bg;
    uint32 bar_step_bg;

    uint32 step_area_border;
    uint32 step_area_bg;
    uint32 step_step_bg;

    uint32 elem_color_1; // step_button_on
    uint32 elem_color_2; // step_button_off
    uint32 elem_color_3; // step_button_onMute
    uint32 elem_color_4; // step_button_offMute
    uint32 elem_color_5; // run_light
    uint32 elem_color_6; // solo
    uint32 elem_color_7; // octave_rotary
    uint32 elem_color_8; // chord_rotary
    uint32 elem_color_9; // duration_rotary
    uint32 elem_color_10;// velocity_rotary

    uint32 main_step_border;
    uint32 bar_step_border;
    uint32 step_step_border;

    uint32 slider_knob_color;
    uint32 slider_outline;

    Array< uint32* > color_list;
public:
    void set_theme( String color_list );

    const String get_color_list() const;
private:
    friend class AppInstanceStore;
    ColorTheme();

public:
    EMPTY_D_CTOR_OUT_WRITE( ColorTheme );

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ColorTheme)
};

#endif  // APPSTYLES_H_INCLUDED
