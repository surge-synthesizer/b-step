/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "UiLookAndFeel.h"
//[/Headers]

#include "mono_AmpPainter.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
void mono_AmpPainter::timerCallback() { repaint(); }

void mono_AmpPainter::refresh_buttons()
{
    ComponentColours colours = UiLookAndFeel::getInstance()->colours;
    juce::Colour button_on = colours.button_on_colour;
    juce::Colour button_off = colours.button_off_colour;

    osc_1->setColour(juce::TextButton::buttonColourId,
                     show_osc[0] ? juce::Colours::lightblue : button_off);
    osc_2->setColour(juce::TextButton::buttonColourId,
                     show_osc[1] ? juce::Colours::blueviolet : button_off);
    osc_3->setColour(juce::TextButton::buttonColourId,
                     show_osc[2] ? juce::Colours::violet : button_off);

    lfo_1->setColour(juce::TextButton::buttonColourId,
                     show_lfo[0] ? juce::Colours::green : button_off);
    lfo_2->setColour(juce::TextButton::buttonColourId,
                     show_lfo[1] ? juce::Colours::greenyellow : button_off);
    lfo_3->setColour(juce::TextButton::buttonColourId,
                     show_lfo[2] ? juce::Colours::yellow : button_off);

    f_1->setColour(juce::TextButton::buttonColourId,
                   show_filter[0] ? juce::Colours::red : button_off);
    f_2->setColour(juce::TextButton::buttonColourId,
                   show_filter[1] ? juce::Colours::orangered : button_off);
    f_3->setColour(juce::TextButton::buttonColourId,
                   show_filter[2] ? juce::Colours::orange : button_off);

    f_env_1->setColour(juce::TextButton::buttonColourId,
                       show_filter_env[0] ? juce::Colours::red : button_off);
    f_env_2->setColour(juce::TextButton::buttonColourId,
                       show_filter_env[1] ? juce::Colours::orangered : button_off);
    f_env_3->setColour(juce::TextButton::buttonColourId,
                       show_filter_env[2] ? juce::Colours::orange : button_off);

    out->setColour(juce::TextButton::buttonColourId,
                   show_out ? UiLookAndFeel::getInstance()->colours.slider_track_colour
                            : button_off);
    out_env->setColour(juce::TextButton::buttonColourId,
                       show_out_env
                           ? UiLookAndFeel::getInstance()->colours.slider_track_colour.darker()
                           : button_off);
}

//[/MiscUserDefs]

