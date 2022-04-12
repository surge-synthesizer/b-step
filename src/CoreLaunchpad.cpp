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

#include "CoreLaunchpad.h"

#include "CoreDatastructure.h"
#include "CoreSequencer.h"

#include "PluginProcessor.h" // TODO can be done by structure only
#include "UiSettings.h"      // TODO can be done by structure only

//// COLORS

enum LAUNCHPAD
{
    LAUNCHPAD_OFF = 0,

    LAUNCHPAD_RED_LOW = 13,
    LAUNCHPAD_RED_MID = 14,
    LAUNCHPAD_RED_FULL = 15,

    LAUNCHPAD_AMBER_LOW = 17,
    LAUNCHPAD_AMBER_MID = 18, // ??
    LAUNCHPAD_AMBER_FULL = 19,

    LAUNCHPAD_YELLO_FULL = 35, // ?? manual find

    LAUNCHPAD_GREEN_LOW = 28,
    LAUNCHPAD_GREEN_MID = 33, // ??
    LAUNCHPAD_GREEN_FULL = 60,

    LAUNCHPAD_RED_FLASH_FULL = 11,
    LAUNCHPAD_AMBER_FLASH_FULL = 59,
    LAUNCHPAD_YELLOW_FLASH_FULL = 58,
    LAUNCHPAD_GREN_FLASH_FULL = 56
};

enum LAUNCHPAD_ROWS
{
    FIXED_LAUNCHPAD_ROW_STEP_RUNLIGHT = 0,
    // first page
    RELEATIVE_LAUNCHPAD_END_ROW_STEPS = 4,
    RELEATIVE_LAUNCHPAD_ROW_BAR_CHORD_UP = 5,
    RELEATIVE_LAUNCHPAD_ROW_BAR_CHORD_DOWN = 6,
    FIXED_LAUNCHPAD_ROW_STEP_BAR_SELECT = 7,

    // second page
    RELEATIVE_LAUNCHPAD_ROW_BAR_OCTAVE_UP = 8, // Page 2
    RELEATIVE_LAUNCHPAD_ROW_BAR_OCTAVE_DOWN = 9,
    RELEATIVE_LAUNCHPAD_ROW_SPACER_OCTAVE = 10,
    RELEATIVE_LAUNCHPAD_ROW_DURATION = 11,
    RELEATIVE_LAUNCHPAD_ROW_VECLOCITY = 12,
    RELEATIVE_LAUNCHPAD_ROW_REPATS = 13,

    // RIGHT BUTTONS
    FIXED_LAUNCHPAD_PAGE_1_SHIFT_CARLA_CC_FIX = 0,
    FIXED_LAUNCHPAD_PAGE_1_GLOBAL_OCTAVE_UP = 1,
    FIXED_LAUNCHPAD_PAGE_1_GLOBAL_OCTAVE_DOWN = 2,
    FIXED_LAUNCHPAD_PAGE_1_GLOBAL_NOTE_UP = 3,
    FIXED_LAUNCHPAD_PAGE_1_GLOBAL_NOTE_DOWN = 4,
    FIXED_LAUNCHPAD_PAGE_1_GLOBAL_CHORD_UP = 5,
    FIXED_LAUNCHPAD_PAGE_1_GLOBAL_CHORD_DOWN = 6,
    FIXED_LAUNCHPAD_PAGE_1_SET_SOLO_BAR = 7,

    // TOP BUTTONS ( CC )
    // TODO REMOVE CARLA OFFSETS!
    FIXED_LAUNCHPAD_TOP_UP = 105,
    FIXED_LAUNCHPAD_TOP_DOWN = 104,
    FIXED_LAUNCHPAD_TOP_LEFT = 106,
    FIXED_LAUNCHPAD_TOP_RIGHT = 107,
    FIXED_LAUNCHPAD_TOP_SESSION = 108,
    FIXED_LAUNCHPAD_TOP_USER_1 = 109,
    FIXED_LAUNCHPAD_TOP_USER_2 = 110,
    FIXED_LAUNCHPAD_TOP_MIXER = 111,
    FIXED_LAUNCHPAD_TOP_UP_CARLA_FIX = 5,
    FIXED_LAUNCHPAD_TOP_DOWN_CARLA_FIX = 4,
    FIXED_LAUNCHPAD_TOP_LEFT_CARLA_FIX = 6,
    FIXED_LAUNCHPAD_TOP_RIGHT_CARLA_FIX = 7,
    FIXED_LAUNCHPAD_TOP_SESSION_CARLA_FIX = 8,
    FIXED_LAUNCHPAD_TOP_USER_1_CARLA_FIX = 9,
    FIXED_LAUNCHPAD_TOP_USER_2_CARLA_FIX = 10,
    FIXED_LAUNCHPAD_TOP_MIXER_CARLA_FIX = 11,

    SCROLL_OFFSET_PAGE_1 = 0,
    SCROLL_OFFSET_PAGE_2 = 7
};

static inline std::uint8_t get_launchpad_row_0_color(bool is_running_step_)
{
    if (is_running_step_)
        return LAUNCHPAD_RED_FULL;

    return LAUNCHPAD_OFF;
}

static inline std::uint8_t get_launchpad_steps_color(bool is_mute_)
{
    if (is_mute_)
        return LAUNCHPAD_OFF;

    return LAUNCHPAD_YELLO_FULL;
}

static inline std::uint8_t get_launchpad_running_step_color(bool is_running_)
{
    if (is_running_)
        return LAUNCHPAD_RED_FULL;

    return LAUNCHPAD_OFF;
}

static inline std::uint8_t get_launchpad_running_bar_color(bool is_running_)
{
    if (is_running_)
        return LAUNCHPAD_RED_FULL;

    return LAUNCHPAD_OFF;
}

static inline std::uint8_t get_launchpad_solo_bar_color(bool is_running_)
{
    if (is_running_)
        return LAUNCHPAD_YELLO_FULL;

    return LAUNCHPAD_OFF;
}

