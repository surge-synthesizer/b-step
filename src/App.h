/*
  ==============================================================================

    App.h
    Created: 28 May 2014 10:30:02am
    Author:  monotomy

  ==============================================================================
*/

#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

//#define DEMO 1
//#define DEMO 0

// PRE
class AppInstanceStore;
//#define TESTER_BUILD

#ifdef TESTER_BUILD
//#	define BUILD_INFO String(String("FEB-14 ")+Time::getCompilationDate().formatted("%Y:%m:%d-%H:%M:%S" +String(" ")))
//#	define USE_A_SYNTH 1             // in development
//#	define USE_STANDALONE_SYNTH 1	 // in development
//#	define USE_PLUGIN_PROCESS_BLOCK 1
#	define LOG_THE_EVENTS_TO_FILE 1
#	ifndef USE_PLUGIN_PROCESS_BLOCK
#		ifndef B_STEP_STANDALONE
#			define USE_PLUGIN_PROCESS_BLOCK 1
#		endif
#	endif

//#	define USE_ACTIVE_SENSING 1      // to test
#	define USE_BIGGER_AREA_HACK 1    // to test
#	define DEVELOPMENT 1		 //

#else   // RELEASE

#	define BUILD_INFO String("")
//#	define USE_A_SYNTH 1             // in development
//#	define USE_STANDALONE_SYNTH 1	 // in development
//#	define USE_PLUGIN_PROCESS_BLOCK 1
//#	define LOG_THE_EVENTS_TO_FILE 1
#	ifndef USE_PLUGIN_PROCESS_BLOCK
#		ifndef B_STEP_STANDALONE
#			define USE_PLUGIN_PROCESS_BLOCK 1
#		endif
#	endif

//#	define USE_ACTIVE_SENSING 1      // to test
#	define USE_BIGGER_AREA_HACK 1    // to test
//#	define DEVELOPMENT 1		 //

#endif // TEST // RELEASE

//#undef BUILD_INFO
//#define BUILD_INFO String(String("FEB-18b ")+Time::getCompilationDate().formatted("%Y:%m:%d-%H:%M:%S" +String(" ")))

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

// float
#define B_STEP_VERSION 2.1
#define B_STEP_MINOR_VERSION 0

// VERSIONING (deprecated)
#define B_STEP_VERSION_STRING "b-step-1.1"

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

#ifdef DEBUG
#	define OUT( name ) std::cout /*<< Time::getCurrentTime().formatted("%H:%M:%S") << " :: " */ << name << std::endl
#else
#	define OUT( name )
#endif

#ifdef DEBUG
#	define OUT_LOG( name ) std::cout << Time::getCurrentTime().formatted("%H:%M:%S") << " :: " << name << std::endl
#else
#	define OUT_LOG( name )
#endif

#ifdef LOG_THE_EVENTS_TO_FILE
#	define SESSION_ERROR_LOG_FILE File( get_log_folder(true).getChildFile("current-session.log") )
#	define GLOBAL_ERROR_LOG_FILE  File( get_log_folder(true).getChildFile("error.log") )
#	define CRASHED_SESSION_ERROR_LOG_FILE File( get_log_folder(true).getChildFile("crashed-session.log") )
#	define MIDI_ERROR_LOG_FILE  File( get_log_folder(true).getChildFile("midi.log") )

#	define SESSION_ERROR_LOG( message ) SESSION_ERROR_LOG_FILE.appendText( Time::getCurrentTime().formatted("%H:%M:%S") + String( " :: " ) + message )
#	define GLOBAL_ERROR_LOG( message ) GLOBAL_ERROR_LOG_FILE.appendText( Time::getCurrentTime().formatted("%Y:%m:%d-%H:%M:%S") + String( " :: " ) + message )
#	define MIDI_ERROR_LOG( message ) MIDI_ERROR_LOG_FILE.appendText( Time::getCurrentTime().formatted("%Y:%m:%d-%H:%M:%S") + String( " :: " ) + message )
#else
#	define SESSION_ERROR_LOG_FILE
#	define GLOBAL_ERROR_LOG_FILE
#	define MIDI_ERROR_LOG_FILE

#	define SESSION_ERROR_LOG( message )
#	define GLOBAL_ERROR_LOG( message )
#	define MIDI_ERROR_LOG( message )
#endif

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

// JUCE
#ifdef B_STEP_STANDALONE
#	include "../../b-step-standalone/JuceLibraryCode/JuceHeader.h"
#	include "../../b-step-standalone/JuceLibraryCode/BinaryData.h"
#else
#	include "../JuceLibraryCode/JuceHeader.h"
// #	include "../../b-step-standalone/JuceLibraryCode/BinaryData.h" // MANAGE ALL INCLUDES FROM THE STANDALONE PROJECT!
#endif

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

