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

#ifndef __JUCE_HEADER_F99A763C4421110E__
#define __JUCE_HEADER_F99A763C4421110E__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"

class UiTextImExport;
class UiTextImExportListener
{
    friend class UiTextImExport;

    const juce::String _title;
    bool _is_importer;

  protected:
    juce::String _data;

  private:
    virtual bool on_ok() = 0;
    virtual void on_chancel(){};

  protected:
    UiTextImExportListener(const juce::String &title_, const juce::String &default_text_,
                           bool is_importer_)
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
class UiTextImExport : public UiEditor, public juce::Timer, public juce::Button::Listener
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

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> titel;
    std::unique_ptr<juce::TextButton> ok;
    std::unique_ptr<juce::TextButton> cancel;
    std::unique_ptr<juce::TextEditor> text;
    std::unique_ptr<juce::TextButton> copy_past;
    std::unique_ptr<juce::Label> note;
    std::unique_ptr<juce::Label> description;
    std::unique_ptr<juce::TextButton> send_mail;
    std::unique_ptr<juce::TextButton> button_info;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiTextImExport)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_F99A763C4421110E__
