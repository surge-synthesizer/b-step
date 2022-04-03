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

#ifndef PARAMETER_INCLUDED
#define PARAMETER_INCLUDED

#include "App.h"
#include "AppInstanceStore.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
typedef int pod_type;
class PodParameterBase
{
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // PROPERTIE REFERENCES
  protected:
    pod_type _value;
    const pod_type MIN;
    const pod_type MAX;
    juce::String _string_value;

    const pod_type DEFAULT;

    const unsigned int _index;
    const char *const _param_ident;
    const char *const _param_unique_ident;
    const char *const _help_url;
    int id;
    const juce::String _param_short_ident;
    const juce::String _name;

    //// PROPERTIES
  protected:
    inline void try_set_value(pod_type value_)
    {
        if (value_ >= MIN)
            if (value_ <= MAX)
            {
                _value = value_;
                _string_value = juce::String(_value);
            }
    }

  public:
    inline pod_type value() const { return _value; }
    inline unsigned int index() const { return _index; }
    inline const juce::String &name() const { return _name; }
    inline const char *get_param_ident() const { return _param_ident; }
    inline const char *get_param_unique_ident() const { return _param_unique_ident; }
    inline const char *get_help_url() const { return _help_url; }
    inline const juce::String &get_param_short_ident() const { return _param_short_ident; }

    //// COMPARE

    inline bool operator==(pod_type value_) const { return (_value == value_); }

    inline bool operator!=(pod_type value_) const { return (_value != value_); }

    inline bool operator>=(pod_type value_) const { return (_value >= value_); }

    inline bool operator<=(pod_type value_) const { return (_value <= value_); }

    inline bool operator>(pod_type value_) const { return (_value > value_); }

    inline bool operator<(pod_type value_) const { return (_value < value_); }

    //// GETTER

    inline operator pod_type() const { return _value; }

    //// MATH

    inline pod_type operator+(pod_type value_) const { return _value + value_; }

    inline pod_type operator-(pod_type value_) const { return _value - value_; }

    inline pod_type operator*(pod_type value_) const { return _value * value_; }

    inline pod_type operator/(pod_type value_) const { return _value / value_; }

    inline pod_type operator%(pod_type value_) const { return _value % value_; }

    // ASSIGNMENT

    inline pod_type operator=(pod_type value_)
    {
        try_set_value(value_);
        return _value;
    }
    inline pod_type operator=(const PodParameterBase &other_)
    {
        try_set_value(other_._value);
        return _value;
    }

    // ASSIGNMENT MATH

    inline pod_type &operator+=(pod_type value_)
    {
        try_set_value(_value + value_);
        return _value;
    }

    inline pod_type &operator-=(pod_type value_)
    {
        try_set_value(_value - value_);
        return _value;
    }

    inline pod_type &operator*=(pod_type value_)
    {
        try_set_value(_value * value_);
        return _value;
    }

    inline pod_type &operator/=(pod_type value_)
    {
        try_set_value(_value / value_);
        return _value;
    }

    inline pod_type &operator%=(pod_type value_)
    {
        try_set_value(_value % value_);
        return _value;
    }

    inline pod_type &operator++(pod_type)
    {
        try_set_value(_value + 1);
        return _value;
    }

    inline pod_type &operator--(pod_type)
    {
        try_set_value(_value - 1);
        return _value;
    }

    struct NotifiableWrapper
    {
        virtual ~NotifiableWrapper() = default;
        virtual void begin() = 0;
        virtual void end() = 0;
        virtual void notify(float f) = 0;
    };
    NotifiableWrapper *wrapper{nullptr};
    inline void beginChangeGesture()
    {
        if (wrapper)
            wrapper->begin();
    }
    inline void endChangeGesture()
    {
        if (wrapper)
            wrapper->end();
    }
    inline pod_type set_value_notifying_host(pod_type value_)
    {
        try_set_value(value_);
        notifyCurrent();
        return _value;
    }
    void notifyCurrent()
    {
        if (wrapper)
            wrapper->notify(in_percent());
    }

