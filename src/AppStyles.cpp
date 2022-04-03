/*
  ==============================================================================

    AppStyles.cpp
    Created: 27 May 2014 5:54:00pm
    Author:  monotomy

  ==============================================================================
*/

#include "AppStyles.h"
#include "App.h"
#include "AppInstanceStore.h"

std::uint32_t &AppStyle::get_background_color() { return default_colour; }
std::uint32_t &AppStyle::get_foreground_color() { return default_colour; }
std::uint32_t &AppStyle::get_border_color() { return default_colour; }
std::uint32_t &AppStyle::get_button_border_color() { return button_border_color; }
std::uint32_t &AppStyle::get_font_color() { return default_colour; }
std::uint32_t &AppStyle::get_element_border_color() { return default_colour; }
std::uint32_t &AppStyle::get_slider_knob_color() { return default_colour; }
std::uint32_t &AppStyle::get_slider_outline_color() { return default_colour; }
std::uint32_t &AppStyle::get_state_on_1_color() { return default_colour; }
std::uint32_t &AppStyle::get_state_on_2_color() { return default_colour; }
std::uint32_t &AppStyle::get_state_off_1_color() { return default_colour; }
std::uint32_t &AppStyle::get_state_off_2_color() { return default_colour; }
bool AppStyle::is_opaque() const { return false; }
bool AppStyle::is_wrapper_opaque() const { return false; }
const juce::Font &AppStyle::get_font() const { return _font; }
void AppStyle::set_font(juce::Font font_) { _font = font_; }

AppStyle::AppStyle() : default_colour(0xff000000), button_border_color(0xff111111) {}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/*
ColorTheme::ColorTheme()
{
    main_border 	=
Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR).darker(0.5).getARGB(); main_bg
=		Colour(0xFF483d37).darker(0.5).getARGB();

    step_area_border	=		GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR;
    step_area_bg	=		0xFF483d37;

    bar_area_border	=
Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR).darker(0.2).getARGB(); bar_area_bg	=
Colour(step_area_bg).darker(0.5).getARGB();

    elem_color_1	=			0xFFcd000d;	// mute
    elem_color_2	=		0xFF81a22e;
    elem_color_3	=			elem_color_1;     // Skip
    elem_color_4	=			main_bg ;     // mute off
    elem_color_5	=			0xFFff4800;     // Run
    elem_color_6	=			0xFFffce3c;     // Solo
    elem_color_7	=			0xFF6ac8e1;     // Octave
    elem_color_8	=			0xFFb9c815;     // Chord
    elem_color_9	=			0xFFe9efb0;     // Duration

    elem_color_10	=		Colour(0xFF012634).brighter(0.2).getARGB();  // Velocity
}
*/
/* THE GOOD OLD BROWN */
/*
ColorTheme::ColorTheme()
{
    main_border 	=
Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR).darker(0.5).getARGB(); main_bg
=		Colour(0xFF483d37).darker(0.5).getARGB();

    step_area_border	=		GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR;
    step_area_bg	=		0xFF483d37;

    bar_area_border	=
Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR).darker(0.2).getARGB(); bar_area_bg	=
Colour(step_area_bg).darker(0.5).getARGB();

    elem_color_1	=		0xFFff7f2b;
    elem_color_2	=		0xFF000000;
    elem_color_3	=		Colours::red.darker( 0.4 ).getARGB();
    elem_color_4	=		Colour( step_area_bg ).darker( 0.6 ).getARGB();
    elem_color_5	=		Colour(0xFFa02c2c).brighter(0.8).getARGB();
    elem_color_6	=		Colour(0xFFff7f2b).darker(0.5).getARGB();
    elem_color_7	=		0xFFff7f2b;
    elem_color_8	=		0xFF89a02c;
    elem_color_9	=		0xff00c0c8;
    elem_color_10	=		GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR;
}
*/

