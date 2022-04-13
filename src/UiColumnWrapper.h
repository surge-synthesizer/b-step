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

#ifndef __JUCE_HEADER_8614586703E11C5E__
#define __JUCE_HEADER_8614586703E11C5E__

#include "App.h"
#include "Controller.h"
#include "UI_MoveEvent2ChildsComponent.h"

class UiColumn16;
class AppStyle;
struct SubeditorBase : public MoveEvent2ChildsComponent
{
  protected:
    AppStyle *_style;

  public:
    void set_style(AppStyle *const style_)
    {
        if (_style != style_)
        {
            _style = style_;
            on_style_set(_style);
        }
    }
    virtual void set_text(const juce::String &){};
    virtual void on_style_set(AppStyle *const){};
    virtual void set_background_style(AppStyle *const) {}
    virtual void refresh_ui(juce::Array<juce::Component *> &){};
    virtual void get_controllers_for_paint_popup(juce::Array<MONO_Controller *> &) {}
    virtual ModelBase *get_model(std::uint8_t) { return nullptr; };

    SubeditorBase() : _style(nullptr) {}
    virtual ~SubeditorBase() {}

    //==============================================================================
    JUCE_LEAK_DETECTOR(SubeditorBase)
};

class UiColumnWrapper : public juce::Component
{
  public:
    //==============================================================================
    UiColumnWrapper();
    ~UiColumnWrapper();

    //==============================================================================
  private:
    AppStyle *_style;

  public:
    void set_leftside_subeditor(SubeditorBase *const leftside_editor_);
    void set_colum_editor(UiColumn16 *const leftside_editor_);

    void set_style(AppStyle *const style_);

    // the text will only be set if the wrapped leftside editor have an label
    void set_text(const juce::String &text_) { leftside_subeditor->set_text(text_); };

    UiColumn16 *get_column_editor() { return column_editor.get(); }
    SubeditorBase *get_leftside_editor() { return leftside_subeditor.get(); }

    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_);
    void get_controllers_for_paint_popup(juce::Array<MONO_Controller *> &controllers_with_popup_);

    void paint(juce::Graphics &g);
    void resized();

  private:
    //==============================================================================
    std::unique_ptr<SubeditorBase> leftside_subeditor;
    std::unique_ptr<UiColumn16> column_editor;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiColumnWrapper)
};

#endif // __JUCE_HEADER_8614586703E11C5E__
