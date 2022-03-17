/*
  ==============================================================================

    Created: late
    Author:  monotomy

  ==============================================================================
*/

#ifndef CORE_BAR_CONTROLLERS_INCLUDED
#define CORE_BAR_CONTROLLERS_INCLUDED

#include "CoreObservers.h"
#include "ControllerConfig.h"
#include "CoreCopy.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarstringOctave : public MONO_UISliderController
{
    SelectedBarstringObserver selected_barstring;

    PodParameterBase *get_parameter() const override
    {
        return &selected_barstring.get().octave_offset;
    }

  public:
    ControllerBarstringOctave(AppInstanceStore *const app_instance_store_, uint8 barstring_id_)
        : MONO_UISliderController(app_instance_store_),
          selected_barstring(app_instance_store_, barstring_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerStepLight : public MONO_UIButtonController
{
    SelectedBarstepObserver selected_barstep;
    AppInstanceStore *const _app_instance_store;
    bool is_multidrag_source;

    IS_NOT_MIDI_LEARNABLE

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // DEFAULT DRAG AND DROP!
    bool are_you_simple_dragable() override { return true; }

    String _dragNdrop_ident;
    String &get_dragNdrop_ident() override { return _dragNdrop_ident; }

    Component *get_dragNdrop_source() override
    {
        BarStepCopySourceData *source = new BarStepCopySourceData(
            &selected_barstep.get_selected_bar(), &selected_barstep.get(), is_multidrag_source);

        is_multidrag_source = false;
        return source;
    }

    bool is_interested_in_drag_source(
        const DragAndDropTarget::SourceDetails &dragSourceDetails_) override
    {
        if (dragSourceDetails_.sourceComponent.get()->getName().compare("TlR") == 0)
        {
            if (are_you_rubberable())
            {
                return true;
            }

            return false;
        }
        if (dragSourceDetails_.sourceComponent.get()->getName().compare("TlQ") == 0)
        {
            return true;
        }
        else if (dragSourceDetails_.description.toString().compare(get_dragNdrop_ident()) == 0)
        {
            Component *source_component = dragSourceDetails_.sourceComponent.get();
            if (source_component)
            {
                BarStepCopySourceData *step_copy_source =
                    dynamic_cast<BarStepCopySourceData *>(source_component);
                if (step_copy_source)
                {
                    // TODO the source will be never deleted, should be done on mouse up
                    if (step_copy_source->is_multi_drag)
                    {
                        // copy barstep
                        selected_barstep.get() = *step_copy_source->copy_source_barstep;

                        // copy steps
                        uint8 target_step_id = selected_barstep.get().id;
                        uint8 source_step_id = step_copy_source->copy_source_barstep->id;
                        for (int barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
                        {
                            selected_barstep.get_selected_bar()
                                .barstring(barstring_id)
                                .step(target_step_id) =
                                step_copy_source->copy_source_bar->barstring(barstring_id)
                                    .step(source_step_id);
                        }
                    }
                    return true;
                }
            }
        }
        return false;
    }

    void item_dropped_top(const DragAndDropTarget::SourceDetails &dragSourceDetails_) override
    {
        if (dragSourceDetails_.description.toString().compare(get_dragNdrop_ident()) == 0)
        {
            BarStepCopySourceData *const source = reinterpret_cast<BarStepCopySourceData *const>(
                dragSourceDetails_.sourceComponent.get());
            if (source)
                CoreCopy::barstep(*source->copy_source_barstep, selected_barstep.get(),
                                  *source->copy_source_bar, selected_barstep.get_selected_bar());
        }
    }

    void get_label_text_top(String &string_) const override
    {
        if (selected_barstep.get().skip)
        {
            string_ = String("S");
            return;
        }

        if (is_step_muted_on_any_way())
        {
            string_ = String("M");
            return;
        }

        int8 current_step_repeat = selected_barstep.get_running_repeat_as_count_down();
        if (current_step_repeat > 0)
        {
            string_ = String(current_step_repeat);
            return;
        }

        const Bar &running_bar = selected_barstep.get_running_bar();
        if (running_bar.barstep(selected_barstep.step_id).pos_entry_point)
        {
            string_ = String(">>");
            return;
        }
        else if (running_bar.barstep(selected_barstep.step_id).pos_reset_point)
            if (!selected_barstep.is_repeat_at_step_already_processed())
            {
                string_ = String("<<");
                return;
            }

        string_ = HAS_NO_TEXT_VALUE;
    }

    AppStyle *get_custom_label_style() const override
    {
        if (is_step_muted_on_any_way())
        {
            return _app_instance_store->style_step_area_skip;
        }

        const Bar &running_bar = selected_barstep.get_running_bar();
        const BarStep &running_barstep = running_bar.barstep(selected_barstep.step_id);
        {
            if (running_barstep.skip_repeat)
            {
                return _app_instance_store->style_step_area_skip;
            }
        }
        if (selected_barstep.get_running_repeat_as_count_down() > 0)
        {
            if (running_barstep.dont_roll_repeat)
                return _app_instance_store->style_step_area_duration;
            else
                return _app_instance_store->style_step_area_run;
        }

        return nullptr;
    }

    bool is_step_muted_on_any_way() const
    {
        if (selected_barstep.get().mute)
            return true;
        if (selected_barstep.get().skip)
            return true;
        if (selected_barstep.get().probability == 0)
            return true;

        return false;
    }

    unsigned int get_current_state() const override
    {
        if (selected_barstep.is_running_step_id())
            return STATES::ON_1;
        if (selected_barstep.get().skip)
            return STATES::OFF_2;
        if (is_step_muted_on_any_way())
            return STATES::OFF_2;

        return STATES::OFF_1;
    }

    uint32 get_current_color() const override
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
                return get_runing_color();
            case STATES::OFF_2:
                return _app_instance_store->color_theme->elem_color_4;
            case STATES::ON_2:
                return _model->get_style()->get_state_on_2_color();
            default:
                return 0x00000000;
            }
        }
        return 0x00000000;
    }

    uint32 get_runing_color() const
    {
        switch (selected_barstep.get_selected_bar().group)
        {
        case 0:
            return _app_instance_store->style_bar_area_run->get_state_on_1_color();
        case 1:
            return _app_instance_store->style_bar_area_chord->get_state_on_1_color();
        case 2:
            return _app_instance_store->style_bar_area_octave->get_state_on_1_color();
        case 3:
            return _app_instance_store->style_bar_area_time->get_state_on_1_color();
        default:
            return _app_instance_store->style_bar_area_run->get_state_on_1_color();
        }
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // MULTI DRAG N DROP
    USE_DEFAULT_MULTI_DRAG
    bool should_start_multi_drag() override
    {
        is_multidrag_source = true;
        return true;
    }

    String &get_multi_dragNdrop_ident() override { return get_dragNdrop_ident(); }

    // RUBBER
    bool are_you_rubberable() override { return true; }

    void rubber_droped() override
    {
        // TODO dont create a new one, hold one global for this case
        selected_barstep.get() = BarStep(124);

        // TODO dont create a new one, hold one global for this case
        Step step(5, 124);
        for (int barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
        {
            selected_barstep.get_selected_bar()
                .barstring(barstring_id)
                .step(selected_barstep.get().id) = step;
        }
    }

    const String get_help_url() override
    {
        return MANUAL_URL + "advanced-users/the-runlight-more-than-left-to-right";
    }

    void on_clicked_top() override { selected_barstep.get().mute.invert(); }

  public:
    ControllerStepLight(AppInstanceStore *const app_instance_store_, uint8 step_id_)
        : MONO_UIButtonController(app_instance_store_),
          selected_barstep(app_instance_store_, step_id_), _app_instance_store(app_instance_store_),
          is_multidrag_source(false), _dragNdrop_ident(BARSTEP_DRAG_N_DROP_IDENT)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
// TODO default controller handling
class ControllerBarSelect : public MONO_UIButtonController
{
    BarObserver bar;
    AppInstanceStore *const _app_instance_store;
    bool is_multidrag_source;

    PodParameterBase *get_parameter() const override
    {
        return &_app_instance_store->editor_config.selected_bar_id;
    }

    void on_clicked_top() override { bar.set_selected_bar(); }

    void on_param_via_changed() const override { bar.set_selected_bar(); }

    void get_label_text_top(String &string_) const override
    {
        if (bar.is_running_bar())
        {
            uint8 running_repeat = bar.get_running_bar_repeat();
            if (running_repeat > 1)
                string_ = String(running_repeat);
            else if (_app_instance_store->sequencer.is_unprocessed_bar_reset(bar.get()))
                string_ = String("<<");
            else
                /// TODO HAS NO TEXT VALUE IS THE STRING INIT FROM THE CALLER
                string_ = String(HAS_NO_TEXT_VALUE);
        }
        else if (_app_instance_store->sequencer.is_unprocessed_bar_reset(bar.get()))
            string_ = String("<<");
        else if (bar.is_probabliy_next_bar())
            string_ = String("N");
        else if (bar.get().skip)
            string_ = String("S");
        else if (bar.get().mute)
            string_ = String("M");
        else if (bar.get().solo || Sequencer::is_valid_for_auto_chain(bar.get()))
            string_ = String("-");
        else
            string_ = String(HAS_NO_TEXT_VALUE);
    }

    bool is_bar_muted_on_any_way() const
    {
        if (bar.get().mute)
            return true;
        if (bar.get().skip)
            return true;

        return false;
    }

    unsigned int get_current_state() const override
    {
        if (bar.is_running_bar())
            return STATES::ON_1;
        if (bar.get().mute)
            return STATES::OFF_2;
        if (bar.get().solo)
            return STATES::OFF_1;
        if (bar.get().skip)
            return STATES::OFF_2;
        if (!Sequencer::is_valid_for_auto_chain(bar.get()))
            return STATES::OFF_2;

        return STATES::OFF_1;
    }

    uint32 get_current_color() const override
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
                return get_runing_color();
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

    uint32 get_runing_color() const
    {
        switch (bar.get().group)
        {
        case 0:
            return _app_instance_store->style_bar_area_run->get_state_on_1_color();
        case 1:
            return _app_instance_store->style_bar_area_chord->get_state_on_1_color();
        case 2:
            return _app_instance_store->style_bar_area_octave->get_state_on_1_color();
        case 3:
            return _app_instance_store->style_bar_area_time->get_state_on_1_color();
        default:
            return _app_instance_store->style_bar_area_run->get_state_on_1_color();
        }
    }

    AppStyle *get_custom_label_style() const override
    {
        if (is_bar_muted_on_any_way())
        {
            return _app_instance_store->style_bar_area_skip;
        }

        if (bar.is_running_bar())
        {
            if (bar.get_running_bar_repeat() > 1)
                return _app_instance_store->style_bar_area_time;
        }

        if (bar.is_probabliy_next_bar())
            return _app_instance_store->style_bar_area_time;

        if (_app_instance_store->sequencer.is_unprocessed_bar_reset(bar.get()))
        {
            if (bar.is_running_bar())
                return _app_instance_store->style_bar_area_time;
            else
                return _app_instance_store->style_bar_area_run;
        }

        if (Sequencer::is_valid_for_auto_chain(bar.get()))
            return _app_instance_store->style_bar_area_mute;

        return nullptr;
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // DEFAULT DRAG AND DROP!
    bool are_you_simple_dragable() override { return true; }

    String _dragNdrop_ident;
    String &get_dragNdrop_ident() override { return _dragNdrop_ident; }

    Component *get_dragNdrop_source() override
    {
        BarCopySourceData *source = new BarCopySourceData(&bar.get(), is_multidrag_source);
        is_multidrag_source = false;
        return source;
    }

    bool is_interested_in_drag_source(
        const DragAndDropTarget::SourceDetails &dragSourceDetails_) override
    {
        if (dragSourceDetails_.sourceComponent.get()->getName().compare("TlR") == 0)
        {
            if (are_you_rubberable())
            {
                return true;
            }

            return false;
        }
        if (dragSourceDetails_.sourceComponent.get()->getName().compare("TlQ") == 0)
        {
            return true;
        }
        else if (dragSourceDetails_.description.toString().compare(get_dragNdrop_ident()) == 0)
        {
            Component *source = dragSourceDetails_.sourceComponent.get();
            if (source)
            {
                BarCopySourceData *bar_copy_source = dynamic_cast<BarCopySourceData *>(source);
                if (bar_copy_source)
                {
                    if (bar_copy_source->is_multi_drag)
                    {
                        bar.get() = *bar_copy_source->copy_source_bar;
                        bar.set_selected_bar();
                    }
                }
                return true;
            }
        }
        else if (dragSourceDetails_.description.toString().compare(
                     BAR_CLIPBOARD_DRAG_N_DROP_IDENT) == 0)
        {
            Component *source = dragSourceDetails_.sourceComponent.get();
            if (source)
            {
                return true;
            }
        }

        return false;
    }
    void item_dropped_top(const DragAndDropTarget::SourceDetails &dragSourceDetails_) override
    {
        if (dragSourceDetails_.description.toString().compare(get_dragNdrop_ident()) == 0)
        {
            BarCopySourceData *source =
                reinterpret_cast<BarCopySourceData *>(dragSourceDetails_.sourceComponent.get());
            bar.get() = *source->copy_source_bar;
        }
        else if (dragSourceDetails_.description.toString().compare(
                     BAR_CLIPBOARD_DRAG_N_DROP_IDENT) == 0)
        {
            BarCopySourceData *source =
                reinterpret_cast<BarCopySourceData *>(dragSourceDetails_.sourceComponent.get());
            if (source)
                CoreCopy::bar_from_clipboard(bar.get(), source);
        }

        bar.set_selected_bar();
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // MULTI DRAG N DROP
    USE_DEFAULT_MULTI_DRAG
    bool should_start_multi_drag() override
    {
        is_multidrag_source = true;
        return true;
    }

    String &get_multi_dragNdrop_ident() override { return get_dragNdrop_ident(); }

    // RUBBER
    bool are_you_rubberable() override { return true; }

    const String get_help_url() override
    {
        return MANUAL_URL + "beginner/basic-functions/bar-selection-and-bar-copy";
    }

    void rubber_droped() override
    {
        // TODO
        Bar empty_bar(0);
        bar.get() = empty_bar;
    }

  public:
    ControllerBarSelect(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UIButtonController(app_instance_store_), bar(app_instance_store_, bar_id_),
          _app_instance_store(app_instance_store_), is_multidrag_source(false),
          _dragNdrop_ident(BAR_DRAG_N_DROP_IDENT)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarChainmute : public MONO_UIButtonController
{
    BarObserver bar;
    AppInstanceStore *const _app_instance_store;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase *get_parameter() const override { return &bar.get().force_chain; }

  public:
    ControllerBarChainmute(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UIButtonController(app_instance_store_), bar(app_instance_store_, bar_id_),
          _app_instance_store(app_instance_store_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarOctave : public MONO_UISliderController
{
    BarObserver bar;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase *get_parameter() const override { return &bar.get().octave_offset; }

  public:
    ControllerBarOctave(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UISliderController(app_instance_store_), bar(app_instance_store_, bar_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarChord : public MONO_UISliderController
{
    BarObserver bar;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase *get_parameter() const override { return &bar.get().chord_id; }

    void get_label_text_top(String &string_) const override
    {
        string_ = String(bar.get().chord_id + 1);
    }

  public:
    ControllerBarChord(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UISliderController(app_instance_store_), bar(app_instance_store_, bar_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarRepeat : public MONO_UISliderController
{
    BarObserver bar;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase *get_parameter() const override { return &bar.get().repeats; }

    void get_label_text_top(String &string_) const override { string_ = String(bar.get().repeats); }

  public:
    ControllerBarRepeat(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UISliderController(app_instance_store_), bar(app_instance_store_, bar_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarCCType : public MONO_UISliderController
{
    SelectedBarObserver selected_bar;
    const unsigned int _cc_set_id;

    PodParameterBase *get_parameter() const override
    {
        return &selected_bar.get().cc_set(_cc_set_id).cc_type;
    }

    void get_label_text_top(String &string_) const override
    {
        string_ = String(selected_bar.get().cc_set(_cc_set_id).cc_type);
    }

  public:
    ControllerBarCCType(AppInstanceStore *const app_instance_store_, uint8 cc_set_id_)
        : MONO_UISliderController(app_instance_store_), selected_bar(app_instance_store_),
          _cc_set_id(cc_set_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarSongReset : public MONO_UIButtonController
{
    BarObserver bar;

    USE_DEFAULT_MULTI_DRAG

    virtual PodParameterBase *get_parameter() const override { return &bar.get().pos_reset; }

  public:
    ControllerBarSongReset(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UIButtonController(app_instance_store_), bar(app_instance_store_, bar_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarSongEntry : public MONO_UIButtonController
{
    BarObserver bar;

    virtual PodParameterBase *get_parameter() const override { return &bar.get().pos_reset; }

  public:
    ControllerBarSongEntry(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UIButtonController(app_instance_store_), bar(app_instance_store_, bar_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarSkip : public MONO_UIButtonController
{
    BarObserver bar;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase *get_parameter() const override { return &bar.get().skip; }

  public:
    ControllerBarSkip(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UIButtonController(app_instance_store_), bar(app_instance_store_, bar_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarMute : public MONO_UIButtonController
{
    BarObserver bar;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase *get_parameter() const override { return &bar.get().mute; }

  public:
    ControllerBarMute(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UIButtonController(app_instance_store_), bar(app_instance_store_, bar_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarSolo : public MONO_UIButtonController
{
    BarObserver bar;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase *get_parameter() const override { return &bar.get().solo; }

    void on_clicked_top() override { bar.get().solo.invert(); }

    void get_label_text_top(String &string_) const override
    {
        if (bar.get().group > 0)
            string_ = String("|") + String(bar.get().group + 1) + String("|");
        else
            string_ = String(HAS_NO_TEXT_VALUE);
    }

    AppStyle *get_custom_label_style() const override
    {
        switch (bar.get().group)
        {
        case 0:
            return _app_instance_store->style_bar_area_run;
        case 1:
            return _app_instance_store->style_bar_area_chord;
        case 2:
            return _app_instance_store->style_bar_area_octave;
        case 3:
            return _app_instance_store->style_bar_area_time;
        default:
            return _app_instance_store->style_bar_area_run;
        }
    }

  public:
    ControllerBarSolo(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UIButtonController(app_instance_store_), bar(app_instance_store_, bar_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarPlayReverse : public MONO_UIButtonController
{
    BarObserver bar;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase *get_parameter() const override { return &bar.get().play_reverse; }

  public:
    ControllerBarPlayReverse(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UIButtonController(app_instance_store_), bar(app_instance_store_, bar_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarPlayRandom : public MONO_UIButtonController
{
    BarObserver bar;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase *get_parameter() const override { return &bar.get().random_playback; }

  public:
    ControllerBarPlayRandom(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UIButtonController(app_instance_store_), bar(app_instance_store_, bar_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
// TODO is no more needed, but function will be used by the rubber tool
class ControllerBarReset2Default : public MONO_UIButtonController, public Timer
{
    BarObserver bar;
    AppInstanceStore *const _app_instance_store;

    void on_clicked_top() override
    {
        startTimer(750);
        // TODO
        bar.get() = Bar(0);
    }

    USE_DEFAULT_MULTI_DRAG
    void on_value_changed(int) override { on_clicked_top(); }

    unsigned int get_current_state() const override { return Timer::isTimerRunning(); }

    void timerCallback() override { stopTimer(); }

  public:
    ControllerBarReset2Default(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UIButtonController(app_instance_store_), bar(app_instance_store_, bar_id_),
          _app_instance_store(app_instance_store_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarTriggerPoint : public MONO_UISliderController
{
    AppInstanceStore *const _app_instance_store;
    BarObserver bar;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase *get_parameter() const override { return &bar.get().group; }

    void get_label_text_top(String &string_) const override
    {
        if (bar.get().group == -1)
            string_ = String("off");
        else
            string_ = String("|") + String(bar.get().group + 1) + String("|");
    }

    uint32 get_current_color() const override
    {
        switch (bar.get().group)
        {
        case 0:
            return _app_instance_store->style_bar_area_run->get_state_on_1_color();
        case 1:
            return _app_instance_store->style_bar_area_chord->get_state_on_1_color();
        case 2:
            return _app_instance_store->style_bar_area_octave->get_state_on_1_color();
        case 3:
            return _app_instance_store->style_bar_area_time->get_state_on_1_color();
        default:
            return _app_instance_store->style_bar_area_run->get_state_on_1_color();
        }
    }

  public:
    ControllerBarTriggerPoint(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UISliderController(app_instance_store_), _app_instance_store(app_instance_store_),
          bar(app_instance_store_, bar_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBarStepShift : public MONO_UISliderController
{
    BarObserver bar;
    AppInstanceStore *const _app_instance_store;
    int8 tmp_last_copy_offset;
    CriticalSection lock;

    bool is_still_in_progress;

    void on_value_changed(int v_) override
    {
        bar.set_selected_bar();

        const ScopedLock myScopedLock(lock);

        int8 offset = 0;
        if (v_ > tmp_last_copy_offset && v_ <= 15)
            offset = 1;
        else if (v_ < tmp_last_copy_offset && v_ >= -15)
            offset = -1;
        else
            return;

        tmp_last_copy_offset += offset;

        Array<bool> tmp_source_mutes;

        // copy alg
        int count_from = 0;
        if (offset < 0)
            count_from = SUM_STEPS - 1;
        int count_to = SUM_STEPS;
        if (offset < 0)
            count_to = -1;
        int count_up_or_down = 1;
        if (offset < 0)
            count_up_or_down = -1;

        // get the first source
        for (uint8 barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
        {
            tmp_source_mutes.add(bar.get().barstring(barstring_id).step(count_from).is_mute);
        }

        // copy all
        for (int8 source_step_id = count_from; source_step_id != count_to;
             source_step_id += count_up_or_down)
        {
            Array<bool> tmp_target_mutes;
            int8 target_step_id = source_step_id + offset;
            if (target_step_id >= SUM_STEPS) // close loop up direction
                target_step_id = target_step_id - SUM_STEPS;
            else if (target_step_id < 0) // close loop down direction
                target_step_id = SUM_STEPS + target_step_id;

            for (int barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
            {
                Step &target_step = bar.get().barstring(barstring_id).step(target_step_id);
                tmp_target_mutes.add(target_step.is_mute);
                target_step.is_mute = tmp_source_mutes.getUnchecked(barstring_id);
            }

            tmp_source_mutes.clearQuick();
            tmp_source_mutes = tmp_target_mutes;
        }
    }

    int get_value() const override { return tmp_last_copy_offset; }

    int get_range_max() override { return 15; }

    int get_range_min() override { return -15; }

  public:
    ControllerBarStepShift(AppInstanceStore *const app_instance_store_, uint8 bar_id_)
        : MONO_UISliderController(app_instance_store_), bar(app_instance_store_, bar_id_),
          _app_instance_store(app_instance_store_), tmp_last_copy_offset(0)
    {
    }
};

#endif