#if JUCE_MAC
#	define PLATFORM_B_FOLDER userMusicDirectory
#	define APP_ROOT_FOLDER "/B-Step Sequencer"
#elif JUCE_LINUX || RASPBERRY || JUCE_ANDROID
#	define PLATFORM_B_FOLDER userDocumentsDirectory
#	define APP_ROOT_FOLDER "/B-Step"
#elif JUCE_WINDOWS
#	define PLATFORM_B_FOLDER userDocumentsDirectory
#	define APP_ROOT_FOLDER "/b-step"
#elif JUCE_IOS
#	define PLATFORM_B_FOLDER userDocumentsDirectory
#	define APP_ROOT_FOLDER "/b-step"
#endif

inline static File get_app_folder(const String& sub_dirs_ = "" ) {
    File file = File(File::getSpecialLocation(File::PLATFORM_B_FOLDER).getFullPathName()
                     +String(APP_ROOT_FOLDER+sub_dirs_)).getFullPathName();

    return file;
}

inline static File get_downloads_folder( bool create_if_not_exist_ = false ) {
    File folder = get_app_folder().getChildFile("downloads");

    if(create_if_not_exist_)
        folder.createDirectory();

    return folder;
}
inline static File get_log_folder( bool create_if_not_exist_ = false ) {
    File folder = get_app_folder().getChildFile("log");

    if(create_if_not_exist_)
        folder.createDirectory();

    return folder;
}
inline static File get_session_folder( bool create_if_not_exist_ = false ) {
    File folder = get_app_folder().getChildFile("session");

    if(create_if_not_exist_)
        folder.createDirectory();

    return folder;
}
inline static File get_projects_folder( bool create_if_not_exist_ = false ) {
    File folder = get_app_folder().getChildFile("projects");

    if(create_if_not_exist_)
        folder.createDirectory();

    return folder;
}
inline static File get_snapshots_folder( bool create_if_not_exist_ = false ) {
    File folder = get_app_folder().getChildFile("snapshots");

    if(create_if_not_exist_)
        folder.createDirectory();

    return folder;
}
inline static File get_chordset_folder( bool create_if_not_exist_ = false ) {
    File folder = get_app_folder().getChildFile("chordsets");

    if(create_if_not_exist_)
        folder.createDirectory();

    return folder;
}
inline static File get_mappings_folder( bool create_if_not_exist_ = false) {
    File folder = get_app_folder().getChildFile("mappings");

    if(create_if_not_exist_)
        folder.createDirectory();

    return folder;
}
inline static File get_colours_folder( bool create_if_not_exist_ = false ) {
    File folder = get_app_folder().getChildFile("colours");

    if(create_if_not_exist_)
        folder.createDirectory();

    return folder;
}
inline static File get_manual_folder( bool create_if_not_exist_ = false ) {
    File folder = get_app_folder().getChildFile("manual");

    if(create_if_not_exist_)
        folder.createDirectory();

    return folder;
}

#undef PLATFORM_B_FOLDER
#undef APP_ROOT_FOLDER

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

class RAII_POST {
    const char*const _type;
    const char*const _class;
public:
    RAII_POST( const char*const type_, const char*const class_ ) : _type( type_ ), _class( class_ ) {
        OUT_LOG( _type + String("::") + _class );
        if( String(_type) =="DOWN" )
            SESSION_ERROR_LOG( _type + String("::") + _class +String("\n") );
    }
    ~RAII_POST() {
        OUT_LOG( _type + String("::") + _class + String("::DONE") );
        if( String(_type) =="DOWN" )
            SESSION_ERROR_LOG( _type + String("::") + _class + String("::DONE\n") );
    }
};

#ifdef DEBUG
#	define BOOT( class ) RAII_POST( "BOOT", #class );
#else
#	define BOOT( class )
#endif

#ifdef DEBUG
#	define DOWN( class ) RAII_POST( "DOWN", #class );
#else
#	define DOWN( class )
#endif

#ifdef DEBUG
#	define EMPTY_CTOR_OUT_WRITE( class ) ~class() { BOOT( class ) }
#else
#	define EMPTY_CTOR_OUT_WRITE( class )
#endif
#ifdef DEBUG
#	define EMPTY_D_CTOR_OUT_WRITE( class ) ~class() { DOWN( class ) }
#else
#	define EMPTY_D_CTOR_OUT_WRITE( class )
#endif

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