//==============================================================================
mono_AmpPainter::mono_AmpPainter() : original_w(1000), original_h(400)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible(sl_osc_octave_3 = new juce::Slider(juce::String()));
    sl_osc_octave_3->setRange(300, 44100, 1);
    sl_osc_octave_3->setSliderStyle(juce::Slider::LinearHorizontal);
    sl_osc_octave_3->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    sl_osc_octave_3->setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::yellow);
    sl_osc_octave_3->setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xff161616));
    sl_osc_octave_3->setColour(juce::Slider::textBoxTextColourId, juce::Colours::yellow);
    sl_osc_octave_3->addListener(this);

    addAndMakeVisible(osc_1 = new juce::TextButton("new button"));
    osc_1->setButtonText(TRANS("OSC 1"));
    osc_1->addListener(this);

    addAndMakeVisible(osc_2 = new juce::TextButton("new button"));
    osc_2->setButtonText(TRANS("OSC 2"));
    osc_2->addListener(this);

    addAndMakeVisible(osc_3 = new juce::TextButton("new button"));
    osc_3->setButtonText(TRANS("OSC 3"));
    osc_3->addListener(this);

    addAndMakeVisible(lfo_1 = new juce::TextButton("new button"));
    lfo_1->setButtonText(TRANS("LFO 1"));
    lfo_1->addListener(this);

    addAndMakeVisible(lfo_2 = new juce::TextButton("new button"));
    lfo_2->setButtonText(TRANS("LFO 2"));
    lfo_2->addListener(this);

    addAndMakeVisible(lfo_3 = new juce::TextButton("new button"));
    lfo_3->setButtonText(TRANS("LFO 3"));
    lfo_3->addListener(this);

    addAndMakeVisible(out = new juce::TextButton("new button"));
    out->setButtonText(TRANS("OUT"));
    out->addListener(this);

    addAndMakeVisible(f_1 = new juce::TextButton("new button"));
    f_1->setButtonText(TRANS("F 1"));
    f_1->addListener(this);

    addAndMakeVisible(f_2 = new juce::TextButton("new button"));
    f_2->setButtonText(TRANS("F 2"));
    f_2->addListener(this);

    addAndMakeVisible(f_3 = new juce::TextButton("new button"));
    f_3->setButtonText(TRANS("F 3"));
    f_3->addListener(this);

    addAndMakeVisible(f_env_1 = new juce::TextButton("new button"));
    f_env_1->setButtonText(TRANS("F-ADSR 1"));
    f_env_1->addListener(this);

    addAndMakeVisible(f_env_2 = new juce::TextButton("new button"));
    f_env_2->setButtonText(TRANS("F-ADSR 2"));
    f_env_2->addListener(this);

    addAndMakeVisible(f_env_3 = new juce::TextButton("new button"));
    f_env_3->setButtonText(TRANS("F-ADSR 3"));
    f_env_3->addListener(this);

    addAndMakeVisible(out_env = new juce::TextButton("new button"));
    out_env->setButtonText(TRANS("O-ADSR"));
    out_env->addListener(this);

    addAndMakeVisible(drawing_area = new Component());
    drawing_area->setName("");

    //[UserPreSize]
    resizer = 1;

    osc_values.add(new EndlessBuffer<float>());
    osc_values.add(new EndlessBuffer<float>());
    osc_values.add(new EndlessBuffer<float>());
    lfo_values.add(new EndlessBuffer<float>());
    lfo_values.add(new EndlessBuffer<float>());
    lfo_values.add(new EndlessBuffer<float>());
    filter_values.add(new EndlessBuffer<float>());
    filter_values.add(new EndlessBuffer<float>());
    filter_values.add(new EndlessBuffer<float>());
    filter_env_values.add(new EndlessBuffer<float>());
    filter_env_values.add(new EndlessBuffer<float>());
    filter_env_values.add(new EndlessBuffer<float>());

    buffers.add(osc_values[0]);
    buffers.add(osc_values[1]);
    buffers.add(osc_values[2]);
    buffers.add(lfo_values[0]);
    buffers.add(lfo_values[1]);
    buffers.add(lfo_values[2]);
    buffers.add(filter_values[0]);
    buffers.add(filter_values[1]);
    buffers.add(filter_values[2]);
    buffers.add(filter_env_values[0]);
    buffers.add(filter_env_values[1]);
    buffers.add(filter_env_values[2]);
    buffers.add(&values);
    buffers.add(&values_env);

    show_lfo.add(false);
    show_lfo.add(false);
    show_lfo.add(false);
    show_osc.add(false);
    show_osc.add(false);
    show_osc.add(false);
    show_filter.add(false);
    show_filter.add(false);
    show_filter.add(false);
    show_filter_env.add(false);
    show_filter_env.add(false);
    show_filter_env.add(false);

    show_out = true;
    show_out_env = false;
    show_lfo_mix = false;

    refresh_buttons();

    setOpaque(true);
    //[/UserPreSize]

    setSize(1000, 400);

    //[Constructor] You can add your own custom stuff here..
    sl_osc_octave_3->setValue(2048);

    startTimer(40);
    //[/Constructor]
}