static inline std::uint8_t get_launchpad_selected_bar_color(bool is_selected_)
{
    if (is_selected_)
        return LAUNCHPAD_AMBER_FULL;

    return LAUNCHPAD_OFF;
}

static inline std::uint8_t get_launchpad_bar_chord_color_up(const Bar &bar_)
{
    enum
    {
        RANGE_0 = 0,
        RANGE_1 = 1,
        RANGE_2 = 2,
        RANGE_3 = 3,
        RANGE_4 = 4,
        RANGE_5 = 5
    };
    // assert( bar_.chord_id <= RANGE_5 or bar_.chord_id <= RANGE_0 );

    switch (bar_.chord_id)
    {
    case RANGE_0:
        return LAUNCHPAD_AMBER_MID;
    case RANGE_1:
        return LAUNCHPAD_AMBER_LOW;
    case RANGE_2:
        return LAUNCHPAD_AMBER_LOW;
    case RANGE_3:
        return LAUNCHPAD_RED_LOW;
    case RANGE_4:
        return LAUNCHPAD_RED_MID;
    case RANGE_5:
        return LAUNCHPAD_RED_FULL;
    default:
        return LAUNCHPAD_OFF;
    }
}

static inline std::uint8_t get_launchpad_bar_chord_color_down(const Bar &bar_)
{
    enum
    {
        RANGE_0 = 0,
        RANGE_1 = 1,
        RANGE_2 = 2,
        RANGE_3 = 3,
        RANGE_4 = 4,
        RANGE_5 = 5
    };
    // assert( bar_.chord_id <= RANGE_5 or bar_.chord_id <= RANGE_0 );

    switch (bar_.chord_id)
    {
    case RANGE_0:
        return LAUNCHPAD_AMBER_FULL;
    case RANGE_1:
        return LAUNCHPAD_AMBER_MID;
    case RANGE_2:
        return LAUNCHPAD_AMBER_LOW;
    case RANGE_3:
        return LAUNCHPAD_AMBER_LOW;
    case RANGE_4:
        return LAUNCHPAD_RED_LOW;
    case RANGE_5:
        return LAUNCHPAD_RED_MID;
    default:
        return LAUNCHPAD_OFF;
    }
}

static inline std::uint8_t get_launchpad_bar_octave_color_up(const Bar &bar_)
{
    enum
    {
        RANGE_0 = -2,
        RANGE_1 = -1,
        RANGE_2 = 0,
        RANGE_3 = 1,
        RANGE_4 = 2
    };
    // assert( bar_.octave_offset <= RANGE_4 or bar_.octave_offset <= RANGE_0 );

    switch (bar_.octave_offset)
    {
    case RANGE_0:
        return LAUNCHPAD_AMBER_MID;
    case RANGE_1:
        return LAUNCHPAD_AMBER_LOW;
    case RANGE_2:
        return LAUNCHPAD_AMBER_LOW;
    case RANGE_3:
        return LAUNCHPAD_RED_LOW;
    case RANGE_4:
        return LAUNCHPAD_RED_MID;
    default:
        return LAUNCHPAD_OFF;
    }
}

static inline std::uint8_t get_launchpad_bar_octave_color_down(const Bar &bar_)
{
    enum
    {
        RANGE_0 = -2,
        RANGE_1 = -1,
        RANGE_2 = 0,
        RANGE_3 = 1,
        RANGE_4 = 2
    };
    // assert( bar_.octave_offset <= RANGE_4 or bar_.octave_offset <= RANGE_0 );

    switch (bar_.octave_offset)
    {
    case RANGE_0:
        return LAUNCHPAD_AMBER_FULL;
    case RANGE_1:
        return LAUNCHPAD_AMBER_MID;
    case RANGE_2:
        return LAUNCHPAD_AMBER_LOW;
    case RANGE_3:
        return LAUNCHPAD_AMBER_LOW;
    case RANGE_4:
        return LAUNCHPAD_RED_LOW;
    default:
        return LAUNCHPAD_OFF;
    }
}

static inline std::uint8_t get_launchpad_duration_color(std::uint8_t duration_)
{
    if (duration_ <= 4)
        return LAUNCHPAD_RED_LOW;

    if (duration_ <= 8)
        return LAUNCHPAD_RED_MID;

    return LAUNCHPAD_RED_FULL;
}

static inline std::uint8_t get_launchpad_velocity_color(std::uint8_t velocity_)
{
    if (velocity_ <= 50)
        return LAUNCHPAD_AMBER_LOW;

    if (velocity_ < 100)
        return LAUNCHPAD_AMBER_MID;

    return LAUNCHPAD_AMBER_FULL;
}

static inline std::uint8_t get_launchpad_bar_repeat_color(const Bar &bar_)
{
    switch (bar_.repeats)
    {
    case 1:
        return LAUNCHPAD_GREEN_LOW;
    case 2:
        return LAUNCHPAD_GREEN_LOW;
    case 3:
        return LAUNCHPAD_GREEN_MID;
    case 4:
        return LAUNCHPAD_GREEN_MID;
    case 5:
        return LAUNCHPAD_GREEN_FULL;
    case 6:
        return LAUNCHPAD_GREEN_FULL;
    case 7:
        return LAUNCHPAD_YELLO_FULL;
    case 8:
        return LAUNCHPAD_YELLO_FULL;
    default:
        return LAUNCHPAD_OFF;
    }
}

static inline std::uint8_t get_mode_color() { return LAUNCHPAD_AMBER_FULL; }

static inline std::uint8_t get_pressed_option_color() { return LAUNCHPAD_AMBER_FULL; }

static inline std::uint8_t get_mode_arrow_color() { return LAUNCHPAD_AMBER_LOW; }