    inline pod_type set_value(pod_type value_)
    {
        try_set_value(value_);
        return _value;
    }

    inline bool isBoolean()
    {
        // FIXME - this compare is super gross
        // UPDATE - made it even grosserer but silences MSVC C4805
        return MIN == false && MAX == static_cast<int>(true);
    }

    inline pod_type invert()
    {
        if (isBoolean())
        {
            try_set_value(!_value);
            return _value;
        }
        else
        {
            try_set_value(-1 * _value);
            return _value;
        }
    }

    //// TRANSLATIONS

    // 0 to 1.0f
    inline float in_percent() const { return 1.0f / (MAX - MIN) * (_value - MIN); }

    inline float default_value_in_percent() const { return 1.0f / (MAX - MIN) * (DEFAULT - MIN); }

    // 0 to 1.0f
    inline float set_from_percent(float percent_)
    {
        if (isBoolean())
        {
            try_set_value(percent_ > 0.5f ? true : false);
        }
        else
        {
            try_set_value(percent_ * (MAX - MIN) + MIN);
        }
        return in_percent();
    }

    inline const juce::String &as_string() const { return _string_value; }

    inline unsigned int num_steps() const { return MAX + 1 - MIN; }

    inline int default_value() const { return DEFAULT; }

    inline int max_value() const { return MAX; }

    inline int min_value() const { return MIN; }

    // REMOTE
    pod_type remote_state;
    inline void set_remote_value(pod_type for_host_) { remote_state = for_host_; }
    inline pod_type remote_value() const { return remote_state; }
    inline std::uint8_t value_unsigned() const { return _value - MIN; }
    inline std::uint8_t remote_value_unsigned() const { return remote_state - MIN; }
    inline pod_type set_value_unsigned(std::uint8_t value_)
    {
        try_set_value(value_ + MIN);
        return _value;
    }

  protected:
    PodParameterBase(pod_type value_, const unsigned int index_, const char *const param_ident_,
                     const char *const param_unique_ident_, const char *const help_url_,
                     const juce::String &param_short_ident_, const juce::String &name_,
                     const pod_type min_, const pod_type max_, const pod_type default_,
                     int id_ = -1);

#ifdef DEBUG
    virtual
#endif
        ~PodParameterBase();

    JUCE_LEAK_DETECTOR(PodParameterBase)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct NO_IDENT_DEFINED // DUMMY FOR APPPARAMETERLIST
{
    enum IDS
    {
        DUMMY
    };

    static const char *parameter_name(int) { return "PLEASE REPORT -> BUG"; }
    static const char *parameter_name_short(int) { return "PLEASE REPORT -> BUG"; }
    static const char *get_help_url(int) { return ""; }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NO_IDENT_DEFINED)
};
template <pod_type MIN_, pod_type DEFAULT_, pod_type MAX_,
          unsigned int OWNER_INDEX_ = NO_IDENT_DEFINED::DUMMY,
          class IDENT_DEFINER_ = NO_IDENT_DEFINED>
class PodParameter : public PodParameterBase
{
  public:
    enum PARAMS
    {
        DEFAULT = DEFAULT_,
        MIN = MIN_,
        MAX = MAX_,

        INDEX = OWNER_INDEX_
    };

  public:
    typedef PodParameter<MIN_, DEFAULT_, MAX_, OWNER_INDEX_> type;

    // ASIGNMENT
    inline pod_type operator=(const type &other_) { return PodParameterBase::operator=(other_); }
    inline pod_type operator=(pod_type value_) { return PodParameterBase::operator=(value_); }

  public:
    PodParameter();
    PodParameter(int);
    PodParameter(const juce::String &);
};

template <pod_type MIN_, pod_type DEFAULT_, pod_type MAX_, unsigned int OWNER_INDEX_,
          class IDENT_DEFINER_>
