/*
  ==============================================================================

    Created: late
    Author:  monotomy

  ==============================================================================
*/

#ifndef CORE_BARSTEP_CONTROLLERS_INCLUDED
#define CORE_BARSTEP_CONTROLLERS_INCLUDED

#include "CoreObservers.h"
#include "ControllerConfig.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerStepDuration : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().duration;
    }

    void get_label_text_top( String& popup_text_ ) const override {
        APPDEF_BarStep::duration2string( selected_barstep.get().duration, popup_text_ );
    };

public:
    ControllerStepDuration ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerStepVelocity : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().velocity;
    }

public:
    ControllerStepVelocity ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepRepeats : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().repeats;
    }

public:
    ControllerBarstepRepeats ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepRepeatsDistance : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().repeat_distance;
    }

    void get_label_text_top( String& popup_text_ ) const override {
        APPDEF_BarStep::duration2string( selected_barstep.get().repeat_distance, popup_text_ );
    };

public:
    ControllerBarstepRepeatsDistance ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepRepeatsDistanceOffset : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().repeat_distance_offset;
    }

    void get_label_text_top( String& popup_text_ ) const override {
        APPDEF_BarStep::duration2string ( selected_barstep.get().repeat_distance_offset, popup_text_ );
    };

public:
    ControllerBarstepRepeatsDistanceOffset ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepRepeatsVelocityOffset : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().repeat_velocity_offset;
    }

public:
    ControllerBarstepRepeatsVelocityOffset ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepRepeatsDurationOffset : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().repeat_duration_offset;
    }

    void get_label_text_top( String& popup_text_ ) const override {
        APPDEF_BarStep::duration2string( selected_barstep.get().repeat_duration_offset, popup_text_ );
    };

public:
    ControllerBarstepRepeatsDurationOffset ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepRepeatsNoteOffset : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().repeat_note_offset;
    }

    void get_label_text_top( String& popup_text_ ) const override {
        popup_text_ = String( selected_barstep.get().repeat_note_offset );
    };

public:
    ControllerBarstepRepeatsNoteOffset ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepRepeatsProbability : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().repeat_probability;
    }

    void get_label_text_top( String& popup_text_ ) const override {
        popup_text_ = String( selected_barstep.get().repeat_probability ) + "%";
    };

public:
    ControllerBarstepRepeatsProbability ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepRepeatsForce2ChordNotes : public MONO_UIButtonController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().repeat_force_chord_notes;
    }

public:
    ControllerBarstepRepeatsForce2ChordNotes  ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};


// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepOctaveOffset : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().octave_offset;
    }

public:
    ControllerBarstepOctaveOffset ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepChord : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().chord_id;
    }

    void get_label_text_top( String& popup_text_ ) const override {
        popup_text_ = String(selected_barstep.get().chord_id+1);
    };

public:
    ControllerBarstepChord ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepSkip : public MONO_UIButtonController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().skip;
    }

public:
    ControllerBarstepSkip  ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepMute : public MONO_UIButtonController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().mute;
    }

    virtual void on_value_changed( int v_ ) override {
        if( v_ == STATES::ON_2 )
            selected_barstep.get().mute = true;
        else
            selected_barstep.get().mute = false;
    }

    unsigned int get_current_state() const override
    {
        if( selected_barstep.get().mute )
            return STATES::ON_2;

        return STATES::OFF_1;
    }

public:
    ControllerBarstepMute  ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepDelay : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().delay;
    }

    void get_label_text_top( String& popup_text_ ) const override {
        APPDEF_BarStep::duration2string( selected_barstep.get().delay, popup_text_ );
    };

public:
    ControllerBarstepDelay ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepProbability : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().probability;
    }

    void get_label_text_top( String& popup_text_ ) const override {
        popup_text_ = String(selected_barstep.get().probability)+String("%");
    };