enum ALERT_TYPES
{
    ONE_BUTTON_BOX,
    TWO_BUTTON_BOX,
    TREE_BUTTON_BOX
};

struct AlertHandler {

    ALERT_TYPES _type;

    AlertWindow::AlertIconType _icon;

    String _title;
    String _message;
    String _button_1;
    String _button_2;
    String _button_3;

    operator bool() const {
        switch( _type )
        {
        case TWO_BUTTON_BOX :
            return AlertWindow::showOkCancelBox (_icon,
                                                 _title,
                                                 _message,
                                                 _button_1,
                                                 _button_2
                                                );
        case TREE_BUTTON_BOX :
            return AlertWindow::showYesNoCancelBox (_icon,
                                                    _title,
                                                    _message,
                                                    _button_1,
                                                    _button_2,
                                                    _button_3
                                                   );
        default :
            AlertWindow::showMessageBoxAsync (_icon,
                                              _title,
                                              _message,
                                              _button_1 );
            return true;
        };
    }

    AlertHandler( ALERT_TYPES type_,
                  AlertWindow::AlertIconType icon_,
                  String& title_,
                  String& message_,
                  String button_1_ = "",
                  String button_2_ = "",
                  String button_3_ = "" ) :
        _type( type_ ),
        _icon( icon_ ),
        _title(title_),
        _message(message_),
        _button_1(button_1_),
        _button_2(button_2_),
        _button_3(button_3_)
    {
        GLOBAL_ERROR_LOG( String("\"")+title_+String("::")+message_  );
        SESSION_ERROR_LOG( String("\"")+title_+String("::")+message_  );
    }
};

#define ALERT_LOG_SHOW( message_window_type, icon, title, message, button_1, button_2, button_3 ) \
  AlertHandler( message_window_type, icon, title, message, button_1, button_2, button_3 )

#define ALERT_LOG( title, message ) GLOBAL_ERROR_LOG( title+String("::")+message ); SESSION_ERROR_LOG( title+String("::")+message );

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

// Own FRAMEWORK
#include "Parameter.h"
//#include "AppInstanceStore.h" // included by Parameter.h

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

static const String MANUAL_URL("http://b-step-manual-redirect.monoplugs.com/");

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

// THREAD WITH THE OPTION TO KILL ITSELF
class AutonomThread : public Thread, public AsyncUpdater {
    virtual void handleAsyncUpdate() override {
        if( ! stopThread(2000) )
        {
            GLOBAL_ERROR_LOG( "THREAD CAN STOPPED: "+getThreadName() );
        }
        delete this;
    }

protected:
    void selfkill() {
        triggerAsyncUpdate();
    }

    AutonomThread( const String& name_ ) : Thread( name_ ) {
    }

    virtual ~AutonomThread() {}
};

// GLOBAL UI VAR
// NOTE this will change this var cross over all plugins
// Will be used by low level components without the way over the app instance store

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

#define INCLUDE_USER_DEBUG "_USER_DEBUG_HEADERS.h"
struct GLOBAL_VALUE_HOLDER : public DeletedAtShutdown
{
    int8 INSTANCES;

    int16 LONG_MOUSE_DOWN_INTERVAL;
    float MULTIDRAG_SENSITIVITY;
    float SIMPLEDRAG_SENSITIVITY;
    bool MULTIDRAG_ENABLE;
    bool MULTIDRAG_AT_RIGHT_MOUSE;
    bool ENABLE_MOUSEWHEEL;
    bool DONT_SHOW_AGAIN_2_1;
    bool AUTO_CHECK_UPDATES;
    bool USER_ASKED_FOR_AUTO_UPDATE;
    bool QUESTION_WAS_UP;
    bool WHATS_NEW_WAS_UP;

    uint32 MASTER_COLOUR;

#ifdef LOG_THE_EVENTS_TO_FILE
    bool SESSION_FILE_WAS_STILL_PRESENT;
    String COPY_OF_SESSION_FILE;
#endif // LOG_THE_EVENTS_TO_FILE

#ifdef DEVELOPMENT
    AppInstanceStore* _app_instance_store;
#endif

