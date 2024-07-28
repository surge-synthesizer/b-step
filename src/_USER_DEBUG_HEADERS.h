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

#ifndef USER_DEBUG_H_INCLUDED
#define USER_DEBUG_H_INCLUDED
// ----------------------------------------
#ifdef DEVELOPMENT
// HEADERS
#include "UiSettings.h"
#include "UiEditorAbout.h"
#include "FileIO.h"

// PRINT TYPES
// - EVENTS

#define LOG_BUTTON_EVENTS "BUTTON::"
// #	define LOG_BUTTON_EVENTS 0

// #	define LOG_VST_CLOCK "CLOCK::"
#define LOG_VST_CLOCK 0

#define LOG_VST_TRANSPORT_EVENTS "TRANSPORT-EVENT::"
// #	define LOG_VST_TRANSPORT_EVENTS 0

// PRINTER
#define USER_OUT(LOG_TYPE, a, b, c, d)                                                             \
    if (LOG_TYPE != 0)                                                                             \
    {                                                                                              \
        AppInstanceStore *_STORE = GLOBAL_VALUE_HOLDER::getInstance()->_app_instance_store;        \
        if (_STORE)                                                                                \
        {                                                                                          \
            UiEditorAbout *_EDITOR_ABOUT = GLOBAL_VALUE_HOLDER::getInstance()                      \
                                               ->_app_instance_store->editor_config.about_winodow; \
            if (_EDITOR_ABOUT)                                                                     \
            {                                                                                      \
                _EDITOR_ABOUT->print_debug(String(LOG_TYPE) + String(a) + String(b) + String(c) +  \
                                           String(d));                                             \
            }                                                                                      \
        }                                                                                          \
    } // EO LOG_TYPE
// ----------------------------------------
#else
// HIDE PRINTER
#define USER_OUT(LOG_TYPE, a, b, c, d)

#endif
// ----------------------------------------
#endif