static inline std::uint8_t get_global_octave_up_color(const Pattern &)
{
    return LAUNCHPAD_AMBER_MID;
}
static inline std::uint8_t get_global_octave_down_color(const Pattern &)
{
    return LAUNCHPAD_AMBER_LOW;
}

static inline std::uint8_t get_global_note_up_color(const Pattern &) { return LAUNCHPAD_RED_MID; }
static inline std::uint8_t get_global_note_down_color(const Pattern &) { return LAUNCHPAD_RED_LOW; }
static inline std::uint8_t get_global_chord_type_up_color(const Pattern &)
{
    return LAUNCHPAD_GREEN_MID;
}
static inline std::uint8_t get_global_chord_type_down_color(const Pattern &)
{
    return LAUNCHPAD_GREEN_LOW;
}

static inline std::uint8_t get_speed_up_color(const ProcessorUserData &processor_data_)
{
    if (GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_HALF == processor_data_.speed)
        return LAUNCHPAD_RED_LOW;
    if (GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_NORMAL == processor_data_.speed)
        return LAUNCHPAD_RED_LOW;
    // DOUBLE
    return LAUNCHPAD_RED_FULL;
}
static inline std::uint8_t get_speed_down_color(const ProcessorUserData &processor_data_)
{
    if (GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_HALF == processor_data_.speed)
        return LAUNCHPAD_RED_FULL;
    if (GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_NORMAL == processor_data_.speed)
        return LAUNCHPAD_RED_LOW;
    // DOUBLE
    return LAUNCHPAD_RED_LOW;
}

