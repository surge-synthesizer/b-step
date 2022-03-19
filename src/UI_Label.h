/*
  ==============================================================================

    UI_Label.h
    Created: 29 May 2014 7:55:19pm
    Author:  monotomy

  ==============================================================================
*/

#ifndef UI_LABEL_H_INCLUDED
#define UI_LABEL_H_INCLUDED

#include "App.h"

class AppStyle;
class UiLabel : public juce::Component
{
    juce::String _text;
    AppStyle *_style;
    bool _is_manual_unopaque;

    std::uint32_t _last_painted_bg;
    std::uint32_t _last_painted_outline;
    std::uint32_t _last_painted_fg;

    bool force_repaint;

  public:
    juce::Justification justification;
    bool is_repaint_required();

  private:
    void resized() override;

  public:
    void cache_paint();

  private:
    void paint(juce::Graphics &g_) override;

  public:
    void set_text(const juce::String &text_);
    void set_style(AppStyle *const style_);

    UiLabel(const juce::String &text_ = "", AppStyle *const style_ = nullptr);
    ~UiLabel();

    void set_manual_opaque(bool is_opaque_) { _is_manual_unopaque = !is_opaque_; }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiLabel)
};

#endif // UI_LABEL_H_INCLUDED
