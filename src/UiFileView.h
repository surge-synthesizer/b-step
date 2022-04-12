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

#ifndef __JUCE_HEADER_267DD144E1A31482__
#define __JUCE_HEADER_267DD144E1A31482__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"

class UiFileView;
class FileViewOwner
{
    friend class UiFileView;
    virtual void on_view_delete(UiFileView *const) = 0;

  protected:
    virtual ~FileViewOwner() {}

    JUCE_LEAK_DETECTOR(FileViewOwner)
};

class UiFileViewListener
{
    friend class UiFileView;
    virtual void on_text_changed(juce::String &new_text_) = 0;
    virtual void on_text_chancel() = 0;

  protected:
    virtual ~UiFileViewListener() {}

    JUCE_LEAK_DETECTOR(UiFileViewListener)
};
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiFileView : public juce::TextButton,
                   public juce::Timer,
                   public juce::TextEditor::Listener,
                   public juce::Button::Listener,
                   public juce::Slider::Listener
{
  public:
    //==============================================================================
    UiFileView();
    ~UiFileView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    FileViewOwner *_owner;
    void set_owner(FileViewOwner *const owner_) { _owner = owner_; }

    void set_label_text(const juce::String &);
    void add_button_listener(juce::Button::Listener *const listener_)
    {
        imageButton->addListener(listener_);
    }
    void show_slider(bool state) { player_slider->setVisible(state); }
    juce::Slider *get_thumb() const { return player_slider.get(); }

    int label_offset;
    void set_label_x_offset(int label_offset_) { label_offset = label_offset_; }

    void set_label_color(std::uint32_t color)
    {
        label->setColour(juce::TextEditor::textColourId, juce::Colour(color));

        // FORCE COLOR REPAINT
        juce::String temp_text = label->getText();
        label->setText("");
        label->setText(temp_text, false);
    }

    UiFileViewListener *_listener;
    bool is_notified;
    void set_input_listener(UiFileViewListener *const input_listener_,
                            const juce::String &default_name_)
    {
        is_notified = false;

        imageButton->toBack();
        label->toFront(false);

        _listener = input_listener_;
        label->setText(default_name_);
        startTimer(350);
        label->grabKeyboardFocus();
    }

    void timerCallback() override
    {
        label->toFront(false);

        label->setText(label->getText());
        label->addListener(this);
        label->setWantsKeyboardFocus(true);
        label->grabKeyboardFocus();

        stopTimer();
    }

    void textEditorEscapeKeyPressed(juce::TextEditor &) override
    {
        if (_listener && !is_notified)
        {
            is_notified = true;
            grabKeyboardFocus();

            _listener->on_text_chancel();
            _listener = nullptr;

            label->toBack();
            imageButton->toFront(true);

            // FORCE COLOR REPAINT
            juce::String temp_text = label->getText();
            label->setText("");
            label->setText(temp_text, false);

            OUT("ESC");
        }
    }
    void textEditorReturnKeyPressed(juce::TextEditor &te_) override
    {
        if (_listener && !is_notified)
        {
            is_notified = true;
            grabKeyboardFocus();

            juce::String text = te_.getText();
            _listener->on_text_changed(text);
            te_.setText(text, false);
            _listener = nullptr;

            label->toBack();
            imageButton->toFront(true);

            // FORCE COLOR REPAINT
            juce::String temp_text = label->getText();
            label->setText("");
            label->setText(temp_text, false);
        }
    }
    void textEditorFocusLost(juce::TextEditor &te_) override
    {
        if (juce::Desktop::getInstance().findComponentAt(
                juce::Desktop::getLastMouseDownPosition()) == label.get())
        {
            te_.grabKeyboardFocus();
            return;
        }
        textEditorEscapeKeyPressed(te_);
    }

    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void sliderValueChanged(juce::Slider *sliderThatWasMoved) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::TextEditor> label;
    std::unique_ptr<juce::ImageButton> imageButton;
    std::unique_ptr<juce::Slider> player_slider;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiFileView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_267DD144E1A31482__