mono_AmpPainter::~mono_AmpPainter()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    sl_osc_octave_3 = nullptr;
    osc_1 = nullptr;
    osc_2 = nullptr;
    osc_3 = nullptr;
    lfo_1 = nullptr;
    lfo_2 = nullptr;
    lfo_3 = nullptr;
    out = nullptr;
    f_1 = nullptr;
    f_2 = nullptr;
    f_3 = nullptr;
    f_env_1 = nullptr;
    f_env_2 = nullptr;
    f_env_3 = nullptr;
    out_env = nullptr;
    drawing_area = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void mono_AmpPainter::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    {
        g.fillAll(juce::Colour(0xff101010));

        // TODO MAKE INTS!
        const int size = sl_osc_octave_3->getValue();
        float scale = float(drawing_area->getWidth()) / size;
        const int paint_start_offset_x = drawing_area->getX();
        const int paint_start_offset_y = drawing_area->getY();
        const float height = drawing_area->getHeight();
        const int line_center = paint_start_offset_y + height / 2;

        const int current_position = osc_values[0]->get_current_position(0);
        const int past_offaset = osc_values[0]->get_past_offset();

        {
            juce::Colour colour = juce::Colour(0xff444444);
            g.setGradientFill(juce::ColourGradient(colour.darker(0.3f), 0.0f, 0.0f,
                                                   juce::Colour(0xff161617), 0.0f, height, false));
            // g.setGradientFill (ColourGradient (color_1, 0.0f, 0.0f, color_1.darker (0.3f), 0.0f,
            // height, false));
            g.fillRoundedRectangle(proportionOfWidth(0.170f), proportionOfHeight(0.0375f),
                                   proportionOfWidth(0.8150f), proportionOfHeight(0.825f), 3);

            g.setColour(colour.darker(0.6f));
            g.drawRoundedRectangle(proportionOfWidth(0.170f), proportionOfHeight(0.0375f),
                                   proportionOfWidth(0.8150f), proportionOfHeight(0.825f), 3, 1);

            g.setColour(UiLookAndFeel::getInstance()->colours.label_text_colour.withAlpha(0.3f));
            g.fillRect(proportionOfWidth(0.170f), int(paint_start_offset_y + height / 2),
                       proportionOfWidth(0.8150f), 1);
        }

        struct mono_AmpPainter
        {
            static void exec(juce::Graphics &g,

                             const int buffer_pos_, const float scale_,

                             const int x_offset_, const int y_center_, const int height_,

                             const juce::Colour &col_,

                             EndlessBuffer<float> &source_buffer_, int num_samples_)
            {
                const juce::Colour col_fill(col_.withAlpha(0.1f));
                int last_x = -9999;
                int last_y = -9999;
                for (int sid = 0; sid < num_samples_; ++sid)
                {
                    const int x = std::floor((scale_ * sid) + x_offset_);
                    float y = source_buffer_.get(buffer_pos_, sid);
                    bool paint_line = true;
                    if (last_x == x)
                    {
                        paint_line = false;
                    }
                    {
                        if (y >= 0)
                        {
                            if (y > 1)
                                y = 1;

                            int h = mono_floor(y * height_) / 2;

                            if (paint_line)
                            {
                                g.setColour(col_fill);
                                g.fillRect(x, y_center_ - h, 1, h);
                            }
                            if (last_y != y || last_x == x)
                            {
                                g.setColour(col_);
                                g.fillRect(x, y_center_ - h, 1, 1);

                                last_y = y;
                            }
                        }
                        else
                        {
                            if (y < -1)
                                y = -1;

                            int h = mono_floor(y * height_) * -1 / 2;
                            if (paint_line)
                            {
                                g.setColour(col_fill);
                                g.fillRect(x, y_center_, 1, h);
                            }
                            if (last_y != y || last_x == x)
                            {
                                g.setColour(col_);
                                g.fillRect(x, y_center_ + h, 1, 1);

                                last_y = y;
                            }
                        }

                        last_x = x;
                    }
                }
            }
        };

        for (int osc_id = 0; osc_id != osc_values.size(); ++osc_id)
        {
            EndlessBuffer<float> &values = *osc_values[osc_id];
            if (show_osc[osc_id])
            {
                juce::Colour col;
                if (osc_id == 0)
                    col = juce::Colours::lightblue;
                else if (osc_id == 1)
                    col = juce::Colours::blueviolet;
                else
                    col = juce::Colours::violet;

                mono_AmpPainter::exec(g,

                                      current_position, scale,

                                      paint_start_offset_x, line_center, height,

                                      col, values, size);
            }
        }

        for (int lfo_id = 0; lfo_id != lfo_values.size(); ++lfo_id)
        {
            EndlessBuffer<float> &values = *lfo_values[lfo_id];
            if (show_lfo[lfo_id])
            {
                juce::Colour col;
                if (lfo_id == 0)
                    col = juce::Colours::green;
                else if (lfo_id == 1)
                    col = juce::Colours::greenyellow;
                else
                    col = juce::Colours::yellow;

                mono_AmpPainter::exec(g,

                                      current_position, scale,

                                      paint_start_offset_x, line_center, height,

                                      col, values, size);
            }
        }

        for (int filter_id = 0; filter_id != lfo_values.size(); ++filter_id)
        {
            juce::Colour col;
            if (filter_id == 0)
                col = juce::Colours::red;
            else if (filter_id == 1)
                col = juce::Colours::orangered;
            else
                col = juce::Colours::orange;

            EndlessBuffer<float> &values = *filter_values[filter_id];
            if (show_filter[filter_id])
            {
                mono_AmpPainter::exec(g,

                                      current_position, scale,

                                      paint_start_offset_x, line_center, height,

                                      col, values, size);
            }

            EndlessBuffer<float> &values_env = *filter_env_values[filter_id];
            if (show_filter_env[filter_id])
            {
                mono_AmpPainter::exec(g,

                                      current_position, scale,

                                      paint_start_offset_x, line_center, height,

                                      col, values_env, size);
            }
        }

        const int out_position = values.get_current_position(past_offaset);
        if (show_out)
        {
            mono_AmpPainter::exec(g,

                                  out_position, scale,

                                  paint_start_offset_x, line_center, height,

                                  UiLookAndFeel::getInstance()->colours.slider_track_colour, values,
                                  size);
        }

        if (show_out_env)
        {
            mono_AmpPainter::exec(
                g,

                out_position, scale,

                paint_start_offset_x, line_center, height,

                UiLookAndFeel::getInstance()->colours.slider_track_colour.darker(), values_env,
                size);
        }
    }

    return;
    //[/UserPrePaint]

    g.fillAll(juce::Colours::black);

    g.setGradientFill(juce::ColourGradient(
        juce::Colour(0xff161616), static_cast<float>(proportionOfWidth(0.5000f)),
        static_cast<float>(proportionOfHeight(0.0375f)), juce::Colour(0x00000000),
        static_cast<float>(proportionOfWidth(0.5000f)),
        static_cast<float>(proportionOfHeight(0.0625f)), false));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setGradientFill(juce::ColourGradient(
        juce::Colour(0xff161616), static_cast<float>(proportionOfWidth(0.1700f)),
        static_cast<float>(proportionOfHeight(0.5000f)), juce::Colour(0x00000000),
        static_cast<float>(proportionOfWidth(0.1800f)),
        static_cast<float>(proportionOfHeight(0.5000f)), false));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setGradientFill(juce::ColourGradient(
        juce::Colour(0xff161616), static_cast<float>(proportionOfWidth(0.9850f)),
        static_cast<float>(proportionOfHeight(0.5000f)), juce::Colour(0x00000000),
        static_cast<float>(proportionOfWidth(0.9750f)),
        static_cast<float>(proportionOfHeight(0.5000f)), false));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setGradientFill(juce::ColourGradient(
        juce::Colour(0xff161616), static_cast<float>(proportionOfWidth(0.5000f)),
        static_cast<float>(proportionOfHeight(0.8625f)), juce::Colour(0x00000000),
        static_cast<float>(proportionOfWidth(0.5000f)),
        static_cast<float>(proportionOfHeight(0.8375f)), false));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setGradientFill(juce::ColourGradient(
        juce::Colour(0xff2b3524), static_cast<float>(proportionOfWidth(0.5750f)),
        static_cast<float>(proportionOfHeight(1.5875f)), juce::Colours::black,
        static_cast<float>(proportionOfWidth(0.5750f)),
        static_cast<float>(proportionOfHeight(0.0125f)), true));
    g.fillRect(proportionOfWidth(0.1650f), proportionOfHeight(0.0275f), proportionOfWidth(0.8250f),
               proportionOfHeight(0.8475f));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void mono_AmpPainter::resized()
{
    //[UserPreResize] Add your own custom resize code here..
#include "UiDynamicSizeStart.h"
    //[/UserPreResize]

    sl_osc_octave_3->setBounds(170, 360, 820, 30);
    osc_1->setBounds(10, 15, 40, 50);
    osc_2->setBounds(10, 75, 40, 50);
    osc_3->setBounds(10, 135, 40, 50);
    lfo_1->setBounds(10, 215, 40, 50);
    lfo_2->setBounds(10, 275, 40, 50);
    lfo_3->setBounds(10, 335, 40, 50);
    out->setBounds(115, 15, 40, 50);
    f_1->setBounds(60, 15, 40, 50);
    f_2->setBounds(60, 75, 40, 50);
    f_3->setBounds(60, 135, 40, 50);
    f_env_1->setBounds(60, 215, 40, 50);
    f_env_2->setBounds(60, 275, 40, 50);
    f_env_3->setBounds(60, 335, 40, 50);
    out_env->setBounds(115, 75, 40, 50);
    drawing_area->setBounds(170, 15, 815, 330);
    //[UserResized] Add your own custom resize handling here..

#include "UiDynamicSizeEnd.h"
    //[/UserResized]
}

