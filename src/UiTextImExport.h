/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_F99A763C4421110E__
#define __JUCE_HEADER_F99A763C4421110E__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"

class UiTextImExport;
class UiTextImExportListener
{
    friend class UiTextImExport;

    const String _title;
    bool _is_importer;

  protected:
    String _data;

  private:
    virtual bool on_ok() = 0;
    virtual void on_chancel(){};

  protected:
    UiTextImExportListener(const String &title_, const String &default_text_, bool is_importer_)
        : _title(title_), _is_importer(is_importer_), _data(default_text_)
    {
    }

    virtual ~UiTextImExportListener() {}

  private:
    UiTextImExportListener();

    // returns false if the editor should be keep opend
    void perform_ok(bool &success_)
    {
        if (on_ok())
        {
            success_ = true;
            delete this;
            return;
        }

        success_ = false;
    }
    // returns false if the editor should be keep opend
    void perform_chancel()
    {
        on_chancel();
        delete this;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiTextImExportListener)
};
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiTextImExport : public UiEditor, public Timer, public Button::Listener
{
  public:
    //==============================================================================
    UiTextImExport(AppInstanceStore *const app_instance_store_,
                   UiTextImExportListener *const listener_);
    ~UiTextImExport();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;
    UiTextImExportListener *const _listener;

    void timerCallback() override;
    void on_close_clicked() override;
    //[/UserMethods]

    void paint(Graphics &g) override;
    void resized() override;
    void buttonClicked(Button *buttonThatWasClicked) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> titel;
    ScopedPointer<TextButton> ok;
    ScopedPointer<TextButton> cancel;
    ScopedPointer<TextEditor> text;
    ScopedPointer<TextButton> copy_past;
    ScopedPointer<Label> note;
    ScopedPointer<Label> description;
    ScopedPointer<TextButton> send_mail;
    ScopedPointer<TextButton> send_mail_to_monoplugs;
    ScopedPointer<TextButton> button_info;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiTextImExport)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_F99A763C4421110E__