    juce_DeclareSingleton (GLOBAL_VALUE_HOLDER,false)
private:
    GLOBAL_VALUE_HOLDER();
    ~GLOBAL_VALUE_HOLDER();

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// LOAD AND SAVE
public:
    void save_to( XmlElement& xml ) const
    {
        xml.setAttribute ( "multidrag_time" , LONG_MOUSE_DOWN_INTERVAL );
        xml.setAttribute ( "multidrag_sens" , MULTIDRAG_SENSITIVITY );
        xml.setAttribute ( "singledrag_sens" , SIMPLEDRAG_SENSITIVITY );
        xml.setAttribute ( "multidrag_on" , MULTIDRAG_ENABLE );
        xml.setAttribute ( "multidrag_right" , MULTIDRAG_AT_RIGHT_MOUSE );
        xml.setAttribute ( "mousewheel_enabled" , ENABLE_MOUSEWHEEL );
        xml.setAttribute ( "_2_1_info" , DONT_SHOW_AGAIN_2_1 );
        xml.setAttribute ( "check_for_updates" , AUTO_CHECK_UPDATES );
        xml.setAttribute ( "asked_for_autoupdate" , USER_ASKED_FOR_AUTO_UPDATE );
        xml.setAttribute ( "question_was_up" , QUESTION_WAS_UP );
    }

    void load_from( const XmlElement& xml )
    {
        LONG_MOUSE_DOWN_INTERVAL = xml.getIntAttribute ( "multidrag_time", 750 );
        MULTIDRAG_SENSITIVITY = xml.getDoubleAttribute ( "multidrag_sens", 0.2 );
        SIMPLEDRAG_SENSITIVITY = xml.getDoubleAttribute ( "singledrag_sens", 0.5 );
        MULTIDRAG_ENABLE = xml.getIntAttribute ( "multidrag_on", true );
        MULTIDRAG_AT_RIGHT_MOUSE = xml.getIntAttribute ( "multidrag_right", false );
        ENABLE_MOUSEWHEEL = xml.getIntAttribute ( "mousewheel_enabled", true );
        DONT_SHOW_AGAIN_2_1 = xml.getIntAttribute ( "_2_1_info", false );
        AUTO_CHECK_UPDATES = xml.getIntAttribute ( "check_for_updates", true );
        USER_ASKED_FOR_AUTO_UPDATE = xml.getIntAttribute ( "asked_for_autoupdate", false );
        QUESTION_WAS_UP = xml.getIntAttribute ( "question_was_up", false );
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GLOBAL_VALUE_HOLDER)
};

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

class FingerDrag : public Component
{
    Component* _root_view;
    Viewport* view;

    Point<int> _start_drag_position;

    bool is_mouse_down;
    bool is_dragging;

    void mouseDown( const MouseEvent& e_ ) override
    {
        if( is_mouse_down )
            return;

        int mouse_x = e_.getScreenPosition().getX();
        int mouse_y = e_.getScreenPosition().getY();
        int this_x = this->getScreenPosition().getX();
        int this_y = this->getScreenPosition().getY();

        if( dynamic_cast< ScrollBar* >( Desktop::getInstance().getMainMouseSource().getComponentUnderMouse() ) )
            return;
        else if( dynamic_cast< ScrollBar* >( Component::getCurrentlyFocusedComponent() ) )
	  return;

        // CHECK IF THE ROOT OF ALL FOCUSED COMPONENT IS THE FILE BROWSER
        Component*component = Component::getCurrentlyFocusedComponent();
        bool we_have_focus = false;
        while( component )
        {
            if( _root_view == component )
            {
                we_have_focus = true;
                break;
            }
            else
                component = component->getParentComponent();
        }
        if( we_have_focus )
        {
            if( mouse_x >= this_x && mouse_x <= this_x + getWidth() )
                if( mouse_y >= this_y && mouse_y <= this_y + getHeight() )
                {
                    unfocusAllComponents();
                    is_mouse_down = true;
                }
        }
    }
    void mouseUp( const MouseEvent& ) override
    {
        is_mouse_down = false;
        is_dragging = false;
        setInterceptsMouseClicks(false,false);
    }
    void mouseDrag( const MouseEvent& e_ ) override
    {
        if( ! is_mouse_down )
            return;

        if( ! is_dragging )
        {
            if (!(e_.getDistanceFromDragStart() > 40 || e_.getDistanceFromDragStart() < -40))
                return;
            else
            {
                setInterceptsMouseClicks(true,true);
                _start_drag_position = view->getViewPosition();
                is_dragging = true;
            }
        }

        view->setViewPosition( _start_drag_position.getX(), _start_drag_position.getY() - e_.getDistanceFromDragStartY() );
    }
public:
    FingerDrag( Viewport*view_to_move_, Component* root_view_ )
        :
        _root_view( root_view_ ),
        view( view_to_move_ ),
        is_mouse_down(false),
        is_dragging(false)
    {
        Desktop::getInstance().addGlobalMouseListener(this);
        setInterceptsMouseClicks(false,false);
    }
    ~FingerDrag()
    {
        Desktop::getInstance().removeGlobalMouseListener(this);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FingerDrag)
};

#endif  // APP_H_INCLUDED
