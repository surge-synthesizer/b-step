#ifndef __UI_TOOLS_H__
#define __UI_TOOLS_H__

#include "App.h"
#include "UI_Base.h"
#include "CoreDatastructure.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class UITool :
    public DragAndDropContainer,
    public ImageButton
{
protected:
    Image _curser_image;

    virtual const Image& get_curser_image();

private:
    virtual void mouseDrag ( const MouseEvent& e_ ) override;
    void mouseUp( const MouseEvent& e_ );
    void clicked() override;

protected:
    AppInstanceStore* _app_instance_store;

    void set_app_instance_store( AppInstanceStore*const app_instance_store_  ) {
        _app_instance_store = app_instance_store_;
    }

    bool is_draged;

    UITool( const String& name_ );

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR ( UITool )
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class UIRubber : public UITool
{
    ScopedPointer<Drawable> drawable;

    void paint( Graphics& g_ ) override;

public:
    void set_app_instance_store( AppInstanceStore*const app_instance_store_  ) {
        _app_instance_store = app_instance_store_;
    }

    UIRubber( const String& );
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class UIQuestion : public UITool
{
    ScopedPointer< Drawable > drawable;

    void paint( Graphics& g_ ) override;

public:
    void set_app_instance_store( AppInstanceStore*const app_instance_store_  ) {
        _app_instance_store = app_instance_store_;
    }

    UIQuestion( const String& );
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class BarCopyClipboard : public UIBarClipboardSettings
{
public:
    Bar* stored_bar;

public:
    BarCopyClipboard( uint8 id_ );
    ~BarCopyClipboard();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR ( BarCopyClipboard )
};

class UiEditorClipboard;
class UIClipboard : public UITool, public DragAndDropTarget
{
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    ScopedPointer<Component> drag_source;

public:
    // PARAMETER
    AppInstanceStore*const _app_instance_store;
    GstepAudioProcessorEditor*const _main_window;
    const uint8 id;
    BarCopyClipboard& _bar_copy_clipboard;

    ScopedPointer< Drawable > drawable;
    UiEditorClipboard* _editor;

    void paint( Graphics& g_ ) override;
    void mouseDrag ( const MouseEvent& e_ ) override;
    void clicked() override;

    bool isInterestedInDragSource ( const SourceDetails& dragSourceDetails_ ) override;
    void itemDropped ( const SourceDetails& dragSourceDetails_ ) override;
    void dragOperationEnded(const DragAndDropTarget::SourceDetails &) override;

public:
    UIClipboard( AppInstanceStore* app_instance_store_,
                 GstepAudioProcessorEditor*main_window_,
                 uint8 id_ );

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR ( UIClipboard )
};

#endif // __UI_TOOLS_H__


