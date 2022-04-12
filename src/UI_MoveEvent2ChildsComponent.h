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

#ifndef __UI_BIGGERAREASELECT_H__
#define __UI_BIGGERAREASELECT_H__

#include "App.h"
#include "Controller.h"
#include "_H_UiElements.h"

#define NEUTRAL_MOUSE_DOWN_POINT Point<int>(-1, -1)

class MoveEvent2ChildsComponent : public juce::Component
{
#ifdef USE_BIGGER_AREA_HACK
    juce::Point<int> _last_mouse_down_point;

  private:
    juce::Array<ModelBase *> _null_models;
    virtual const juce::Array<ModelBase *> &get_event_receiveable_models() { return _null_models; }

    enum MOUSE_EVENT_TYPE
    {
        MOUSE_DOWN,
        MOUSE_UP,
        MOUSE_MOVE,
        MOUSE_ENTER,
        MOUSE_DRAG,
        MOUSE_EXIT,
        MOUSE_WHEEL_MOVE,
        MOUSE_DOUBLE_CLICK
    };

    void mouseDown(const juce::MouseEvent &event_) override
    {
        try_trigger_mouse_event(event_, nullptr, MOUSE_DOWN);
    }

    void mouseUp(const juce::MouseEvent &event_) override
    {
        try_trigger_mouse_event(event_, nullptr, MOUSE_UP);
    }

    void mouseMove(const juce::MouseEvent &event_) override
    {
        try_trigger_mouse_event(event_, nullptr, MOUSE_MOVE);
    }

    void mouseEnter(const juce::MouseEvent &event_) override
    {
        try_trigger_mouse_event(event_, nullptr, MOUSE_ENTER);
    }

    void mouseExit(const juce::MouseEvent &event_) override
    {
        try_trigger_mouse_event(event_, nullptr, MOUSE_EXIT);
    }

    void mouseDrag(const juce::MouseEvent &event_) override
    {
        try_trigger_mouse_event(event_, nullptr, MOUSE_DRAG);
    }

    void mouseDoubleClick(const juce::MouseEvent &event_) override
    {
        try_trigger_mouse_event(event_, nullptr, MOUSE_DOUBLE_CLICK);
    }

    void mouseWheelMove(const juce::MouseEvent &event_,
                        const juce::MouseWheelDetails &wheel_) override
    {
        try_trigger_mouse_event(event_, &wheel_, MOUSE_WHEEL_MOVE);
    }

    void try_trigger_mouse_event(const juce::MouseEvent &event_,
                                 const juce::MouseWheelDetails *const wheel_,
                                 MOUSE_EVENT_TYPE event_type_)
    {
        int x = event_.getMouseDownX();
        int y = event_.getMouseDownY();

        for (int radius = 1; radius != 20; ++radius)
        {
            if (try_send_event_at(x, y - radius, event_, wheel_, event_type_))
                return;
            else if (try_send_event_at(x + radius, y - radius, event_, wheel_, event_type_))
                return;
            else if (try_send_event_at(x + radius, y, event_, wheel_, event_type_))
                return;
            else if (try_send_event_at(x + radius, y + radius, event_, wheel_, event_type_))
                return;
            else if (try_send_event_at(x, y + radius, event_, wheel_, event_type_))
                return;
            else if (try_send_event_at(x - radius, y + radius, event_, wheel_, event_type_))
                return;
            else if (try_send_event_at(x - radius, y, event_, wheel_, event_type_))
                return;
            else if (try_send_event_at(x - radius, y - radius, event_, wheel_, event_type_))
                return;
        }
    }

    inline bool try_send_event_at(int x_, int y_, const juce::MouseEvent &event_,
                                  const juce::MouseWheelDetails *const wheel_,
                                  MOUSE_EVENT_TYPE event_type_)
    {
        const juce::Array<ModelBase *> &models = get_event_receiveable_models();
        juce::Rectangle<int> bounds_in_parent;
        ModelBase *model;
        for (int i = 0; i != models.size(); ++i)
        {
            model = models.getUnchecked(i);
            bounds_in_parent = models.getUnchecked(i)->getBoundsInParent();
            if ((x_ >= bounds_in_parent.getX() &&
                 x_ <= bounds_in_parent.getX() + bounds_in_parent.getWidth()) &&
                ((y_ >= bounds_in_parent.getY() &&
                  y_ <= bounds_in_parent.getY() + bounds_in_parent.getHeight())))
            {
                juce::Component *const component = model->get_view();
                if (component)
                {
                    switch (event_type_)
                    {
                    case MOUSE_EXIT:
                        component->mouseExit(event_);
                        break;
                    case MOUSE_ENTER:
                        component->mouseEnter(event_);
                        break;
                    case MOUSE_DOWN:
                        component->mouseDown(event_);
                        break;
                    case MOUSE_UP:
                        component->mouseUp(event_);
                        break;
                    case MOUSE_MOVE:
                        component->mouseMove(event_);
                        break;
                    case MOUSE_DRAG:
                        component->mouseDrag(event_);
                        break;
                    case MOUSE_WHEEL_MOVE:
                        component->mouseWheelMove(event_, *wheel_);
                        break;
                    case MOUSE_DOUBLE_CLICK:
                        component->mouseDoubleClick(event_);
                        break;
                    }

                    return true;
                }
            }
        }

        return false;
    }

    JUCE_LEAK_DETECTOR(MoveEvent2ChildsComponent)
#endif
};

#endif // __UI_BIGGERAREASELECT_H__