void mono_AmpPainter::sliderValueChanged(juce::Slider *sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sl_osc_octave_3)
    {
        //[UserSliderCode_sl_osc_octave_3] -- add your slider handling code here..
        for (int i = 0; i != buffers.size(); ++i)
            buffers.getReference(i)->set_size(sl_osc_octave_3->getValue());

        //[/UserSliderCode_sl_osc_octave_3]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void mono_AmpPainter::buttonClicked(juce::Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == osc_1)
    {
        //[UserButtonCode_osc_1] -- add your button handler code here..
        show_osc.getReference(0) ^= true;
        //[/UserButtonCode_osc_1]
    }
    else if (buttonThatWasClicked == osc_2)
    {
        //[UserButtonCode_osc_2] -- add your button handler code here..
        show_osc.getReference(1) ^= true;
        //[/UserButtonCode_osc_2]
    }
    else if (buttonThatWasClicked == osc_3)
    {
        //[UserButtonCode_osc_3] -- add your button handler code here..
        show_osc.getReference(2) ^= true;
        //[/UserButtonCode_osc_3]
    }
    else if (buttonThatWasClicked == lfo_1)
    {
        //[UserButtonCode_lfo_1] -- add your button handler code here..
        show_lfo.getReference(0) ^= true;
        //[/UserButtonCode_lfo_1]
    }
    else if (buttonThatWasClicked == lfo_2)
    {
        //[UserButtonCode_lfo_2] -- add your button handler code here..
        show_lfo.getReference(1) ^= true;
        //[/UserButtonCode_lfo_2]
    }
    else if (buttonThatWasClicked == lfo_3)
    {
        //[UserButtonCode_lfo_3] -- add your button handler code here..
        show_lfo.getReference(2) ^= true;
        //[/UserButtonCode_lfo_3]
    }
    else if (buttonThatWasClicked == out)
    {
        //[UserButtonCode_out] -- add your button handler code here..
        show_out ^= true;
        //[/UserButtonCode_out]
    }
    else if (buttonThatWasClicked == f_1)
    {
        //[UserButtonCode_f_1] -- add your button handler code here..
        show_filter.getReference(0) ^= true;
        //[/UserButtonCode_f_1]
    }
    else if (buttonThatWasClicked == f_2)
    {
        //[UserButtonCode_f_2] -- add your button handler code here..
        show_filter.getReference(1) ^= true;
        //[/UserButtonCode_f_2]
    }
    else if (buttonThatWasClicked == f_3)
    {
        //[UserButtonCode_f_3] -- add your button handler code here..
        show_filter.getReference(2) ^= true;
        //[/UserButtonCode_f_3]
    }
    else if (buttonThatWasClicked == f_env_1)
    {
        //[UserButtonCode_f_env_1] -- add your button handler code here..
        show_filter_env.getReference(0) ^= true;
        //[/UserButtonCode_f_env_1]
    }
    else if (buttonThatWasClicked == f_env_2)
    {
        //[UserButtonCode_f_env_2] -- add your button handler code here..
        show_filter_env.getReference(1) ^= true;
        //[/UserButtonCode_f_env_2]
    }
    else if (buttonThatWasClicked == f_env_3)
    {
        //[UserButtonCode_f_env_3] -- add your button handler code here..
        show_filter_env.getReference(2) ^= true;
        //[/UserButtonCode_f_env_3]
    }
    else if (buttonThatWasClicked == out_env)
    {
        //[UserButtonCode_out_env] -- add your button handler code here..
        show_out_env ^= true;
        //[/UserButtonCode_out_env]
    }

    //[UserbuttonClicked_Post]
    refresh_buttons();
    //[/UserbuttonClicked_Post]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void mono_AmpPainter::add_filter_env(int id_, const float *values_, int num_samples_) noexcept
{
    for (int i = 0; i != num_samples_; ++i)
        filter_env_values.getUnchecked(id_)->add(values_[i]);
}
void mono_AmpPainter::add_filter(int id_, const float *values_, int num_samples_) noexcept
{
    for (int i = 0; i != num_samples_; ++i)
        filter_values.getUnchecked(id_)->add(values_[i]);
}
void mono_AmpPainter::add_out_env(const float *values_, int num_samples_) noexcept
{
    for (int i = 0; i != num_samples_; ++i)
        values_env.add(values_[i]);
}
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="mono_AmpPainter" componentName=""
                 parentClasses="public Component, public Timer" constructorParams=""
                 variableInitialisers="original_w(1000), original_h(400)" snapPixels="5"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="1000" initialHeight="400">
  <BACKGROUND backgroundColour="ff000000">
    <RECT pos="0 0 0M 0M" fill="linear: 50% 3.75%, 50% 6.25%, 0=ff161616, 1=0"
          hasStroke="0"/>
    <RECT pos="0 0 0M 0M" fill="linear: 17% 50%, 18% 50%, 0=ff161616, 1=0"
          hasStroke="0"/>
    <RECT pos="0 0 0M 0M" fill="linear: 98.5% 50%, 97.5% 50%, 0=ff161616, 1=0"
          hasStroke="0"/>
    <RECT pos="0 0 0M 0M" fill="linear: 50% 86.25%, 50% 83.75%, 0=ff161616, 1=0"
          hasStroke="0"/>
    <RECT pos="16.5% 2.75% 82.5% 84.75%" fill=" radial: 57.5% 158.75%, 57.5% 1.25%, 0=ff2b3524, 1=ff000000"
          hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="" id="6770eaa357af0c63" memberName="sl_osc_octave_3" virtualName=""
          explicitFocusOrder="0" pos="170 360 820 30" rotarysliderfill="ffffff00"
          rotaryslideroutline="ff161616" textboxtext="ffffff00" min="300"
          max="44100" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="new button" id="f50c5e2947daf2d9" memberName="osc_1" virtualName=""
              explicitFocusOrder="0" pos="10 15 40 50" buttonText="OSC 1" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="430b47338d775167" memberName="osc_2" virtualName=""
              explicitFocusOrder="0" pos="10 75 40 50" buttonText="OSC 2" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="2c8665efd6c0c37d" memberName="osc_3" virtualName=""
              explicitFocusOrder="0" pos="10 135 40 50" buttonText="OSC 3"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="80760cb7f2a9d968" memberName="lfo_1" virtualName=""
              explicitFocusOrder="0" pos="10 215 40 50" buttonText="LFO 1"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="70c88d44ebc2f40" memberName="lfo_2" virtualName=""
              explicitFocusOrder="0" pos="10 275 40 50" buttonText="LFO 2"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="c6c837d559f009a2" memberName="lfo_3" virtualName=""
              explicitFocusOrder="0" pos="10 335 40 50" buttonText="LFO 3"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="13f5cd2a936d7f93" memberName="out" virtualName=""
              explicitFocusOrder="0" pos="115 15 40 50" buttonText="OUT" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="b51569f32393a334" memberName="f_1" virtualName=""
              explicitFocusOrder="0" pos="60 15 40 50" buttonText="F 1" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="773e5360237ed15c" memberName="f_2" virtualName=""
              explicitFocusOrder="0" pos="60 75 40 50" buttonText="F 2" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="60cf3f432ebdbf40" memberName="f_3" virtualName=""
              explicitFocusOrder="0" pos="60 135 40 50" buttonText="F 3" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="3aa1b921ef4aea49" memberName="f_env_1"
              virtualName="" explicitFocusOrder="0" pos="60 215 40 50" buttonText="F-ADSR 1"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="68fc0bbd2cf58e73" memberName="f_env_2"
              virtualName="" explicitFocusOrder="0" pos="60 275 40 50" buttonText="F-ADSR 2"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="1d48bab8b4aaf7c9" memberName="f_env_3"
              virtualName="" explicitFocusOrder="0" pos="60 335 40 50" buttonText="F-ADSR 3"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="733cb649c95fb68" memberName="out_env" virtualName=""
              explicitFocusOrder="0" pos="115 75 40 50" buttonText="O-ADSR"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="87835d83e09366f2" memberName="drawing_area"
                    virtualName="" explicitFocusOrder="0" pos="170 15 815 330" class="Component"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
