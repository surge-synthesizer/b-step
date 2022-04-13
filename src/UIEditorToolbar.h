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

#ifndef __JUCE_HEADER_77F0CE91B2F32968__
#define __JUCE_HEADER_77F0CE91B2F32968__

#include "App.h"

class AnimateMove;
class UiEditorInputPopup;

class UiEditor : public juce::ResizableWindow
{
    friend class UiEditorToolbar;
    virtual void on_load_clicked() {}
    virtual void on_save_clicked() {}

  public:
    virtual void on_close_clicked() {}

  private:
    void closeButtonPressed()
    { /*override only in standaline*/
        on_close_clicked();
    }

    friend class AnimateMove;
    volatile bool animate_lock;
    AnimateMove *_animate_mover;

  protected:
    UiEditor(juce::String name = "B-Info");
    ~UiEditor();

    void center_relative_and_make_visible(juce::Component *const parent_ = nullptr,
                                          bool resize_ = true, bool make_labels_dragable_ = true);
    void restore_XY(juce::Point<int> &XY_);
    void make_childs_dragable();

    bool canModalEventBeSentToComponent(const juce::Component *) override { return true; }

  public:
    void animate_move(int y_to_move_);
    void animate_move_back();
};

//==============================================================================

class UiEditorToolbar : public juce::Component, public juce::Button::Listener
{
  public:
    //==============================================================================
    UiEditorToolbar(UiEditor *const owner_editor_, bool show_close = true, bool show_move = true,
                    bool show_load_save = true);
    ~UiEditorToolbar();

    //==============================================================================
    UiEditor *const _owner_editor;

    void paint(juce::Graphics &g);
    void resized();
    void buttonClicked(juce::Button *buttonThatWasClicked);

    // Binary resources:
    static const char *load_svg;
    static const int load_svgSize;
    static const char *save_svg;
    static const int save_svgSize;
    static const char *move_svg;
    static const int move_svgSize;
    static const char *close_svg;
    static const int close_svgSize;

  private:
    //==============================================================================
    std::unique_ptr<juce::ImageButton> close;
    std::unique_ptr<juce::ImageButton> load;
    std::unique_ptr<juce::ImageButton> save;
    std::unique_ptr<juce::Drawable> drawable1;
    std::unique_ptr<juce::Drawable> drawable2;
    std::unique_ptr<juce::Drawable> drawable3;
    std::unique_ptr<juce::Drawable> drawable4;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorToolbar)
};

#endif // __JUCE_HEADER_77F0CE91B2F32968__
