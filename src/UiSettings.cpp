/*
  ==============================================================================

    UiSettings.cpp
    Created: 2 Aug 2014 11:08:12am
    Author:  monotomy

  ==============================================================================
*/

#include "UiSettings.h"
#include "UiEditorAbout.h"
#include "UiEditorChords.h"
#include "UiEditorClipboard.h"
#include "UiEditorDemo.h"
#include "UiEditorMidiLearn.h"
#include "UiEditorSettings.h"
#include "UiEditorSetup.h"
#include "ControllerMidiLearn.h"
#include "UiEditorFileManager.h"
#include "UiEditorWhatsNew.h"
#include "AppStyleEditor.h"
#include "UIHtmlView.h"
#include "UiQuestionIsYourFriend.h"
#include "UiTextImExport.h"

#include "UiMainWindow.h"

EditorConfig::EditorConfig(AppInstanceStore*const app_instance_store_)
    : _app_instance_store( app_instance_store_ ),
      _resize_denominator( 1 ),

      demo_time_is_over(false),
      slider_controller_is_down( nullptr ),

      controller_mid_learn( nullptr ),
      midi_learn_editor( nullptr ),
      chord_editor( nullptr ),
      editor_settings( nullptr ),
      about_winodow( nullptr ),
#ifdef DEMO
      demo_window( nullptr ),
