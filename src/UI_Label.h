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