ColorTheme::ColorTheme()
{
    BOOT(ColorTheme);

    main_border =
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR).darker(0.5).getARGB();
    main_bg = juce::Colour(0xFF412d21).darker(0.4).getARGB();

    step_area_border = GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR; //
    step_area_bg = 0xFF412d21;

    bar_area_border =
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR).darker(0.2).getARGB();
    bar_area_bg = juce::Colour(step_area_bg).darker(0.6).getARGB();

    elem_color_1 = 0xFFd0222d;
    elem_color_2 = 0xFF000000;
    elem_color_3 = elem_color_1;
    elem_color_4 = juce::Colour(step_area_bg).darker(0.6).getARGB();
    elem_color_5 = 0xFFc9a376;
    elem_color_6 = 0xFFf98120;
    elem_color_7 = 0xFFff7f2b;
    elem_color_8 = 0xFF86983d;
    elem_color_9 = 0xFF4dadb1; // 0xff00c0c8;
    elem_color_10 = GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR;

    main_step_bg = juce::Colour(main_bg).darker(0.6).getARGB();
    bar_step_bg = juce::Colour(bar_area_bg).darker(0.6).getARGB();
    step_step_bg = juce::Colour(step_area_bg).darker(0.6).getARGB();

    main_step_border = juce::Colour(main_bg).darker(0.9).getARGB();
    bar_step_border = juce::Colour(bar_area_bg).darker(0.9).getARGB();
    step_step_border = juce::Colour(step_area_bg).darker(0.9).getARGB();

    slider_knob_color = 0xff000000;
    slider_outline = 0xff141414;

    color_list.add(&elem_color_1);
    // color_list.add( &elem_color_2 );
    color_list.add(&elem_color_3);
    color_list.add(&elem_color_4);
    color_list.add(&elem_color_5);
    color_list.add(&elem_color_6);
    color_list.add(&elem_color_7);
    color_list.add(&elem_color_8);
    color_list.add(&elem_color_9);
    color_list.add(&elem_color_10);
    color_list.add(&main_border);
    color_list.add(&main_bg);
    color_list.add(&step_area_border);
    color_list.add(&step_area_bg);
    color_list.add(&bar_area_border);
    color_list.add(&bar_area_bg);

    color_list.add(&main_step_bg);
    color_list.add(&bar_step_bg);
    color_list.add(&step_step_bg);

    color_list.add(&main_step_border);
    color_list.add(&bar_step_border);
    color_list.add(&step_step_border);

    color_list.add(&slider_knob_color);
    color_list.add(&slider_outline);

    color_list.add(&GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR);
}

void AppStyle::paint_outline_label(juce::Graphics &g_, const juce::Component &owner_,
                                   const juce::String &text_, AppStyle *const style_,
                                   const juce::Justification justification_, float x_, float y_,
                                   float w_, float h_, bool heigh_else_with_prop)
{
    if (style_)
    {
        float prop;
        if (heigh_else_with_prop)
            prop = 1.0f / 40 * owner_.getHeight();
        else
            prop = 1.0f / 35 * owner_.getWidth();

#if JUCE_ANDROID
        Image image(Image::ARGB, owner_.proportionOfWidth(w_), owner_.proportionOfHeight(h_), true);
        Graphics g(image);

        g.setColour(Colour(style_->get_font_color()));
        g.setFont(style_->get_font().withHeight(jmin(20.0f, owner_.proportionOfHeight(h_) * 0.8f)));

        g.drawFittedText(text_, 0, owner_.proportionOfHeight(y_), owner_.proportionOfWidth(w_),
                         owner_.proportionOfHeight(h_), justification_, 1);

        Image shadow_free(image);

        DropShadow shadow(Colour(style_->get_slider_outline_color()), 1, Point<int>(0, 0));
        shadow.drawForImage(g_, image);
        shadow.drawForImage(g_, image);
        shadow.drawForImage(g_, image);

        g_.drawImageAt(shadow_free, 0, 0);
#else
        juce::Path text_path;
        juce::GlyphArrangement glyphs;
        glyphs.addFittedText(style_->get_font().withHeight(prop * style_->get_font().getHeight()),
                             text_, owner_.proportionOfWidth(x_), owner_.proportionOfHeight(y_),
                             owner_.proportionOfWidth(w_), owner_.proportionOfHeight(h_),
                             justification_, 6, 0.3);
        glyphs.createPath(text_path);

        g_.setColour(juce::Colour(style_->get_slider_outline_color()));
        juce::PathStrokeType stroke_type(2 * prop);
        g_.strokePath(text_path, stroke_type);

        g_.setColour(juce::Colour(style_->get_font_color()));
        g_.fillPath(text_path);
#endif
    }
}

void ColorTheme::set_theme(juce::String color_list_)
{
    bool still_comma_inside = true;
    juce::String comma(",");
    int counter = 0;
    while (still_comma_inside)
    {
        if (counter >= color_list.size())
        {
            return;
        }

        int comma_poition = color_list_.indexOfChar(*comma.toWideCharPointer());
        if (comma_poition == -1)
            still_comma_inside = false;
        else
        {
            // Colour col( Colour::fromString( colour_list.substring(0,comma_poition) ) );
            *color_list.getUnchecked(counter) =
                juce::Colour::fromString(color_list_.substring(0, comma_poition)).getARGB();
            color_list_ = color_list_.substring(comma_poition + 1);
        }

        counter++;
        if (counter > 300)
        {
            return;
        }
    }
}
const juce::String ColorTheme::get_color_list() const
{
    juce::String color_list_string;
    for (int i = 0; i != color_list.size(); ++i)
    {
        color_list_string +=
            juce::Colour(*color_list.getUnchecked(i)).toString() + juce::String(",");
    }
    color_list_string +=
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR).toString() +
        juce::String(",");

    return color_list_string;
}