public:
    ControllerBarstepProbability ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepReset2Default : public MONO_UIButtonController, public Timer
{
    SelectedBarstepObserver selected_barstep;
    AppInstanceStore*const _app_instance_store;

    IS_NOT_MIDI_LEARNABLE

    void on_clicked_top() override
    {
        startTimer(750);
        selected_barstep.get() = BarStep( SUM_STEPS+99 );

        Step step( SUM_STRINGS+1, SUM_STEPS+99 );
        for( int barstring_id = 0 ; barstring_id != SUM_STRINGS ; ++barstring_id )
        {
            selected_barstep.get_selected_bar().barstring(barstring_id).step(selected_barstep.get().id) = step;
        }
    }

    USE_DEFAULT_MULTI_DRAG
    void on_value_changed( int ) override
    {
        on_clicked_top();
    }

    unsigned int get_current_state() const override {
        return Timer::isTimerRunning();
    }

    void timerCallback()
    {
        stopTimer();
    }

public:
    ControllerBarstepReset2Default  ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ ),
          _app_instance_store( app_instance_store_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
// TODO delete
class ControllerBarstepCopy : public MONO_UIButtonController
{
    IS_NOT_MIDI_LEARNABLE

    SelectedBarstepObserver selected_barstep;

public:
    ControllerBarstepCopy  ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepRepeatsIsUsed : public MONO_UIButtonController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().skip_repeat;
    }

public:
    ControllerBarstepRepeatsIsUsed  ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepRepeatsNoteUpNDown : public MONO_UIButtonController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().repeat_note_upNdown;
    }

public:
    ControllerBarstepRepeatsNoteUpNDown  ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepRepeatsRoll : public MONO_UIButtonController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().dont_roll_repeat;
    }

public:
    ControllerBarstepRepeatsRoll  ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepPosEntryPoint : public MONO_UIButtonController
{
    SelectedBarstepObserver selected_barstep;

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().pos_entry_point;
    }

    void on_clicked_top() override
    {
        if( ! selected_barstep.get().pos_entry_point )
        {
            for( int step_id = 0 ; step_id != SUM_BARS ; ++step_id )
            {
                if( selected_barstep.step_id == step_id )
                    selected_barstep.get().pos_entry_point = true;
                else
                    selected_barstep.get_selected_bar().barstep( step_id ).pos_entry_point = false;
            }
        }
        else
        {
            selected_barstep.get().pos_entry_point = false;
        }
    }

public:
    ControllerBarstepPosEntryPoint  ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepPosResetPoint : public MONO_UIButtonController
{
    SelectedBarstepObserver selected_barstep;
    const AppInstanceStore*const _app_instance_store;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().pos_reset_point;
    }

public:
    ControllerBarstepPosResetPoint  ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ ),
          _app_instance_store( app_instance_store_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepPosForceToAbsolute : public MONO_UIButtonController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().pos_force_to_absolute_step;
    }

public:
    ControllerBarstepPosForceToAbsolute  ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepUseChord : public MONO_UIButtonController
{
    SelectedBarstepObserver selected_barstep;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().use_step_chord;
    }

    void get_label_text_top( String& string_ ) const override
    {
        string_ = String(selected_barstep.get().chord_id+1);
    }

public:
    ControllerBarstepUseChord  ( AppInstanceStore*const app_instance_store_, uint8 step_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepCCValue : public MONO_UISliderController
{
    SelectedBarstepObserver selected_barstep;
    const AppInstanceStore*const _app_instance_store;
    const unsigned int _cc_val_id;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().cc_val(_cc_val_id).value;
    }

    /* USE FOR LABEL ON THE LEFT SIDER TODO???
    void get_label_text_top( String& popup_text_ ) const override {
        popup_text_ = _app_instance_store->midi_cc.names.getUnchecked(selected_barstep.get().cc_val(_cc_val_id).value);
    };
    */
public:
    ControllerBarstepCCValue ( AppInstanceStore*const app_instance_store_, uint8 step_id_, uint8 cc_val_id_ )
        : MONO_UISliderController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ ),
          _app_instance_store( app_instance_store_ ),
          _cc_val_id( cc_val_id_ )
    {}
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstepCCEnable : public MONO_UIButtonController
{
    SelectedBarstepObserver selected_barstep;
    const unsigned int _cc_id;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase* get_parameter() const override {
        return &selected_barstep.get().cc_val(_cc_id).enable;
    }

    void get_label_text_top( String& string_ ) const override
    {
        string_ = String(selected_barstep.get().cc_val(_cc_id).value);
    }

public:
    ControllerBarstepCCEnable ( AppInstanceStore*const app_instance_store_, uint8 step_id_, uint8 cc_id_ )
        : MONO_UIButtonController ( app_instance_store_ ),
          selected_barstep( app_instance_store_, step_id_ ),
          _cc_id( cc_id_ )
    {}
};

#endif
