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
//#	define LOG_BUTTON_EVENTS 0

//#	define LOG_VST_CLOCK "CLOCK::"
#define LOG_VST_CLOCK 0

#define LOG_VST_TRANSPORT_EVENTS "TRANSPORT-EVENT::"
//#	define LOG_VST_TRANSPORT_EVENTS 0

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