PodParameter<MIN_, DEFAULT_, MAX_, OWNER_INDEX_, IDENT_DEFINER_>::PodParameter()
    : PodParameterBase(DEFAULT_, INDEX, IDENT_DEFINER_::parameter_name(OWNER_INDEX_),
                       IDENT_DEFINER_::parameter_name_short(OWNER_INDEX_),
                       IDENT_DEFINER_::get_help_url(OWNER_INDEX_),
                       IDENT_DEFINER_::parameter_name_short(OWNER_INDEX_),
                       juce::String(IDENT_DEFINER_::parameter_name(OWNER_INDEX_)), MIN, MAX,
                       DEFAULT)
{
}

template <pod_type MIN_, pod_type DEFAULT_, pod_type MAX_, unsigned int OWNER_INDEX_,
          class IDENT_DEFINER_>
PodParameter<MIN_, DEFAULT_, MAX_, OWNER_INDEX_, IDENT_DEFINER_>::PodParameter(
    const juce::String &manual_id_)
    : PodParameterBase(DEFAULT_, INDEX, IDENT_DEFINER_::parameter_name(OWNER_INDEX_),
                       IDENT_DEFINER_::parameter_name_short(OWNER_INDEX_),
                       IDENT_DEFINER_::get_help_url(OWNER_INDEX_),
                       juce::String(IDENT_DEFINER_::parameter_name_short(OWNER_INDEX_)) +
                           manual_id_,
                       juce::String(IDENT_DEFINER_::parameter_name(OWNER_INDEX_) + manual_id_), MIN,
                       MAX, DEFAULT)
{
}

template <pod_type MIN_, pod_type DEFAULT_, pod_type MAX_, unsigned int OWNER_INDEX_,
          class IDENT_DEFINER_>
PodParameter<MIN_, DEFAULT_, MAX_, OWNER_INDEX_, IDENT_DEFINER_>::PodParameter(int i)
    : PodParameterBase(DEFAULT_, INDEX, IDENT_DEFINER_::parameter_name(OWNER_INDEX_),
                       IDENT_DEFINER_::parameter_name_short(OWNER_INDEX_),
                       IDENT_DEFINER_::get_help_url(OWNER_INDEX_),
                       juce::String(IDENT_DEFINER_::parameter_name_short(OWNER_INDEX_)) +
                           juce::String("-") + juce::String(i + 1),
                       juce::String(IDENT_DEFINER_::parameter_name(OWNER_INDEX_)) +
                           (juce::String("-") + juce::String(i + 1)),
                       MIN, MAX, DEFAULT, i)
{
    return;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class Parameters
{
  private:
    juce::Array<PodParameterBase *> _store;

  public:
    inline unsigned int size() const { return _store.size(); }
    inline PodParameterBase *operator[](unsigned int index_) const
    {
        return _store.getUnchecked(index_);
    }

  public:
    Parameters(PodParameterBase *a_, PodParameterBase *b_ = nullptr, PodParameterBase *c_ = nullptr,
               PodParameterBase *d_ = nullptr, PodParameterBase *e_ = nullptr,
               PodParameterBase *f_ = nullptr, PodParameterBase *g_ = nullptr,
               PodParameterBase *h_ = nullptr, PodParameterBase *i_ = nullptr,
               PodParameterBase *j_ = nullptr, PodParameterBase *k_ = nullptr,
               PodParameterBase *l_ = nullptr, PodParameterBase *m_ = nullptr,
               PodParameterBase *n_ = nullptr, PodParameterBase *o_ = nullptr,
               PodParameterBase *p_ = nullptr, PodParameterBase *q_ = nullptr,
               PodParameterBase *r_ = nullptr, PodParameterBase *s_ = nullptr,
               PodParameterBase *t_ = nullptr, PodParameterBase *u_ = nullptr,
               PodParameterBase *v_ = nullptr, PodParameterBase *w_ = nullptr);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Parameters)
};

#endif // PARAMETER_INCLUDED
