
#ifndef APP_STYLES_CONFIG_H
#define APP_STYLES_CONFIG_H

#include "AppStyles.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class StyleStepArea : public AppStyle
{
  protected:
    ColorTheme *const _color_theme;

  private:
    uint32 &get_background_color() override { return _color_theme->main_bg; }
    uint32 &get_foreground_color() override { return _color_theme->step_area_bg; }
    uint32 &get_border_color() override { return _color_theme->step_area_border; }
    uint32 &get_element_border_color() override { return _color_theme->step_step_border; }
    uint32 &get_slider_knob_color() override { return _color_theme->slider_knob_color; }
    uint32 &get_slider_outline_color() override { return _color_theme->slider_outline; }

    uint32 &get_state_off_1_color() override { return _color_theme->step_step_bg; }

    bool is_opaque() const override { return true; }
    bool is_wrapper_opaque() const override { return true; }

  public:
    StyleStepArea(ColorTheme *const color_theme_) : _color_theme(color_theme_) {}
};

// ************************************************************************************************
class StyleStepAreaMute : public StyleStepArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_1; }
    uint32 &get_state_on_2_color() override { return _color_theme->elem_color_1; }
    uint32 &get_state_off_2_color() override { return _color_theme->elem_color_4; }

    uint32 &get_font_color() override { return _color_theme->elem_color_1; }

  public:
    StyleStepAreaMute(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaOctave : public StyleStepArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_7; }
    uint32 &get_font_color() override { return _color_theme->elem_color_7; }

  public:
    StyleStepAreaOctave(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaSteps : public StyleStepArea
{
    uint32 &get_state_off_1_color() override { return _color_theme->elem_color_7; }
    uint32 &get_state_on_1_color() override { return _color_theme->step_step_bg; }
    uint32 &get_font_color() override { return _color_theme->elem_color_7; }
    uint32 &get_state_on_2_color() override { return _color_theme->elem_color_4; }
    uint32 &get_state_off_2_color() override { return _color_theme->elem_color_1; }

  public:
    StyleStepAreaSteps(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaChord : public StyleStepArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_8; }
    uint32 &get_font_color() override { return _color_theme->elem_color_8; }

  public:
    StyleStepAreaChord(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaDuration : public StyleStepArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_9; }
    uint32 &get_font_color() override { return _color_theme->elem_color_9; }

  public:
    StyleStepAreaDuration(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaVelocity : public StyleStepArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_10; }
    uint32 &get_font_color() override { return _color_theme->elem_color_10; }

  public:
    StyleStepAreaVelocity(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaRun : public StyleStepArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_5; }
    uint32 &get_font_color() override { return _color_theme->elem_color_5; }
    uint32 &get_state_on_2_color() override { return _color_theme->elem_color_3; }
    uint32 &get_state_off_2_color() override { return _color_theme->elem_color_4; }

  public:
    StyleStepAreaRun(ColorTheme *const color_theme_) : StyleStepArea(color_theme_) {}
};
// ************************************************************************************************
class StyleStepAreaSkip : public StyleStepArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_3; }
    uint32 &get_font_color() override { return _color_theme->elem_color_3; }

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
    uint32 &get_background_color() override { return _color_theme->main_bg; }
    uint32 &get_foreground_color() override { return _color_theme->bar_area_bg; }
    uint32 &get_border_color() override { return _color_theme->bar_area_border; }
    uint32 &get_element_border_color() override { return _color_theme->bar_step_border; }
    uint32 &get_slider_knob_color() override { return _color_theme->slider_knob_color; }
    uint32 &get_slider_outline_color() override { return _color_theme->slider_outline; }

    uint32 &get_state_off_1_color() override { return _color_theme->bar_step_bg; }

    bool is_opaque() const override { return true; }
    bool is_wrapper_opaque() const override { return false; }

  public:
    StyleBarArea(ColorTheme *const color_theme_) : _color_theme(color_theme_) {}
};

