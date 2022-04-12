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

#ifndef __JUCE_HEADER_7652F95A41A347E0__
#define __JUCE_HEADER_7652F95A41A347E0__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"

//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class NewComponent : public juce::Component,
                     public juce::Slider::Listener,
                     public juce::ComboBox::Listener,
                     public juce::Button::Listener
{
  public:
    //==============================================================================
    NewComponent();
    ~NewComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint(juce::Graphics &g);
    void resized();
    void sliderValueChanged(juce::Slider *sliderThatWasMoved);
    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged);
    void buttonClicked(juce::Button *buttonThatWasClicked);

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> slider;
    std::unique_ptr<juce::ComboBox> comboBox;
    std::unique_ptr<juce::ComboBox> comboBox2;
    std::unique_ptr<juce::ComboBox> comboBox3;
    std::unique_ptr<juce::TextButton> textButton;
    std::unique_ptr<juce::TextButton> textButton2;
    std::unique_ptr<juce::ComboBox> comboBox4;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NewComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_7652F95A41A347E0__
