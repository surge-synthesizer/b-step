/*
  ==============================================================================

    Created: spät
    Author:  monotomy

  ==============================================================================
*/

#ifndef CONRTOLLER_CONFIG_INCLUDED
#define CONRTOLLER_CONFIG_INCLUDED

#include "App.h"

#include "Controller.h"

#include "AppStyles.h"

#include "UiSettings.h"
#include "_H_UiElements.h"

#include "MIDILearn.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class MONO_UIButtonController : public MONO_Controller
{
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // IDENTING

    const char *get_controller_type_ident() const override
    {
        PodParameterBase *const param = get_parameter();
        if (param)
            return param->get_param_unique_ident();

        return nullptr;
    }

    virtual const juce::String &get_controller_name() const override
    {
        PodParameterBase *const param = get_parameter();
        if (param)
            return param->name();

        return _no_conroller;
    }

    virtual UI_VIEW_TYPES get_view_type() override { return UI_VIEW_TYPES::UI_BUTTON; }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // SET VALUE HANDLING
    virtual void on_clicked_top() override
    {
        PodParameterBase *param = get_parameter();
        if (param)
        {
#ifndef IS_REMOTE_CONTROLLER
            param->beginChangeGesture();
            param->invert();
            param->notifyCurrent();
            param->endChangeGesture();
#else
            param->set_remote_value(param->value() == 1 ? 0 : 1);
#endif
        }
    }

    virtual void on_value_changed(int v_) override
    {
        PodParameterBase *param = get_parameter();
        if (param)
        {
#ifndef IS_REMOTE_CONTROLLER
            param->beginChangeGesture();
            param->set_value_notifying_host(v_);
            param->endChangeGesture();
#else
            param->set_remote_value(v_);
#endif
        }
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // GET VALUE HANDLING
  protected:
    enum STATES
    {
        OFF_1 = false,
        ON_1 = true,
        OFF_2,
        ON_2
    };

  private:
    virtual unsigned int get_current_state() const
    {
        PodParameterBase *param = get_parameter();
        if (param)
            return param->value();

        return STATES::OFF_1;
    }

    // Override this if you have more than two states
    virtual int get_range_max() override { return true; }
    virtual int get_range_min() override { return false; }

    virtual int get_value() const override { return get_current_state(); }

    virtual std::uint32_t get_current_color() const override
    {
        if (_model)
        {
            unsigned int state_value = get_current_state();

            // USER DEFINED IMPL
            switch (state_value)
            {
            case STATES::OFF_1:
                return _model->get_style()->get_state_off_1_color();
            case STATES::ON_1:
                return _model->get_style()->get_state_on_1_color();
            case STATES::OFF_2:
                return _model->get_style()->get_state_off_2_color();
            case STATES::ON_2:
                return _model->get_style()->get_state_on_2_color();
            default:
                return 0x00000000;
            }
        }
        return 0x00000000;
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // RUBBER HANDLING
    virtual bool are_you_rubberable() override { return true; }

    virtual void rubber_droped() override
    {
        PodParameterBase *param = get_parameter();
        if (param)
            param->set_value(param->default_value());
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // UI FEEDBACK
    bool is_click_blocked() override
    {
        return _app_instance_store->midi_in_map.is_in_learning_mode() && is_learnable();
    }
    void handle_blocked_click() override { _app_instance_store->midi_in_map.set_learning(this); }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // MIDI FEEDBACK
    MIDI_HANDLE_TYPES get_midi_handling_type() const override
    {
        return MIDI_HANDLE_TYPES::BUTTON_TOGGLE;
    };

  protected:
    MONO_UIButtonController(); // -> delete

    MONO_UIButtonController(AppInstanceStore *const app_instance_store_)
        : MONO_Controller(app_instance_store_)
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MONO_UIButtonController)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class MONO_UISliderController : public MONO_Controller
{
    AppInstanceStore *const _app_instance_store;

    virtual const juce::String &get_controller_name() const override
    {
        PodParameterBase *const param = get_parameter();
        if (param)
            return param->name();

        return _no_conroller;
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // IDENTING
    virtual UI_VIEW_TYPES get_view_type() override { return UI_VIEW_TYPES::UI_SLIDER; }

    const char *get_controller_type_ident() const override
    {
        PodParameterBase *const param = get_parameter();
        if (param)
            return param->get_param_unique_ident();

        return nullptr;
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // VIEW EVENT HANDLING
    void on_mouse_down(const juce::MouseEvent &) override
    {
        if (_app_instance_store->midi_in_map.is_in_learning_mode() && is_learnable())
        {
            _app_instance_store->midi_in_map.set_learning(this);
        }
        else
        {
            _app_instance_store->editor_config.slider_controller_is_down = this;
            auto *param = get_parameter();
            if (param)
            {
                param->beginChangeGesture();
            }
        }
    }

    void on_mouse_up(const juce::MouseEvent &) override
    {
        if (_app_instance_store->editor_config.slider_controller_is_down == this)
        {
            _app_instance_store->editor_config.slider_controller_is_down = nullptr;
            auto *param = get_parameter();
            if (param)
            {
                param->endChangeGesture();
            }
        }
    }

    virtual void get_label_text_top(juce::String &string_) const override
    {
        string_ = juce::String(get_value());
    };

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // SET VALUE HANDLING
    virtual void on_value_changed(int v_) override
    {
        PodParameterBase *param = get_parameter();
        if (param)
        {
#ifndef IS_REMOTE_CONTROLLER
            param->set_value_notifying_host(v_);
#else
            param->set_remote_value(v_);
#endif
        }
    }

    virtual bool do_you_need_a_text_popup() override
    {
        MultidragSource *const multidrag_source =
            _app_instance_store->editor_config.multidrag_source;
        if (multidrag_source)
        {
            if (_app_instance_store->editor_config.multidrag_source->controller_type_ident ==
                get_controller_type_ident())
            {
                return true;
            }
        }

        if (_app_instance_store->editor_config.slider_controller_is_down == this)
        {
            return true;
        }

        return false;
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // GET VALUE HANDLING
    virtual int get_value() const override
    {
        PodParameterBase *param = get_parameter();
        if (param)
            return param->value();

        return 0;
    }

    virtual int get_range_max() override
    {
        PodParameterBase *param = get_parameter();
        if (param)
            return param->max_value();

        return 0;
    }
    virtual int get_range_min() override
    {
        PodParameterBase *param = get_parameter();
        if (param)
            return param->min_value();

        return 0;
    }

    virtual std::uint32_t get_current_color() const override
    {
        if (_model)
        {
            const AppStyle *const style = _model->get_style();
            if (style)
                return _model->get_style()->get_font_color();
        }

        return 0xffffffff;
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // RUBBER HANDLING
    virtual bool are_you_rubberable() override { return true; }

    virtual void rubber_droped() override
    {
        PodParameterBase *param = get_parameter();
        if (param)
            param->set_value(param->default_value());
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // VIEW SETUP
    void setup_view(void *const top_level_impl_) override
    {
        setup_slider(reinterpret_cast<UISlider *const>(top_level_impl_));
    }

    // DEFAULT SETUP FOR B_STEP
    /* virtual */ void setup_slider(UISlider *const slider_)
    {
        slider_->setRange(get_range_min(), get_range_max(), 1);
        slider_->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        slider_->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        if (get_range_max() > 350)
        {
            slider_->setDragSensitivity(1550);
        }
        else if (get_range_max() > 50)
        {
            slider_->setDragSensitivity(250);
        }
        else
            slider_->setDragSensitivity(200);
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // MIDI FEEDBACK
    MIDI_HANDLE_TYPES get_midi_handling_type() const override
    {
        return MIDI_HANDLE_TYPES::PERCENTAGE_VALUE;
    };

  protected:
    MONO_UISliderController(AppInstanceStore *const app_instance_store_)
        : MONO_Controller(app_instance_store_), _app_instance_store(app_instance_store_)
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MONO_UISliderController)
};

#endif
