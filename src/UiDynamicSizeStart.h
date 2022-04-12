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

//*****************************************************************************
#ifndef DYNAMIC_FILE_INCLUDED
#define DYNAMIC_FILE_INCLUDED 1
#else
PLEASE_INCLUDE_DYNAMIC_SIZE_END_IN_RESIZED
#endif
//*****************************************************************************

// repaint colours
//*****************************************************************************
#define COLOUR_REPLACEMENT_START                                                                   \
    ComponentColours colours = UiLookAndFeel::getInstance()->colours;                              \
    Colour orange_replacement = colours.bg_lines;                                                  \
    orange_replacement.getARGB();

COLOUR_REPLACEMENT_START
#define Colour(x) ((x == 0xffff3b00) ? orange_replacement : Colour(x))

// repaint
//*****************************************************************************
#define WIDTH_AND_HIGHT_FACTORS                                                                    \
    const float width_factor = 1.0f / original_w * getWidth();                                     \
    const float height_factor = 1.0f / original_h * getHeight();

WIDTH_AND_HIGHT_FACTORS
#define fillRoundedRectangle(x, y, w, h, r)                                                        \
    fillRoundedRectangle(                                                                          \
        x > 2 ? float(x) * width_factor : x, y > 2 ? float(y) * height_factor : y,                 \
        w > 2 ? float(w) * width_factor : w, h > 2 ? float(h) * height_factor : h, r == 1 ? 0 : r)
#define drawRoundedRectangle(x, y, w, h, r, t)                                                     \
    drawRoundedRectangle(x > 2 ? float(x) * width_factor : x,                                      \
                         y > 2 ? float(y) * height_factor : y,                                     \
                         w > 2 ? float(w) * width_factor : w,                                      \
                         h > 2 ? float(h) * height_factor : h, r == 1 ? 0 : r, t == 1 ? 0 : t)

#define fillRect(x, y, w, h)                                                                       \
    fillRect(x > 2 ? float(x) * width_factor : x, y > 2 ? float(y) * height_factor : y,            \
             w > 2 ? float(w) * width_factor : w, h > 2 ? float(h) * height_factor : h)

#define drawRect(x, y, w, h, r)                                                                    \
    drawRect(x > 2 ? float(x) * width_factor : x, y > 2 ? float(y) * height_factor : y,            \
             w > 2 ? float(w) * width_factor : w, h > 2 ? float(h) * height_factor : h, float(r))
#define fillEllipse(x, y, w, h)                                                                    \
    fillEllipse(float(x) * width_factor, float(y) * height_factor, float(w) * width_factor,        \
                float(h) * height_factor)
// resized
//*****************************************************************************
#define setBounds(x, y, w, h)                                                                      \
    setBounds(x > 2 ? float(x) * (1.0f / original_w * getWidth()) : x,                             \
              y > 2 ? float(y) * (1.0f / original_h * getHeight()) : y,                            \
              w > 2 ? float(w) * (1.0f / original_w * getWidth()) : w,                             \
              h > 2 ? float(h) * (1.0f / original_h * getHeight()) : h)
#define startNewSubPath(x, y)                                                                      \
    startNewSubPath(x > 2 ? float(x) * (1.0f / original_w * getWidth()) : x,                       \
                    y > 2 ? float(y) * (1.0f / original_h * getHeight()) : y)
#define lineTo(x, y)                                                                               \
    lineTo(x > 2 ? float(x) * (1.0f / original_w * getWidth()) : x,                                \
           y > 2 ? float(y) * (1.0f / original_h * getHeight()) : y)