// ************************************************************************************************
class StyleBarAreaMute : public StyleBarArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_1; }
    uint32 &get_state_on_2_color() override { return _color_theme->elem_color_3; }
    uint32 &get_state_off_2_color() override { return _color_theme->elem_color_4; }

    uint32 &get_font_color() override { return _color_theme->elem_color_1; }

  public:
    StyleBarAreaMute(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
class StyleBarAreaSolo : public StyleBarArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_6; }
    uint32 &get_font_color() override { return _color_theme->elem_color_6; }

  public:
    StyleBarAreaSolo(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
class StyleBarAreaTime : public StyleBarArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_9; }
    uint32 &get_font_color() override { return _color_theme->elem_color_9; }

  public:
    StyleBarAreaTime(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
class StyleBarAreaSkip : public StyleBarArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_3; }
    uint32 &get_font_color() override { return _color_theme->elem_color_3; }

  public:
    StyleBarAreaSkip(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
class StyleBarAreaRun : public StyleBarArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_5; }
    uint32 &get_state_on_2_color() override { return _color_theme->elem_color_3; }
    uint32 &get_font_color() override { return _color_theme->elem_color_5; }
    uint32 &get_state_off_2_color() override { return _color_theme->elem_color_4; }

  public:
    StyleBarAreaRun(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
class StyleBarAreaChord : public StyleBarArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_8; }
    uint32 &get_font_color() override { return _color_theme->elem_color_8; }

  public:
    StyleBarAreaChord(ColorTheme *const color_theme_) : StyleBarArea(color_theme_) {}
};
// ************************************************************************************************
class StyleBarAreaOctave : public StyleBarArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_7; }
    uint32 &get_font_color() override { return _color_theme->elem_color_7; }

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
    uint32 &get_background_color() override { return _color_theme->main_bg; }
    uint32 &get_foreground_color() override { return _color_theme->main_bg; }
    uint32 &get_border_color() override { return _color_theme->main_border; }
    uint32 &get_element_border_color() override { return _color_theme->main_step_border; }
    uint32 &get_slider_knob_color() override { return _color_theme->slider_knob_color; }
    uint32 &get_slider_outline_color() override { return _color_theme->slider_outline; }

    uint32 &get_state_off_1_color() override { return _color_theme->main_step_bg; }

    bool is_opaque() const override { return true; }
    bool is_wrapper_opaque() const override { return true; }

  public:
    StyleGlobalArea(ColorTheme *const color_theme_) : _color_theme(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaRun : public StyleGlobalArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_5; }
    uint32 &get_font_color() override { return _color_theme->elem_color_5; }

  public:
    StyleGlobalAreaRun(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaOctave : public StyleGlobalArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_7; }
    uint32 &get_font_color() override { return _color_theme->elem_color_7; }

  public:
    StyleGlobalAreaOctave(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaChord : public StyleGlobalArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_8; }
    uint32 &get_font_color() override { return _color_theme->elem_color_8; }

  public:
    StyleGlobalAreaChord(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaNotes : public StyleGlobalArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->main_border; }
    uint32 &get_font_color() override { return _color_theme->main_border; }

  public:
    StyleGlobalAreaNotes(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaDuration : public StyleGlobalArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_9; }
    uint32 &get_font_color() override { return _color_theme->elem_color_9; }

  public:
    StyleGlobalAreaDuration(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaVelocity : public StyleGlobalArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_10; }
    uint32 &get_font_color() override { return _color_theme->elem_color_10; }

  public:
    StyleGlobalAreaVelocity(ColorTheme *const color_theme_) : StyleGlobalArea(color_theme_) {}
};
// ************************************************************************************************
class StyleGlobalAreaStop : public StyleGlobalArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_3; }
    uint32 &get_font_color() override { return _color_theme->elem_color_3; }

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
    uint32 &get_background_color() override { return default_colour; }
    uint32 &get_foreground_color() override { return default_colour; }
    uint32 border_color;
    uint32 &get_border_color() override { return border_color; }
    uint32 button_border_color;
    uint32 &get_button_border_color() override { return button_border_color; }

    uint32 &get_state_off_1_color() override { return default_colour; }

    uint32 &get_font_color() override { return GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR; }

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
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_1; }
    uint32 &get_state_on_2_color() override { return _color_theme->elem_color_3; }
    uint32 &get_state_off_2_color() override { return _color_theme->elem_color_4; }

  public:
    StyleMenuAreaMute(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaOctave : public StyleMenuArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_7; }

  public:
    StyleMenuAreaOctave(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaSolo : public StyleMenuArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_6; }

  public:
    StyleMenuAreaSolo(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaTime : public StyleMenuArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_9; }

  public:
    StyleMenuAreaTime(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaSkip : public StyleMenuArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_3; }

  public:
    StyleMenuAreaSkip(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaRun : public StyleMenuArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_5; }

  public:
    StyleMenuAreaRun(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaChord : public StyleMenuArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_8; }

  public:
    StyleMenuAreaChord(ColorTheme *const color_theme_) : StyleMenuArea(color_theme_) {}
};
// ************************************************************************************************
class StyleMenuAreaVelocity : public StyleMenuArea
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_10; }

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
    uint32 bg_colour;
    uint32 &get_background_color() override { return bg_colour; }
    uint32 &get_foreground_color() override { return bg_colour; }
    uint32 &get_border_color() override
    {
        return GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR;
    }
    uint32 button_border_color;
    uint32 &get_button_border_color() override { return button_border_color; }

    uint32 &get_state_off_1_color() override { return default_colour; }
    uint32 &get_state_on_1_color() override
    {
        return GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR;
    }
    uint32 &get_font_color() override { return GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR; }

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
        set_font(Font(Font::getDefaultSansSerifFontName(), font_size, Font::bold));
    }
};

// ************************************************************************************************
class StylePopupEditorMute : public StylePopupEditor
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_1; }
    uint32 &get_state_on_2_color() override { return _color_theme->elem_color_3; }
    uint32 &get_state_off_2_color() override { return _color_theme->elem_color_4; }

    uint32 &get_font_color() override { return _color_theme->elem_color_1; }

  public:
    StylePopupEditorMute(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorOctave : public StylePopupEditor
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_7; }
    uint32 &get_font_color() override { return _color_theme->elem_color_7; }

  public:
    StylePopupEditorOctave(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorSolo : public StylePopupEditor
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_6; }
    uint32 &get_font_color() override { return _color_theme->elem_color_6; }

  public:
    StylePopupEditorSolo(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorTime : public StylePopupEditor
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_9; }
    uint32 &get_font_color() override { return _color_theme->elem_color_9; }

  public:
    StylePopupEditorTime(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorSkip : public StylePopupEditor
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_3; }
    uint32 &get_font_color() override { return _color_theme->elem_color_3; }

  public:
    StylePopupEditorSkip(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorRun : public StylePopupEditor
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_5; }
    uint32 &get_font_color() override { return _color_theme->elem_color_5; }

  public:
    StylePopupEditorRun(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorChord : public StylePopupEditor
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_8; }
    uint32 &get_font_color() override { return _color_theme->elem_color_8; }

  public:
    StylePopupEditorChord(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};
// ************************************************************************************************
class StylePopupEditorVelocity : public StylePopupEditor
{
    uint32 &get_state_on_1_color() override { return _color_theme->elem_color_10; }
    uint32 &get_font_color() override { return _color_theme->elem_color_10; }

  public:
    StylePopupEditorVelocity(ColorTheme *const color_theme_) : StylePopupEditor(color_theme_) {}
};

#endif
