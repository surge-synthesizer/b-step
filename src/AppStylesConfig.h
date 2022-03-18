
#ifndef APP_STYLES_CONFIG_H
#define APP_STYLES_CONFIG_H

#include "AppStyles.h"
#include <cstdint>

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class StyleStepArea : public AppStyle
{
  protected:
    ColorTheme *const _color_theme;

  private:
    std::uint32_t &get_background_color() override { return _color_theme->main_bg; }
    std::uint32_t &get_foreground_color() override { return _color_theme->step_area_bg; }
    std::uint32_t &get_border_color() override { return _color_theme->step_area_border; }
    std::uint32_t &get_element_border_color() override { return _color_theme->step_step_border; }
    std::uint32_t &get_slider_knob_color() override { return _color_theme->slider_knob_color; }
    std::uint32_t &get_slider_outline_color() override { return _color_theme->slider_outline; }

    std::uint32_t &get_state_off_1_color() override { return _color_theme->step_step_bg; }

    bool is_opaque() const override { return true; }
    bool is_wrapper_opaque() const override { return true; }

  public:
    StyleStepArea(ColorTheme *const color_theme_) : _color_theme(color_theme_) {}
};

// ************************************************************************************************
class StyleStepAreaMute : public StyleStepArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_1; }
    std::uint32_t &get_state_on_2_color() override { return _color_theme->elem_color_1; }
    std::uint32_t &get_state_off_2_color() override { return _color_theme->elem_color_4; }

    std::uint32_t &get_font_color() override { return _color_theme->elem_color_1; }

  public:
    StyleStepAreaMute(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaOctave : public StyleStepArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_7; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_7; }

  public:
    StyleStepAreaOctave(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaSteps : public StyleStepArea
{
    std::uint32_t &get_state_off_1_color() override { return _color_theme->elem_color_7; }
    std::uint32_t &get_state_on_1_color() override { return _color_theme->step_step_bg; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_7; }
    std::uint32_t &get_state_on_2_color() override { return _color_theme->elem_color_4; }
    std::uint32_t &get_state_off_2_color() override { return _color_theme->elem_color_1; }

  public:
    StyleStepAreaSteps(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaChord : public StyleStepArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_8; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_8; }

  public:
    StyleStepAreaChord(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaDuration : public StyleStepArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_9; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_9; }

  public:
    StyleStepAreaDuration(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaVelocity : public StyleStepArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_10; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_10; }

  public:
    StyleStepAreaVelocity(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaRun : public StyleStepArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_5; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_5; }
    std::uint32_t &get_state_on_2_color() override { return _color_theme->elem_color_3; }
    std::uint32_t &get_state_off_2_color() override { return _color_theme->elem_color_4; }

  public:
    StyleStepAreaRun(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaSkip : public StyleStepArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_3; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_3; }

  public:
    StyleStepAreaSkip(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class StyleBarArea : public AppStyle
{
  protected:
    ColorTheme *const _color_theme;

  private:
    std::uint32_t &get_background_color() override { return _color_theme->main_bg; }
    std::uint32_t &get_foreground_color() override { return _color_theme->bar_area_bg; }
    std::uint32_t &get_border_color() override { return _color_theme->bar_area_border; }
    std::uint32_t &get_element_border_color() override { return _color_theme->bar_step_border; }
    std::uint32_t &get_slider_knob_color() override { return _color_theme->slider_knob_color; }
    std::uint32_t &get_slider_outline_color() override { return _color_theme->slider_outline; }

    std::uint32_t &get_state_off_1_color() override { return _color_theme->bar_step_bg; }

    bool is_opaque() const override { return true; }
    bool is_wrapper_opaque() const override { return false; }

  public:
    StyleBarArea(ColorTheme *const color_theme_) : _color_theme(color_theme_) {}
};

// ************************************************************************************************
class StyleBarAreaMute : public StyleBarArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_1; }
    std::uint32_t &get_state_on_2_color() override { return _color_theme->elem_color_3; }
    std::uint32_t &get_state_off_2_color() override { return _color_theme->elem_color_4; }

    std::uint32_t &get_font_color() override { return _color_theme->elem_color_1; }

  public:
    StyleBarAreaMute(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
class StyleBarAreaSolo : public StyleBarArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_6; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_6; }

  public:
    StyleBarAreaSolo(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
class StyleBarAreaTime : public StyleBarArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_9; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_9; }

  public:
    StyleBarAreaTime(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
class StyleBarAreaSkip : public StyleBarArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_3; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_3; }

  public:
    StyleBarAreaSkip(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
class StyleBarAreaRun : public StyleBarArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_5; }
    std::uint32_t &get_state_on_2_color() override { return _color_theme->elem_color_3; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_5; }
    std::uint32_t &get_state_off_2_color() override { return _color_theme->elem_color_4; }

  public:
    StyleBarAreaRun(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
class StyleBarAreaChord : public StyleBarArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_8; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_8; }

  public:
    StyleBarAreaChord(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
class StyleBarAreaOctave : public StyleBarArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_7; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_7; }

  public:
    StyleBarAreaOctave(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class StyleGlobalArea : public AppStyle
{
  protected:
    ColorTheme *const _color_theme;

  private:
    std::uint32_t &get_background_color() override { return _color_theme->main_bg; }
    std::uint32_t &get_foreground_color() override { return _color_theme->main_bg; }
    std::uint32_t &get_border_color() override { return _color_theme->main_border; }
    std::uint32_t &get_element_border_color() override { return _color_theme->main_step_border; }
    std::uint32_t &get_slider_knob_color() override { return _color_theme->slider_knob_color; }
    std::uint32_t &get_slider_outline_color() override { return _color_theme->slider_outline; }

    std::uint32_t &get_state_off_1_color() override { return _color_theme->main_step_bg; }

    bool is_opaque() const override { return true; }
    bool is_wrapper_opaque() const override { return true; }

  public:
    StyleGlobalArea(ColorTheme *const color_theme_) : _color_theme(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaRun : public StyleGlobalArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_5; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_5; }

  public:
    StyleGlobalAreaRun(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaOctave : public StyleGlobalArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_7; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_7; }

  public:
    StyleGlobalAreaOctave(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaChord : public StyleGlobalArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_8; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_8; }

  public:
    StyleGlobalAreaChord(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaNotes : public StyleGlobalArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->main_border; }
    std::uint32_t &get_font_color() override { return _color_theme->main_border; }

  public:
    StyleGlobalAreaNotes(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaDuration : public StyleGlobalArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_9; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_9; }

  public:
    StyleGlobalAreaDuration(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaVelocity : public StyleGlobalArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_10; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_10; }

  public:
    StyleGlobalAreaVelocity(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaStop : public StyleGlobalArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_3; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_3; }

  public:
    StyleGlobalAreaStop(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class StyleMenuArea : public AppStyle
{
  protected:
    ColorTheme *const _color_theme;

  private:
    std::uint32_t &get_background_color() override { return default_colour; }
    std::uint32_t &get_foreground_color() override { return default_colour; }
    std::uint32_t border_color;
    std::uint32_t &get_border_color() override { return border_color; }
    std::uint32_t button_border_color;
    std::uint32_t &get_button_border_color() override { return button_border_color; }

    std::uint32_t &get_state_off_1_color() override { return default_colour; }

    std::uint32_t &get_font_color() override
    {
        return GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR;
    }

    bool is_opaque() const override { return true; }
    bool is_wrapper_opaque() const override { return true; }

  public:
    StyleMenuArea(ColorTheme *const color_theme_)
        : _color_theme(color_theme_), button_border_color(0xff444444), border_color(0xff5d5d5d)
    {
    }
};

// ************************************************************************************************
class StyleMenuAreaMute : public StyleMenuArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_1; }
    std::uint32_t &get_state_on_2_color() override { return _color_theme->elem_color_3; }
    std::uint32_t &get_state_off_2_color() override { return _color_theme->elem_color_4; }

  public:
    StyleMenuAreaMute(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaOctave : public StyleMenuArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_7; }

  public:
    StyleMenuAreaOctave(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaSolo : public StyleMenuArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_6; }

  public:
    StyleMenuAreaSolo(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaTime : public StyleMenuArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_9; }

  public:
    StyleMenuAreaTime(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaSkip : public StyleMenuArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_3; }

  public:
    StyleMenuAreaSkip(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaRun : public StyleMenuArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_5; }

  public:
    StyleMenuAreaRun(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaChord : public StyleMenuArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_8; }

  public:
    StyleMenuAreaChord(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaVelocity : public StyleMenuArea
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_10; }

  public:
    StyleMenuAreaVelocity(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class StylePopupEditor : public AppStyle
{
  protected:
    ColorTheme *const _color_theme;

  private:
    std::uint32_t bg_colour;
    std::uint32_t &get_background_color() override { return bg_colour; }
    std::uint32_t &get_foreground_color() override { return bg_colour; }
    std::uint32_t &get_border_color() override
    {
        return GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR;
    }
    std::uint32_t button_border_color;
    std::uint32_t &get_button_border_color() override { return button_border_color; }

    std::uint32_t &get_state_off_1_color() override { return default_colour; }
    std::uint32_t &get_state_on_1_color() override
    {
        return GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR;
    }
    std::uint32_t &get_font_color() override
    {
        return GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR;
    }

    bool is_opaque() const override { return true; }
    bool is_wrapper_opaque() const override { return true; }

  public:
    StylePopupEditor(ColorTheme *const color_theme_)
        : _color_theme(color_theme_), bg_colour(0xff161616), button_border_color(0xff444444)
    {
        int font_size = 21;
#ifdef JUCE_IOS
        font_size = 17;
#endif
        set_font(
            juce::Font(juce::Font::getDefaultSansSerifFontName(), font_size, juce::Font::bold));
    }
};

// ************************************************************************************************
class StylePopupEditorMute : public StylePopupEditor
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_1; }
    std::uint32_t &get_state_on_2_color() override { return _color_theme->elem_color_3; }
    std::uint32_t &get_state_off_2_color() override { return _color_theme->elem_color_4; }

    std::uint32_t &get_font_color() override { return _color_theme->elem_color_1; }

  public:
    StylePopupEditorMute(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorOctave : public StylePopupEditor
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_7; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_7; }

  public:
    StylePopupEditorOctave(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorSolo : public StylePopupEditor
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_6; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_6; }

  public:
    StylePopupEditorSolo(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorTime : public StylePopupEditor
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_9; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_9; }

  public:
    StylePopupEditorTime(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorSkip : public StylePopupEditor
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_3; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_3; }

  public:
    StylePopupEditorSkip(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorRun : public StylePopupEditor
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_5; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_5; }

  public:
    StylePopupEditorRun(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorChord : public StylePopupEditor
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_8; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_8; }

  public:
    StylePopupEditorChord(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorVelocity : public StylePopupEditor
{
    std::uint32_t &get_state_on_1_color() override { return _color_theme->elem_color_10; }
    std::uint32_t &get_font_color() override { return _color_theme->elem_color_10; }

  public:
    StylePopupEditorVelocity(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};

#endif
