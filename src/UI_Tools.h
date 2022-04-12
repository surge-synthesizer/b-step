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

#ifndef __UI_TOOLS_H__
#define __UI_TOOLS_H__

#include "App.h"
#include "UI_Base.h"
#include "CoreDatastructure.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class UITool : public juce::DragAndDropContainer, public juce::ImageButton
{
  protected:
    juce::Image _curser_image;

    virtual const juce::Image &get_curser_image();

  private:
    virtual void mouseDrag(const juce::MouseEvent &e_) override;
    void mouseUp(const juce::MouseEvent &e_) override;
    void clicked() override;

  protected:
    AppInstanceStore *_app_instance_store;

    void set_app_instance_store(AppInstanceStore *const app_instance_store_)
    {
        _app_instance_store = app_instance_store_;
    }

    bool is_draged;

    UITool(const juce::String &name_);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UITool)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class UIRubber : public UITool
{
    std::unique_ptr<juce::Drawable> drawable;

    void paint(juce::Graphics &g_) override;

  public:
    void set_app_instance_store(AppInstanceStore *const app_instance_store_)
    {
        _app_instance_store = app_instance_store_;
    }

    UIRubber(const juce::String &);
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class UIQuestion : public UITool
{
    std::unique_ptr<juce::Drawable> drawable;

    void paint(juce::Graphics &g_) override;

  public:
    void set_app_instance_store(AppInstanceStore *const app_instance_store_)
    {
        _app_instance_store = app_instance_store_;
    }

    UIQuestion(const juce::String &);
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class BarCopyClipboard : public UIBarClipboardSettings
{
  public:
    Bar *stored_bar;

  public:
    BarCopyClipboard(std::uint8_t id_);
    ~BarCopyClipboard();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BarCopyClipboard)
};

class UiEditorClipboard;
class UIClipboard : public UITool, public juce::DragAndDropTarget
{
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    std::unique_ptr<juce::Component> drag_source;

  public:
    // PARAMETER
    AppInstanceStore *const _app_instance_store;
    GstepAudioProcessorEditor *const _main_window;
    const std::uint8_t id;
    BarCopyClipboard &_bar_copy_clipboard;

    std::unique_ptr<juce::Drawable> drawable;
    UiEditorClipboard *_editor;

    void paint(juce::Graphics &g_) override;
    void mouseDrag(const juce::MouseEvent &e_) override;
    void clicked() override;

    bool isInterestedInDragSource(const SourceDetails &dragSourceDetails_) override;
    void itemDropped(const SourceDetails &dragSourceDetails_) override;
    void dragOperationEnded(const juce::DragAndDropTarget::SourceDetails &) override;

  public:
    UIClipboard(AppInstanceStore *app_instance_store_, GstepAudioProcessorEditor *main_window_,
                std::uint8_t id_);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIClipboard)
};

#endif // __UI_TOOLS_H__
