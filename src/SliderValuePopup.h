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

#ifndef __JUCE_HEADER_D1021F64E2F7918__
#define __JUCE_HEADER_D1021F64E2F7918__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
class ModelBase;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SliderValuePopup : public juce::Component
{
  public:
    //==============================================================================
    SliderValuePopup(const ModelBase *const model_);
    ~SliderValuePopup();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
  private:
    juce::String _text;
    const ModelBase *const _model;

  public:
    void set_text(juce::String &value_);
    //[/UserMethods]

    void paint(juce::Graphics &g);
    void resized();

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SliderValuePopup)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_D1021F64E2F7918__
