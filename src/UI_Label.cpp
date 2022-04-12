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

#include "_H_UiElements.h"
#include "AppStyles.h"

UiLabel::UiLabel(const juce::String &text_, AppStyle *const style_)
    : _text(text_), _style(style_), _is_manual_unopaque(false), _last_painted_bg(0x00000000),
      _last_painted_outline(0x00000000), _last_painted_fg(0x00000000),
      justification(juce::Justification::right), force_repaint(false)
{
    setRepaintsOnMouseActivity(true);
    // setBufferedToImage(false);
    // setPaintingIsUnclipped(true);
    setInterceptsMouseClicks(false, false);
}

UiLabel::~UiLabel() {}

void UiLabel::set_text(const juce::String &text_)
{
    if (_text.compare(text_) == 0)
        return;

    _text = text_;

    // force_repaint = true;
    repaint();
}

void UiLabel::resized() { cache_paint(); }

bool UiLabel::is_repaint_required()
{
    if (!_style)
        return false;

    if (force_repaint)
        return true;

    if (_style->get_foreground_color() != _last_painted_bg)
    {
        return true;
    }

    if (_style->get_slider_outline_color() != _last_painted_outline)
    {
        return true;
    }

    if (_style->get_font_color() != _last_painted_fg)
    {
        return true;
    }

    return false;
}

void UiLabel::cache_paint()
{
    if (!_style)
        return;

    _last_painted_bg = _style->get_foreground_color();
    _last_painted_outline = _style->get_slider_outline_color();
    _last_painted_fg = _style->get_font_color();
}

void UiLabel::paint(juce::Graphics &g_)
{
    force_repaint = false;

    cache_paint();
    if (!_is_manual_unopaque)
        if (_style->is_opaque())
            g_.fillAll(juce::Colour(_style->get_foreground_color()));

    AppStyle::paint_outline_label(g_, *this, _text, _style, justification, 0.0588f, 0.1000f,
                                  0.8824f, 0.8000f, true);
}

void UiLabel::set_style(AppStyle *const style_)
{
    if (_style != style_)
    {
        _style = style_;
        if (_is_manual_unopaque)
            setOpaque(false);
        else
            setOpaque(_style->is_opaque());

        cache_paint();
    }
    _style = style_;
}