#endif
      clipboard_editor( nullptr ),
      setup_editor( nullptr ),
      style_editor( nullptr ),
      file_manager( nullptr ),
      whatsnew_editor( nullptr ),
      manual_editor( nullptr ),

      XY_midi_learn_editor( -9999, -9999 ),
      XY_chord_editor( -9999, -9999 ),
      XY_editor_settings( -9999, -9999 ),
      XY_clipboard_editor( -9999, -9999 ),
      XY_setup_editor( -9999, -9999 ),
      XY_style_editor( -9999, -9999 ),
      XY_file_manager( -9999, -9999 ),

      current_editable_colour( nullptr ),

      selected_bar_clipboard_id( 0 ),
      update_notifyer_was_up(false)
{
    BOOT( EditorConfig );

    drum_names.add( ">>" ); 		// 0
    drum_names.add( ">>" ); 		// 1
    drum_names.add( ">>" ); 		// 2
    drum_names.add( ">>" ); 		// 3
    drum_names.add( ">>" ); 		// 4
    drum_names.add( ">>" ); 		// 5
    drum_names.add( ">>" ); 		// 6
    drum_names.add( ">>" ); 		// 7
    drum_names.add( ">>" ); 		// 8
    drum_names.add( ">>" ); 		// 9
    drum_names.add( ">>" ); 		// 10
    drum_names.add( ">>" ); 		// 11
    drum_names.add( ">>" ); 		// 12
    drum_names.add( ">>" ); 		// 13
    drum_names.add( ">>" ); 		// 14
    drum_names.add( ">>" ); 		// 15
    drum_names.add( ">>" ); 		// 16
    drum_names.add( ">>" ); 		// 17
    drum_names.add( ">>" ); 		// 18
    drum_names.add( ">>" ); 		// 19
    drum_names.add( ">>" ); 		// 20
    drum_names.add( ">>" ); 		// 21
    drum_names.add( ">>" ); 		// 22
    drum_names.add( ">>" ); 		// 23
    drum_names.add( ">>" ); 		// 24
    drum_names.add( ">>" ); 		// 25
    drum_names.add( ">>" ); 		// 26
    drum_names.add( ">>" ); 		// 27
    drum_names.add( ">>" ); 		// 28
    drum_names.add( ">>" ); 		// 29
    drum_names.add( ">>" ); 		// 30
    drum_names.add( ">>" ); 		// 31
    drum_names.add( ">>" ); 		// 32
    drum_names.add( ">>" ); 		// 33
    drum_names.add( ">>" ); 		// 34
    drum_names.add( "BD2" ); 		// 35
    drum_names.add( "BD1" ); 		// 36
    drum_names.add( "SS" ); 		// 37
    drum_names.add( "SN1" ); 		// 38
    drum_names.add( "HC" ); 		// 39
    drum_names.add( "SN2" ); 		// 40
    drum_names.add( "LT" ); 		// 41
    drum_names.add( "CH" ); 		// 42
    drum_names.add( "LT" ); 		// 43
    drum_names.add( "PH" ); 		// 44
    drum_names.add( "MT2" ); 		// 45
    drum_names.add( "OH" ); 		// 46
    drum_names.add( "MT" ); 		// 47
    drum_names.add( "HT" ); 		// 48
    drum_names.add( "CCy" ); 		// 49
    drum_names.add( "HT1" ); 		// 50
    drum_names.add( "RCy" ); 		// 51
    drum_names.add( "Cy" ); 		// 52
    drum_names.add( "RB" ); 		// 53
    drum_names.add( "TA" ); 		// 54
    drum_names.add( "SCy" ); 		// 55
    drum_names.add( "CB" ); 		// 56
    drum_names.add( "CCy" ); 		// 57
    drum_names.add( "VS" ); 		// 58
    drum_names.add( "RCy" ); 		// 59
    drum_names.add( "HB" ); 		// 60
    drum_names.add( "LB" ); 		// 61
    drum_names.add( "MHC" ); 		// 62
    drum_names.add( "OHC" ); 		// 63
    drum_names.add( "LC" ); 		// 64
    drum_names.add( "HT" ); 		// 65
    drum_names.add( "LT" ); 		// 66
    drum_names.add( "HA" ); 		// 67
    drum_names.add( "LA" ); 		// 68
    drum_names.add( "Ca" ); 		// 69
    drum_names.add( "M" ); 		// 70
    drum_names.add( "SW" ); 		// 71
    drum_names.add( "LW" ); 		// 72
    drum_names.add( "SG" ); 		// 73
    drum_names.add( "LG" ); 		// 74
    drum_names.add( "Cl" ); 		// 75
    drum_names.add( "HWB" ); 		// 76
    drum_names.add( "LWB" ); 		// 77
    drum_names.add( "MC" ); 		// 78
    drum_names.add( "OC" ); 		// 79
    drum_names.add( "MT" ); 		// 80
    drum_names.add( "OT" ); 		// 81
    drum_names.add( "<<" ); 		// 82
    drum_names.add( "<<" ); 		// 83
    drum_names.add( "<<" ); 		// 84
    drum_names.add( "<<" ); 		// 85
    drum_names.add( "<<" ); 		// 86
    drum_names.add( "<<" ); 		// 87
    drum_names.add( "<<" ); 		// 88
    drum_names.add( "<<" ); 		// 89
    drum_names.add( "<<" ); 		// 90
    drum_names.add( "<<" ); 		// 91
    drum_names.add( "<<" ); 		// 92
    drum_names.add( "<<" ); 		// 93
    drum_names.add( "<<" ); 		// 94
    drum_names.add( "<<" ); 		// 95
    drum_names.add( "<<" ); 		// 96
    drum_names.add( "<<" ); 		// 97
    drum_names.add( "<<" ); 		// 98
    drum_names.add( "<<" ); 		// 99
    drum_names.add( "<<" ); 		// 100
    drum_names.add( "<<" ); 		// 101
    drum_names.add( "<<" ); 		// 102
    drum_names.add( "<<" ); 		// 103
    drum_names.add( "<<" ); 		// 104
    drum_names.add( "<<" ); 		// 105
    drum_names.add( "<<" ); 		// 106
    drum_names.add( "<<" ); 		// 107
    drum_names.add( "<<" ); 		// 108
    drum_names.add( "<<" ); 		// 109
    drum_names.add( "<<" ); 		// 110
    drum_names.add( "<<" ); 		// 111
    drum_names.add( "<<" ); 		// 112
    drum_names.add( "<<" ); 		// 113
    drum_names.add( "<<" ); 		// 114
    drum_names.add( "<<" ); 		// 115
    drum_names.add( "<<" ); 		// 116
    drum_names.add( "<<" ); 		// 117
    drum_names.add( "<<" ); 		// 118
    drum_names.add( "<<" ); 		// 119
    drum_names.add( "<<" ); 		// 120
    drum_names.add( "<<" ); 		// 121
    drum_names.add( "<<" ); 		// 122
    drum_names.add( "<<" ); 		// 123
    drum_names.add( "<<" ); 		// 124
    drum_names.add( "<<" ); 		// 125
    drum_names.add( "<<" ); 		// 126
    drum_names.add( "<<" ); 		// 127
}

void EditorConfig::close_all_editors()
{
#ifdef DEMO
    if( demo_window )
        demo_window = nullptr;
#endif
    if( im_exporter_editor )
        im_exporter_editor->on_close_clicked();
    if( midi_learn_editor )
        midi_learn_editor->on_close_clicked();
    if( chord_editor )
        chord_editor->on_close_clicked();
    if( editor_settings )
        editor_settings->on_close_clicked();
    if( about_winodow )
        about_winodow->on_close_clicked();
    if( clipboard_editor )
        clipboard_editor->on_close_clicked();
    setup_editor = nullptr;
    if( style_editor )
        style_editor->on_close_clicked();
    if( file_manager )
        file_manager->on_close_clicked();
    whatsnew_editor = nullptr;
    if( manual_editor )
        manual_editor->on_close_clicked();
    if( question_editor )
        question_editor->on_close_clicked();
}

EditorConfig::~EditorConfig()
{
    DOWN( EditorConfig );

    close_all_editors();
}

