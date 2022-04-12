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

#include "Parameter.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
PodParameterBase::PodParameterBase(pod_type value_, const unsigned int index_,
                                   const char *const param_ident_,
                                   const char *const param_unique_ident_,
                                   const char *const help_url_,
                                   const juce::String &param_short_ident_,
                                   const juce::String &name_, const pod_type min_,
                                   const pod_type max_, const pod_type default_, int id_)
    : _value(value_),

      MIN(min_), MAX(max_),

      DEFAULT(default_),

      _index(index_),

      _param_ident(param_ident_), _param_unique_ident(param_unique_ident_), _help_url(help_url_),
      id(id_), _param_short_ident(param_short_ident_), _name(name_),

      remote_state(default_)
{
    if (MAX < 10)
    {
        _string_value.preallocateBytes(1);
    }
    if (MAX > 9)
    {
        _string_value.preallocateBytes(2);
    }
    else if (MAX > 99)
    {
        _string_value.preallocateBytes(3);
    }
    else if (MAX > 999)
    {
        _string_value.preallocateBytes(4);
    }
    else if (MAX > 9999)
    {
        _string_value.preallocateBytes(5);
    }

    _string_value = juce::String(_value);
}

PodParameterBase::~PodParameterBase() {}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
Parameters::Parameters(PodParameterBase *a_, PodParameterBase *b_, PodParameterBase *c_,
                       PodParameterBase *d_, PodParameterBase *e_, PodParameterBase *f_,
                       PodParameterBase *g_, PodParameterBase *h_, PodParameterBase *i_,
                       PodParameterBase *j_, PodParameterBase *k_, PodParameterBase *l_,
                       PodParameterBase *m_, PodParameterBase *n_, PodParameterBase *o_,
                       PodParameterBase *p_, PodParameterBase *q_, PodParameterBase *r_,
                       PodParameterBase *s_, PodParameterBase *t_, PodParameterBase *u_,
                       PodParameterBase *v_, PodParameterBase *w_)
{
    _store.add(a_);
    if (b_)
        _store.add(b_);
    if (c_)
        _store.add(c_);
    if (d_)
        _store.add(d_);
    if (e_)
        _store.add(e_);
    if (f_)
        _store.add(f_);
    if (g_)
        _store.add(g_);
    if (h_)
        _store.add(h_);
    if (i_)
        _store.add(i_);
    if (j_)
        _store.add(j_);
    if (k_)
        _store.add(k_);
    if (l_)
        _store.add(l_);
    if (m_)
        _store.add(m_);
    if (n_)
        _store.add(n_);
    if (o_)
        _store.add(o_);
    if (p_)
        _store.add(p_);
    if (q_)
        _store.add(q_);
    if (r_)
        _store.add(r_);
    if (s_)
        _store.add(s_);
    if (t_)
        _store.add(t_);
    if (u_)
        _store.add(u_);
    if (v_)
        _store.add(v_);
    if (w_)
        _store.add(w_);
    _store.minimiseStorageOverheads();
}
