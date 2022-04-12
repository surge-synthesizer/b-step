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

#ifndef __JUCE_HEADER_B1D3D35915111CF0__
#define __JUCE_HEADER_B1D3D35915111CF0__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"

class AppInstanceStore;
class GstepAudioProcessorEditor;

class UIRubber;
class UIQuestion;
class UIClipboard;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MenuBarRight : public juce::Component, public juce::Button::Listener
{
  public:
    //==============================================================================
    MenuBarRight(AppInstanceStore *const app_instance_store_,
                 GstepAudioProcessorEditor *const main_window_);
    ~MenuBarRight();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;
    GstepAudioProcessorEditor *const _main_window;

    void mouseDown(const juce::MouseEvent &e_) override;

    std::int32_t last_painted_colour;
    juce::Array<juce::Drawable *> drawables;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // UI REFRESH
  public:
    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_);

    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;

    // Binary resources:
    static const char *load_svg;
    static const int load_svgSize;
    static const char *save_svg;
    static const int save_svgSize;
    static const char *learn_svg;
    static const int learn_svgSize;
    static const char *info_svg;
    static const int info_svgSize;
    static const char *panic_svg;
    static const int panic_svgSize;
    static const char *settings_svg;
    static const int settings_svgSize;
    static const char *drag_svg;
    static const int drag_svgSize;
    static const char *connection_svg;
    static const int connection_svgSize;
    static const char *trash_svg;
    static const int trash_svgSize;
    static const char *paint_svg;
    static const int paint_svgSize;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ImageButton> open_settings_editor;
    std::unique_ptr<juce::ImageButton> do_midi_learn;
    std::unique_ptr<juce::ImageButton> open_about_window;
    std::unique_ptr<juce::ImageButton> save_preset;
    std::unique_ptr<juce::ImageButton> panic;
    std::unique_ptr<juce::ImageButton> load_preset;
    std::unique_ptr<UIRubber> button_rubber;
    std::unique_ptr<UIQuestion> button_question;
    std::unique_ptr<UIClipboard> button_clipboard_1;
    std::unique_ptr<UIClipboard> button_clipboard_2;
    std::unique_ptr<UIClipboard> button_clipboard_3;
    std::unique_ptr<UIClipboard> button_clipboard_4;
    std::unique_ptr<juce::ImageButton> open_setup_editor;
    std::unique_ptr<juce::ImageButton> clear_project;
    std::unique_ptr<juce::ImageButton> open_styler;
    std::unique_ptr<juce::Drawable> drawable1;
    std::unique_ptr<juce::Drawable> drawable2;
    std::unique_ptr<juce::Drawable> drawable3;
    std::unique_ptr<juce::Drawable> drawable4;
    std::unique_ptr<juce::Drawable> drawable5;
    std::unique_ptr<juce::Drawable> drawable6;
    std::unique_ptr<juce::Drawable> drawable7;
    std::unique_ptr<juce::Drawable> drawable8;
    std::unique_ptr<juce::Drawable> drawable9;
    std::unique_ptr<juce::Drawable> drawable10;
    std::unique_ptr<juce::Drawable> drawable11;
    std::unique_ptr<juce::Drawable> drawable12;
    std::unique_ptr<juce::Drawable> drawable13;
    std::unique_ptr<juce::Drawable> drawable14;
    std::unique_ptr<juce::Drawable> drawable15;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuBarRight)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_B1D3D35915111CF0__