static inline std::uint8_t get_scroll_color(std::uint8_t scoll_offset_)
{
    if (scoll_offset_ > SCROLL_OFFSET_PAGE_1)
        return LAUNCHPAD_GREEN_FULL;

    return LAUNCHPAD_GREEN_LOW;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

//// LAUNCHPAD

//// CTORS

Launchpad::Launchpad(AppInstanceStore *const app_instance_store_, std::uint8_t launchpad_id_)
    : _app_instance_store(app_instance_store_),

      id(launchpad_id_),

      _current_scroll_offset(0),

      channel_in(id), channel_out(id), mode(id)
{
    BOOT(Launchpad)

    // MATRIX BUTTONS
    for (std::uint8_t row_id = 0; row_id != SUM_HARD_BUTTON_ROWS; ++row_id)
    {
        juce::Array<Button> row;
        for (std::uint8_t step_id = 0; step_id != SUM_HARD_BUTTON_STEPS; ++step_id)
        {
            row.add(Button(step_id + row_id * 16, -1));
        }
        _buttons.add(row);

        // OPTION BUTTONS TO
        _buttons_top.add(ButtonTop(row_id + 104, -1)); // Launchpad starts from 104 CC
    }

    // OPTION BUTTONS
    for (std::uint8_t step_id = 0; step_id != SUM_HARD_BUTTON_STEPS; ++step_id)
    {
        _buttons_right.add(ButtonRight(8 + step_id * 16, -1));
    }
}

// ********************************************************************************************

//// LAUNCHPAD CHILDS

//// CTORS

Launchpad::Button::Button(std::uint8_t hard_button_note_number_, std::int8_t)
    : cache_launchpad_controller_value(-1), // UNKNOWN
      message(juce::MidiMessage::noteOn(1, hard_button_note_number_, std::uint8_t(0))),
      is_pressed(false)
{
}

// ********************************************************************************************

Launchpad::ButtonRight::ButtonRight(std::uint8_t hard_button_note_number_,
                                    std::int8_t controller_value_)
    : Button(hard_button_note_number_, controller_value_), is_pressed(false)
{
}

// ********************************************************************************************

Launchpad::ButtonTop::ButtonTop(std::uint8_t hard_button_note_number_,
                                std::int8_t controller_value_)
    : Button(hard_button_note_number_, controller_value_)
{
    message =
        juce::MidiMessage::controllerEvent(1, hard_button_note_number_, int(controller_value_));
}

//// AND THE IMPL

static inline std::uint8_t get_releative_step_id(std::uint8_t mode_, std::uint8_t hard_step_id_)
{
    switch (mode_)
    {
    case LAUNCHPAD_MODE_USER_1:
        return hard_step_id_;
    case LAUNCHPAD_MODE_USER_2:
        return hard_step_id_ + 8;
    case LAUNCHPAD_MODE_SESSION:
        return hard_step_id_ * 2;
    default:
        return hard_step_id_;
    }
}

void Launchpad::process_colormessage_for_button(std::uint8_t color_, std::uint8_t channel_,
                                                Launchpad::Button &button_,
                                                juce::Array<juce::MidiMessage *> &messages_,
                                                bool force_)
{
    if (color_ != button_.cache_launchpad_controller_value)
    {
        // NOTE TODO clean this up, i have changed juce message for this
        button_.message.setVelocity(1.0f / 127 * color_);
        button_.cache_launchpad_controller_value = color_;
        button_.message.setChannel(channel_);
        messages_.add(&button_.message);
    }
}

void Launchpad::process_colormessage_CC_for_button(std::uint8_t color_, std::uint8_t channel_,
                                                   Launchpad::Button &button_,
                                                   juce::Array<juce::MidiMessage *> &messages_,
                                                   bool force_)
{
    if (color_ != button_.cache_launchpad_controller_value)
    {
        button_.message = juce::MidiMessage::controllerEvent(
            channel_out, button_.message.getControllerNumber(), color_);
        button_.cache_launchpad_controller_value = color_;
        messages_.add(&button_.message);
    }
}

void Launchpad::get_updates(juce::Array<juce::MidiMessage *> &messages_)
{
    const Bar &selected_bar =
        _app_instance_store->pattern.bar(_app_instance_store->editor_config.selected_bar_id);
    const Pattern &pattern = _app_instance_store->pattern;

    for (std::uint8_t hard_row_id = 0; hard_row_id != SUM_HARD_BUTTON_ROWS; ++hard_row_id)
    {
        // OPTION BUTTONS TOP
        {
            ButtonTop &option_button_top = _buttons_top.getReference(hard_row_id);
            switch (option_button_top.message.getControllerNumber())
            {
            case FIXED_LAUNCHPAD_TOP_UP: // speed
                process_colormessage_CC_for_button(
                    get_speed_up_color(*_app_instance_store->audio_processor), channel_out,
                    option_button_top, messages_);
                break;
            case FIXED_LAUNCHPAD_TOP_DOWN:
                process_colormessage_CC_for_button(
                    get_speed_down_color(*_app_instance_store->audio_processor), channel_out,
                    option_button_top, messages_);
                break;
            case FIXED_LAUNCHPAD_TOP_LEFT:
                process_colormessage_CC_for_button(get_mode_arrow_color(), channel_out,
                                                   option_button_top, messages_);
                break;
            case FIXED_LAUNCHPAD_TOP_RIGHT:
                process_colormessage_CC_for_button(get_mode_arrow_color(), channel_out,
                                                   option_button_top, messages_);
                break;
            case FIXED_LAUNCHPAD_TOP_SESSION: // SESSION
                if (mode == LAUNCHPAD_MODE_SESSION)
                    process_colormessage_CC_for_button(get_mode_color(), channel_out,
                                                       option_button_top, messages_);
                else
                    process_colormessage_CC_for_button(LAUNCHPAD_OFF, channel_out,
                                                       option_button_top, messages_);
                break;
            case FIXED_LAUNCHPAD_TOP_USER_1: // USER 1
                if (mode == LAUNCHPAD_MODE_USER_1)
                    process_colormessage_CC_for_button(get_mode_color(), channel_out,
                                                       option_button_top, messages_);
                else
                    process_colormessage_CC_for_button(LAUNCHPAD_OFF, channel_out,
                                                       option_button_top, messages_);
                break;
            case FIXED_LAUNCHPAD_TOP_USER_2: // USER 1
                if (mode == LAUNCHPAD_MODE_USER_2)
                    process_colormessage_CC_for_button(get_mode_color(), channel_out,
                                                       option_button_top, messages_);
                else
                    process_colormessage_CC_for_button(LAUNCHPAD_OFF, channel_out,
                                                       option_button_top, messages_);
                break;
            case FIXED_LAUNCHPAD_TOP_MIXER: // SHOW PAGE 1 or 2 1
                process_colormessage_CC_for_button(get_scroll_color(_current_scroll_offset),
                                                   channel_out, option_button_top, messages_);
                break;
            }
        }

        // OPTION BUTTONS ( RIGHT )
        {
            ButtonRight &option_button = _buttons_right.getReference(hard_row_id);
            if (_buttons_right.getReference(hard_row_id).is_pressed)
                ; // process_colormessage_for_button( get_pressed_option_color(), _channel_out,
                  // option_button, messages );
            else
                ; // process_colormessage_for_button( LAUNCHPAD_OFF, _channel_out, option_button,
                  // messages );

            // GLOBAL ROTARY
            // TODO not with the scrolloffset!
            if (_current_scroll_offset == SCROLL_OFFSET_PAGE_1)
            {
                switch (hard_row_id)
                {
                case FIXED_LAUNCHPAD_PAGE_1_SHIFT_CARLA_CC_FIX:
                    if (_buttons_right.getReference(hard_row_id).is_pressed)
                        process_colormessage_for_button(get_pressed_option_color(), channel_out,
                                                        option_button, messages_);
                    else
                        process_colormessage_for_button(LAUNCHPAD_OFF, channel_out, option_button,
                                                        messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_OCTAVE_UP:
                    process_colormessage_for_button(get_global_octave_up_color(pattern),
                                                    channel_out, option_button, messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_OCTAVE_DOWN:
                    process_colormessage_for_button(get_global_octave_down_color(pattern),
                                                    channel_out, option_button, messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_NOTE_UP:
                    process_colormessage_for_button(get_global_note_up_color(pattern), channel_out,
                                                    option_button, messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_NOTE_DOWN:
                    process_colormessage_for_button(get_global_note_down_color(pattern),
                                                    channel_out, option_button, messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_CHORD_UP:
                    process_colormessage_for_button(get_global_chord_type_up_color(pattern),
                                                    channel_out, option_button, messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_CHORD_DOWN:
                    process_colormessage_for_button(get_global_chord_type_down_color(pattern),
                                                    channel_out, option_button, messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_SET_SOLO_BAR:
                    if (_buttons_right.getReference(hard_row_id).is_pressed)
                        process_colormessage_for_button(get_pressed_option_color(), channel_out,
                                                        option_button, messages_);
                    else
                        process_colormessage_for_button(LAUNCHPAD_OFF, channel_out, option_button,
                                                        messages_);
                    break;
                }
            }
            if (_current_scroll_offset == SCROLL_OFFSET_PAGE_2)
            {
                switch (hard_row_id)
                {
                case FIXED_LAUNCHPAD_PAGE_1_SHIFT_CARLA_CC_FIX:
                    if (_buttons_right.getReference(hard_row_id).is_pressed)
                        process_colormessage_for_button(get_pressed_option_color(), channel_out,
                                                        option_button, messages_);
                    else
                        process_colormessage_for_button(LAUNCHPAD_OFF, channel_out, option_button,
                                                        messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_OCTAVE_UP:
                    process_colormessage_for_button(LAUNCHPAD_OFF, channel_out, option_button,
                                                    messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_OCTAVE_DOWN:
                    process_colormessage_for_button(LAUNCHPAD_OFF, channel_out, option_button,
                                                    messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_NOTE_UP:
                    process_colormessage_for_button(LAUNCHPAD_OFF, channel_out, option_button,
                                                    messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_NOTE_DOWN:
                    if (_buttons_right.getReference(hard_row_id).is_pressed)
                        process_colormessage_for_button(get_pressed_option_color(), channel_out,
                                                        option_button, messages_);
                    else
                        process_colormessage_for_button(LAUNCHPAD_OFF, channel_out, option_button,
                                                        messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_CHORD_UP:
                    if (_buttons_right.getReference(hard_row_id).is_pressed)
                        process_colormessage_for_button(get_pressed_option_color(), channel_out,
                                                        option_button, messages_);
                    else
                        process_colormessage_for_button(LAUNCHPAD_OFF, channel_out, option_button,
                                                        messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_CHORD_DOWN:
                    if (_buttons_right.getReference(hard_row_id).is_pressed)
                        process_colormessage_for_button(get_pressed_option_color(), channel_out,
                                                        option_button, messages_);
                    else
                        process_colormessage_for_button(LAUNCHPAD_OFF, channel_out, option_button,
                                                        messages_);
                    break;
                case FIXED_LAUNCHPAD_PAGE_1_SET_SOLO_BAR:
                    if (_buttons_right.getReference(hard_row_id).is_pressed)
                        process_colormessage_for_button(get_pressed_option_color(), channel_out,
                                                        option_button, messages_);
                    else
                        process_colormessage_for_button(LAUNCHPAD_OFF, channel_out, option_button,
                                                        messages_);
                    break;
                }
            }
        }

        // MATRIX BUTTONS
        {
            for (std::uint8_t hard_step_id = 0; hard_step_id != SUM_HARD_BUTTON_STEPS;
                 ++hard_step_id)
            {
                Button &button = _buttons.getReference(hard_row_id).getReference(hard_step_id);

                const std::uint8_t relative_row = hard_row_id + _current_scroll_offset;
                const std::uint8_t releative_step_id_ = get_releative_step_id(mode, hard_step_id);

                // on session we handle the bar from 1 to 8 only on user_2 we take 9 to 16
                const std::uint8_t session_mode_bar_id =
                    (mode == LAUNCHPAD_MODE_SESSION) ? hard_step_id : releative_step_id_;

                if (hard_row_id == FIXED_LAUNCHPAD_ROW_STEP_RUNLIGHT)
                {
                    // RUN LIGHT STEP
                    // TODO move to function start
                    std::uint8_t running_step_id =
                        _app_instance_store->sequencer.get_running_step_id(0); // TODO, for groups?
                    if (releative_step_id_ == running_step_id)
                        process_colormessage_for_button(get_launchpad_running_step_color(true),
                                                        channel_out, button, messages_);
                    else if (mode == LAUNCHPAD_MODE_SESSION &&
                             releative_step_id_ == running_step_id + 1)
                    {
                        process_colormessage_for_button(get_launchpad_running_step_color(true),
                                                        channel_out, button, messages_);
                    }
                    else
                        process_colormessage_for_button(get_launchpad_running_step_color(false),
                                                        channel_out, button, messages_);
                }
                /*
                // TODO removed standard solo bar things
                              // BAR SELECT & RUN LIGHT
                              else if ( hard_row_id == FIXED_LAUNCHPAD_ROW_STEP_BAR_SELECT ) {
                                  // SOLO BAR
                                  if ( session_mode_bar_id ==
                _app_instance_store->sequencer.get_solo_bar_id() ) process_colormessage_for_button (
                get_launchpad_solo_bar_color ( true ), channel_out, button, messages );
                                  // RUN LIGHT BAR
                                  else if ( session_mode_bar_id ==
                _app_instance_store->sequencer.get_running_bar_id() )
                                      process_colormessage_for_button (
                get_launchpad_running_bar_color ( true ), channel_out, button, messages );
                                  // SELECTED BAR LIGHT
                                  else if ( selected_bar.id == session_mode_bar_id )
                                      process_colormessage_for_button (
                get_launchpad_selected_bar_color ( true ), channel_out, button, messages ); else
                                      process_colormessage_for_button (
                get_launchpad_selected_bar_color ( false ), channel_out, button, messages );
                              }
                              */
                // STEP BUTTONS ( every second step on session )
                else if (relative_row <= RELEATIVE_LAUNCHPAD_END_ROW_STEPS)
                {
                    std::uint8_t barstring_id =
                        relative_row - 1; // remove simply the step light row
                    std::uint8_t current_step_color = get_launchpad_steps_color(
                        selected_bar.barstring(barstring_id).step(releative_step_id_).is_mute);
                    process_colormessage_for_button(current_step_color, channel_out, button,
                                                    messages_);
                }
                // BAR OCTAVE UP
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_BAR_CHORD_UP)
                {
                    Bar &bar = _app_instance_store->pattern.bar(session_mode_bar_id);
                    std::uint8_t current_chord_up_color = get_launchpad_bar_chord_color_up(bar);
                    process_colormessage_for_button(current_chord_up_color, channel_out, button,
                                                    messages_);
                }
                // BAR OCTAVE DOWN
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_BAR_CHORD_DOWN)
                {
                    Bar &bar = _app_instance_store->pattern.bar(session_mode_bar_id);
                    std::uint8_t current_chord_down_color = get_launchpad_bar_chord_color_down(bar);
                    process_colormessage_for_button(current_chord_down_color, channel_out, button,
                                                    messages_);
                }
                // OCTAVE UP
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_BAR_OCTAVE_UP)
                {
                    Bar &bar = _app_instance_store->pattern.bar(session_mode_bar_id);
                    std::uint8_t current_chord_up_color = get_launchpad_bar_octave_color_up(bar);
                    process_colormessage_for_button(current_chord_up_color, channel_out, button,
                                                    messages_);
                }
                // OCTAVE DOWN
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_BAR_OCTAVE_DOWN)
                {
                    Bar &bar = _app_instance_store->pattern.bar(session_mode_bar_id);
                    std::uint8_t current_chord_down_color =
                        get_launchpad_bar_octave_color_down(bar);
                    process_colormessage_for_button(current_chord_down_color, channel_out, button,
                                                    messages_);
                }
                // spacer
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_SPACER_OCTAVE)
                {
                    process_colormessage_for_button(LAUNCHPAD_OFF, channel_out, button, messages_);
                }
                // DURATION
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_DURATION)
                {
                    std::uint8_t current_duration_color = get_launchpad_duration_color(
                        selected_bar.barstep(releative_step_id_).duration);
                    process_colormessage_for_button(current_duration_color, channel_out, button,
                                                    messages_);
                }
                // VELOCITY
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_VECLOCITY)
                {
                    std::uint8_t current_velocity_color = get_launchpad_velocity_color(
                        selected_bar.barstep(releative_step_id_).velocity);
                    process_colormessage_for_button(current_velocity_color, channel_out, button,
                                                    messages_);
                }
                // REPATS
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_REPATS)
                {
                    std::uint8_t current_repeats_color = get_launchpad_bar_repeat_color(
                        _app_instance_store->pattern.bar(session_mode_bar_id));
                    process_colormessage_for_button(current_repeats_color, channel_out, button,
                                                    messages_);
                }
            }
        }
    }
}

static inline std::uint8_t get_pref_valid_autochain_bar_id(const Pattern &pattern_,
                                                           unsigned int from_bar_id_)
{
    // check all bars from current + 1
    if (from_bar_id_ != 0)
        for (std::uint8_t bar_id = from_bar_id_ - 1; bar_id >= 0; --bar_id)
        {
            if (Sequencer::is_valid_for_auto_chain(pattern_.bar(bar_id)))
                return bar_id;
        }

    // check all bars from 0 to current
    for (std::uint8_t bar_id = SUM_BARS - 1; bar_id != from_bar_id_ || bar_id > 0; --bar_id)
    {
        if (Sequencer::is_valid_for_auto_chain(pattern_.bar(bar_id)))
            return bar_id;
        if (bar_id == 0)
            return from_bar_id_;
    }

    return from_bar_id_;
}
static inline std::uint8_t get_next_valid_autochain_bar_id(const Pattern &pattern_,
                                                           unsigned int from_bar_id_)
{
    // check all bars from current + 1
    for (std::uint8_t bar_id = from_bar_id_ + 1; bar_id < SUM_BARS; ++bar_id)
    {
        if (Sequencer::is_valid_for_auto_chain(pattern_.bar(bar_id)))
            return bar_id;
    }

    // check all bars from 0 to current
    if (from_bar_id_ != 0)
        for (std::uint8_t bar_id = 0; bar_id != from_bar_id_; ++bar_id)
        {
            if (Sequencer::is_valid_for_auto_chain(pattern_.bar(bar_id)))
                return bar_id;
        }

    return from_bar_id_;
}
// TODO LIST
// double hit makes solo
// duuble hit anywhere will disable solo
// repeat
// refresh on bottom right!
// LEFT RIGHT SCROLL THROUGH CHAINABLE BARS!
void Launchpad::process(const juce::MidiMessage &message_)
{
    // check if we have the corrent channel
    // check the mode per pad
    //
    if (message_.getChannel() != channel_in)
        return;

    // TODO return if > 8 buttons or not an launchpad signal!

    // SWITCH for rotary control
    if (message_.isController())
    {
        if (message_.getControllerValue() != LAUNCHPAD_OFF)
        {
            std::uint8_t controller_value = message_.getControllerNumber();
            switch (controller_value)
            {
            case FIXED_LAUNCHPAD_TOP_UP_CARLA_FIX:;
            case FIXED_LAUNCHPAD_TOP_UP:
                if (_app_instance_store->audio_processor->speed ==
                    APPDEF_ProcessorUserData::SPEED_HALF)
                    _app_instance_store->audio_processor->speed =
                        APPDEF_ProcessorUserData::SPEED_NORMAL;
                else if (_app_instance_store->audio_processor->speed ==
                         APPDEF_ProcessorUserData::SPEED_NORMAL)
                    _app_instance_store->audio_processor->speed =
                        APPDEF_ProcessorUserData::SPEED_DOUBLE;
                else if (_app_instance_store->audio_processor->speed ==
                         APPDEF_ProcessorUserData::SPEED_DOUBLE)
                    _app_instance_store->audio_processor->speed =
                        APPDEF_ProcessorUserData::SPEED_HALF;
                break;
            case FIXED_LAUNCHPAD_TOP_DOWN_CARLA_FIX:;
            case FIXED_LAUNCHPAD_TOP_DOWN:
                if (_app_instance_store->audio_processor->speed ==
                    APPDEF_ProcessorUserData::SPEED_HALF)
                    _app_instance_store->audio_processor->speed =
                        APPDEF_ProcessorUserData::SPEED_DOUBLE;
                else if (_app_instance_store->audio_processor->speed ==
                         APPDEF_ProcessorUserData::SPEED_DOUBLE)
                    _app_instance_store->audio_processor->speed =
                        APPDEF_ProcessorUserData::SPEED_NORMAL;
                else if (_app_instance_store->audio_processor->speed ==
                         APPDEF_ProcessorUserData::SPEED_NORMAL)
                    _app_instance_store->audio_processor->speed =
                        APPDEF_ProcessorUserData::SPEED_HALF;
                break;
            case FIXED_LAUNCHPAD_TOP_LEFT_CARLA_FIX:;
            case FIXED_LAUNCHPAD_TOP_LEFT:
                _app_instance_store->editor_config.selected_bar_id =
                    get_pref_valid_autochain_bar_id(
                        _app_instance_store->pattern,
                        _app_instance_store->editor_config.selected_bar_id);
                break;
            case FIXED_LAUNCHPAD_TOP_RIGHT_CARLA_FIX:;
            case FIXED_LAUNCHPAD_TOP_RIGHT:
                _app_instance_store->editor_config.selected_bar_id =
                    get_next_valid_autochain_bar_id(
                        _app_instance_store->pattern,
                        _app_instance_store->editor_config.selected_bar_id);
                break;
            case FIXED_LAUNCHPAD_TOP_SESSION_CARLA_FIX:;
            case FIXED_LAUNCHPAD_TOP_SESSION:
                mode = LAUNCHPAD_MODE_SESSION;
                break;
            case FIXED_LAUNCHPAD_TOP_USER_1_CARLA_FIX:;
            case FIXED_LAUNCHPAD_TOP_USER_1:
                mode = LAUNCHPAD_MODE_USER_1;
                break;
            case FIXED_LAUNCHPAD_TOP_USER_2_CARLA_FIX:;
            case FIXED_LAUNCHPAD_TOP_USER_2:
                mode = LAUNCHPAD_MODE_USER_2;
                break;
            case FIXED_LAUNCHPAD_TOP_MIXER_CARLA_FIX:;
            case FIXED_LAUNCHPAD_TOP_MIXER:
                if (_current_scroll_offset > SCROLL_OFFSET_PAGE_1)
                    _current_scroll_offset = SCROLL_OFFSET_PAGE_1;
                else
                    _current_scroll_offset = SCROLL_OFFSET_PAGE_2;
                break;
            }
        }
    }
    // standard button handling
    else if (message_.isNoteOnOrOff())
    {
        std::uint8_t controller_number = message_.getControllerNumber();

        const std::uint8_t hard_button_step =
            controller_number % 16; // button 1:1 has value 0 --- button 3:1 has 33
        const std::uint8_t hard_button_row = (controller_number - hard_button_step) / 16;

        const std::uint8_t relative_row = hard_button_row + _current_scroll_offset;

        const std::uint8_t relative_button_id = get_releative_step_id(mode, hard_button_step);

        // on session we handle the bar from 1 to 8 only on user_2 we take 9 to 16
        const std::uint8_t session_mode_bar_id =
            (mode == LAUNCHPAD_MODE_SESSION) ? hard_button_step : relative_button_id;

        // PROCESSING
        if (message_.isNoteOn())
        {
            if (hard_button_step == LAUNCHPAD_RIGHT_OPTION_COLUM)
            {
                _buttons_right.getReference(hard_button_row).is_pressed = true;

                if (_current_scroll_offset != SCROLL_OFFSET_PAGE_2)
                {
                    switch (hard_button_row)
                    {
                    case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_OCTAVE_UP:
                        _app_instance_store->pattern.octave_offset++;
                        break;
                    case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_OCTAVE_DOWN:
                        _app_instance_store->pattern.octave_offset--;
                        break;
                    case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_NOTE_UP:
                        _app_instance_store->pattern.note_offset++;
                        break;
                    case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_NOTE_DOWN:
                        _app_instance_store->pattern.note_offset--;
                        break;
                    case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_CHORD_UP:
                        _app_instance_store->pattern.chord_type++;
                        break;
                    case FIXED_LAUNCHPAD_PAGE_1_GLOBAL_CHORD_DOWN:
                        _app_instance_store->pattern.chord_type--;
                        break;
                    }
                }
            }
            else if (hard_button_row == FIXED_LAUNCHPAD_ROW_STEP_RUNLIGHT)
            { // runlight
                if (_buttons_right.getReference(FIXED_LAUNCHPAD_ROW_STEP_RUNLIGHT).is_pressed)
                {
                    switch (hard_button_step)
                    {
                    case 0:
                        if (_app_instance_store->audio_processor->speed ==
                            GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_HALF)
                            _app_instance_store->audio_processor->speed =
                                GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_NORMAL;
                        else if (_app_instance_store->audio_processor->speed ==
                                 GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_NORMAL)
                            _app_instance_store->audio_processor->speed =
                                GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_DOUBLE;
                        else if (_app_instance_store->audio_processor->speed ==
                                 GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_DOUBLE)
                            _app_instance_store->audio_processor->speed =
                                GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_HALF;
                        break;
                    case 1:
                        if (_app_instance_store->audio_processor->speed ==
                            GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_HALF)
                            _app_instance_store->audio_processor->speed =
                                GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_DOUBLE;
                        else if (_app_instance_store->audio_processor->speed ==
                                 GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_DOUBLE)
                            _app_instance_store->audio_processor->speed =
                                GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_NORMAL;
                        else if (_app_instance_store->audio_processor->speed ==
                                 GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_NORMAL)
                            _app_instance_store->audio_processor->speed =
                                GstepAudioProcessor::ProcessorUserData::appdeff_t::SPEED_HALF;
                        break;
                    case 2:
                        if (mode == LAUNCHPAD_MODE_SESSION)
                            mode = LAUNCHPAD_MODE_USER_2;
                        else if (mode == LAUNCHPAD_MODE_USER_2)
                            mode = LAUNCHPAD_MODE_USER_1;
                        else if (mode == LAUNCHPAD_MODE_USER_1)
                            mode = LAUNCHPAD_MODE_SESSION;
                        break;
                    case 3:
                        if (mode == LAUNCHPAD_MODE_SESSION)
                            mode = LAUNCHPAD_MODE_USER_1;
                        else if (mode == LAUNCHPAD_MODE_USER_1)
                            mode = LAUNCHPAD_MODE_USER_2;
                        else if (mode == LAUNCHPAD_MODE_USER_2)
                            mode = LAUNCHPAD_MODE_SESSION;
                        break;
                    case 4:; // SESSION
                        mode = LAUNCHPAD_MODE_SESSION;
                        break;
                    case 5:; // USER 1
                        mode = LAUNCHPAD_MODE_USER_1;
                        break;
                    case 6:; // USER 2
                        mode = LAUNCHPAD_MODE_USER_2;
                        break;
                    case 7:; // USER 2
                        if (_current_scroll_offset > SCROLL_OFFSET_PAGE_1)
                            _current_scroll_offset = SCROLL_OFFSET_PAGE_1;
                        else
                            _current_scroll_offset = SCROLL_OFFSET_PAGE_2;
                        break;
                    };
                }
            }
            else if (hard_button_row == FIXED_LAUNCHPAD_ROW_STEP_BAR_SELECT)
            { // bar select
                if (_buttons_right.getReference(FIXED_LAUNCHPAD_PAGE_1_SET_SOLO_BAR).is_pressed)
                    // TODO solo bar things
                    ; //_app_instance_store->sequencer.set_current_solo_bar_id ( session_mode_bar_id
                      //);
                else if (hard_button_step != LAUNCHPAD_RIGHT_OPTION_COLUM)
                {
                    std::int8_t bar_button_pressed = -1;
                    for (int id = 0;
                         id != _buttons.getReference(FIXED_LAUNCHPAD_ROW_STEP_BAR_SELECT).size();
                         ++id)
                    {
                        if (_buttons.getReference(FIXED_LAUNCHPAD_ROW_STEP_BAR_SELECT)
                                .getReference(id)
                                .is_pressed)
                        {
                            bar_button_pressed = id;
                        }
                    }
                    if (bar_button_pressed != -1)
                        _app_instance_store->pattern.bar(session_mode_bar_id) =
                            _app_instance_store->pattern.bar(bar_button_pressed);
                    else
                        _buttons.getReference(FIXED_LAUNCHPAD_ROW_STEP_BAR_SELECT)
                            .getReference(session_mode_bar_id)
                            .is_pressed = true;

                    _app_instance_store->editor_config.selected_bar_id = session_mode_bar_id;
                }
            }
            else
            {
                // STEP BUTTONS
                if (relative_row <= RELEATIVE_LAUNCHPAD_END_ROW_STEPS)
                {
                    Bar &selected_bar = _app_instance_store->pattern.bar(
                        _app_instance_store->editor_config.selected_bar_id);

                    std::uint8_t barstring_id =
                        relative_row - 1; // remove simply the step light row
                    selected_bar.barstring(barstring_id).step(relative_button_id).is_mute.invert();
                }
                // BAR CHORD UP
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_BAR_CHORD_UP)
                {
                    _app_instance_store->pattern.bar(session_mode_bar_id).chord_id++;
                }
                // BAR CHORD DOWN
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_BAR_CHORD_DOWN)
                {
                    _app_instance_store->pattern.bar(session_mode_bar_id).chord_id--;
                }
                // BAR OCTAVE
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_BAR_OCTAVE_UP)
                {
                    _app_instance_store->pattern.bar(session_mode_bar_id).octave_offset++;
                }
                // BAR CHORD
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_BAR_OCTAVE_DOWN)
                {
                    _app_instance_store->pattern.bar(session_mode_bar_id).octave_offset--;
                }
                // DURATION
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_DURATION)
                {
                    Bar &selected_bar = _app_instance_store->pattern.bar(
                        _app_instance_store->editor_config.selected_bar_id);
                    if (_buttons_right.getReference(hard_button_row).is_pressed)
                        selected_bar.barstep(relative_button_id).duration--;
                    else
                        selected_bar.barstep(relative_button_id).duration++;
                }
                // VELOCITY
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_VECLOCITY)
                {
                    Bar &selected_bar = _app_instance_store->pattern.bar(
                        _app_instance_store->editor_config.selected_bar_id);
                    if (_buttons_right.getReference(hard_button_row).is_pressed)
                        selected_bar.barstep(relative_button_id).velocity -= 5;
                    else
                        selected_bar.barstep(relative_button_id).velocity += 5;
                }
                // BAR REPEAT
                else if (relative_row == RELEATIVE_LAUNCHPAD_ROW_REPATS)
                {
                    Bar &bar_at_step = _app_instance_store->pattern.bar(session_mode_bar_id);
                    if (_buttons_right.getReference(hard_button_row).is_pressed)
                        bar_at_step.repeats--;
                    else
                        bar_at_step.repeats++;
                }
            }
        }
        // will be ignored for changes in the core
        else if (message_.isNoteOff())
        {
            if (hard_button_step == LAUNCHPAD_RIGHT_OPTION_COLUM)
            { // bar select
                _buttons_right.getReference(hard_button_row).is_pressed = false;
            }
            else if (hard_button_row == FIXED_LAUNCHPAD_ROW_STEP_BAR_SELECT)
            { // bar select
                if (hard_button_step != LAUNCHPAD_RIGHT_OPTION_COLUM)
                {
                    _buttons.getReference(FIXED_LAUNCHPAD_ROW_STEP_BAR_SELECT)
                        .getReference(session_mode_bar_id)
                        .is_pressed = false;
                }
            }
        }
    }

    return;
}

void Launchpad::refresh_all_buttons()
{
    for (std::uint8_t i = 0; i != _buttons.size(); ++i)
    {
        _buttons_right.getReference(i).cache_launchpad_controller_value = -1;
        _buttons_top.getReference(i).cache_launchpad_controller_value = -1;

        auto &buttons = _buttons.getReference(i);
        for (std::uint8_t j = 0; j != buttons.size(); ++j)
            buttons.getReference(j).cache_launchpad_controller_value = -1;
    }
}

void Launchpad::all_buttons_off(juce::Array<juce::MidiMessage *> &messages_)
{
    for (std::uint8_t i = 0; i != _buttons.size(); ++i)
    {
        _buttons_right.getReference(i).message.setVelocity(0);
        messages_.add(&_buttons_right.getReference(i).message);

        _buttons_top.getReference(i).message.setVelocity(0);
        messages_.add(&_buttons_top.getReference(i).message);

        auto &buttons = _buttons.getReference(i);
        for (std::uint8_t j = 0; j != buttons.size(); ++j)
        {
            buttons.getReference(j).message.setVelocity(0);
            messages_.add(&buttons.getReference(j).message);
        }
    }
}
