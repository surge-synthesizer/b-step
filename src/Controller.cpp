/*
  ==============================================================================

    Controller.cpp
    Created: 18 May 2014 11:29:55am
    Author:  monotomy

  ==============================================================================
*/

#include "Controller.h"
#include "AppStyles.h"

#include "_H_UiElements.h"

#include "UiSettings.h"

#include "AppParameterList.h"
#include "MIDILearn.h"

ModelBase::ModelBase(MONO_Controller *const controller_, AppStyle *const style_)
    : _view(nullptr), _controller(nullptr), _style(nullptr), _background_style(nullptr),
      _background_color(0x00000000), should_repaint(false), _is_manual_opaque(true),
      _current_view_type(MONO_Controller::UI_VIEW_TYPES::UI_UNDEFINED)
{
    setRepaintsOnMouseActivity(false);
    // setBufferedToImage(false);
    // setPaintingIsUnclipped(true);
    setInterceptsMouseClicks(false, true);
    setOpaque(true);

    set_style(style_);

    if (controller_)
        set_controller(controller_);
}

ModelBase::~ModelBase()
{
    delete_view();

    if (_controller)
        _controller->set_model(nullptr);
}

void MONO_Controller::set_model(ModelBase *model_) { _model = model_; }

void ModelBase::set_controller(MONO_Controller *const controller_)
{
    _controller = controller_;
    if (_controller)
        _controller->set_model(this);
    setup_view();
}

void ModelBase::setup_view()
{
    if (_controller)
    {
        MONO_Controller::UI_VIEW_TYPES required_view_type = _controller->get_view_type();

        if (required_view_type == _current_view_type)
        {
            if (_view)
                _view->set_controller(_controller, this);

            _controller->setup_view(_view->get_top_level_impl());
        }
        else
        {
            delete_view();

            switch (required_view_type)
            {
            case MONO_Controller::UI_VIEW_TYPES::UI_BUTTON:
                set_view(new UiButton());
                break;
            case MONO_Controller::UI_VIEW_TYPES::UI_SLIDER:
                set_view(new UISlider());
                break;
            case MONO_Controller::UI_VIEW_TYPES::UI_LABEL:
                // set_view( new LabelController_() );
                break;
            default:
                set_view(nullptr);
            }
        }

        _current_view_type = required_view_type;
    }
}

void ModelBase::set_view(UIBase *const ui_element_)
{
    _view = ui_element_;
    if (_view)
    {
        _view->set_controller(_controller, this);
        _controller->setup_view(_view->get_top_level_impl());

        _view->resized(getWidth(), getHeight());

        if (_style)
            addAndMakeVisible(_view->get_top_level_component());
        else
            addChildComponent(_view->get_top_level_component());
    }
}

void ModelBase::delete_view()
{
    if (_view)
    {
        _view->set_controller(nullptr, nullptr);
        delete _view->get_top_level_component();
        _view = nullptr;
    }
}

void ModelBase::resized()
{
    if (_view)
    {
        _view->resized(getWidth(), getHeight());
        should_repaint = true;
    }
}

void ModelBase::get_components_to_repaint(Array<Component *> &components_)
{
    if (_view)
        if (_controller)
            if (_style)
            {
                _controller->prepare_current_ui_states();

                if (_view->refresh_foreground())
                    should_repaint = true;

                refresh_background();

                if (should_repaint)
                    components_.add(this);
            }
}

void ModelBase::refresh_background()
{
    uint32 new_bg_colour;
    uint32 working_colour;
    if (!_is_manual_opaque)
    {
        setOpaque(false);
        new_bg_colour = 0x00000000;
    }
    else if (_background_style)
    {
        working_colour = _background_style->get_foreground_color();
        setOpaque(working_colour);
        new_bg_colour = working_colour;
    }
    else if (_style)
    {
        working_colour = _style->get_foreground_color();
        setOpaque(working_colour);

        if (_style->is_opaque())
            new_bg_colour = working_colour;
        else
            new_bg_colour = 0x00000000;
    }
    else
    {
        setOpaque(false);
        new_bg_colour = 0x00000000;
    }

    if (new_bg_colour != _background_color)
    {
        _background_color = new_bg_colour;
        should_repaint = true;
    }
}

void ModelBase::paint(Graphics &g_)
{
    refresh_background();
    should_repaint = false;
    _view->cache_paint(g_, _background_color);
}

void ModelBase::set_manual_opaque(bool state_)
{
    _is_manual_opaque = state_;
    refresh_background();
    should_repaint = true;
}

void ModelBase::get_controllers_for_paint_popup(Array<MONO_Controller *> &controllers_for_popup_)
{
    if (_view)
        if (_controller)
            if (_controller->do_you_need_a_text_popup())
                controllers_for_popup_.add(_controller);
}

void ModelBase::set_style(AppStyle *const style_)
{
    if (_style != style_)
    {
        _style = style_;
        refresh_background();
    }

    if (_view)
    {
        Component *_view_component = _view->get_top_level_component();
        if (!_view_component->isVisible())
        {
            _view_component->setVisible(true);
        }
    }
}

void ModelBase::set_background_style(AppStyle *const style_)
{
    if (_background_style != style_)
    {
        _background_style = style_;
        refresh_background();
    }
}

uint32 MONO_Controller::get_current_color_low()
{
    bool use_midi_learn_colour = false;
    if (_app_instance_store->midi_in_map.is_in_learning_mode())
        if (is_learnable())
            use_midi_learn_colour = true;

    if (use_midi_learn_colour)
    {
        return Colour(get_current_color()).overlaidWith(Colour(0x66888888)).getARGB();
    }
    else
    {
        return get_current_color();
    }
}

Image &ModelBase::get_drag_image(Image &image) const
{
    int spacer = 20;
    image = Image(Image::ARGB, getWidth() + spacer, getHeight() + spacer, true);
    Graphics g(image);
    Colour col = Colours::yellow;
    if (_style)
        col = Colour(_style->get_font_color());
    g.setColour(col);
    g.drawEllipse(2, 2, getWidth() + spacer - 4, getHeight() + spacer - 4, 4);

    Image element = Image(Image::ARGB, getWidth(), getHeight(), true);
    Graphics g_element(element);
    _view->cache_paint(g_element, 0x00000000);

    g.drawImageAt(element, spacer / 2, spacer / 2);

    return image;
}

AppStyle *ModelBase::get_style() const { return _style; }

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const Component *MONO_Controller::get_ui_peer() const
{
    if (_model)
        return _model->get_view();

    return nullptr;
}

const ModelBase *MONO_Controller::get_model() const { return _model; }

Component *ModelBase::get_view() { return _view->get_top_level_component(); }

const MONO_Controller *ModelBase::get_controller() const { return _controller; }

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
MONO_Controller::MONO_Controller(AppInstanceStore *const app_instance_store_)
    : _model(nullptr), _app_instance_store(app_instance_store_), _dragNdrop_ident("DR"),
      _multidrag_ident("MDR")
{
    if (is_learnable())
        _app_instance_store->midi_mappable_controllers.add(this);
}
#include "UIHtmlView.h"
bool MONO_Controller::on_pre_mouse_down_escape(const MouseEvent &)
{
    if (_app_instance_store->editor_config.style_editor)
    {
        _app_instance_store->editor_config.current_editable_colour =
            &_model->get_style()->get_font_color();
        return true;
    }
    if (_app_instance_store->editor_config.manual_editor)
    {
        if (_model->get_controller())
            if (_model->get_controller()->get_parameter())
                _app_instance_store->editor_config.manual_editor->try_open_url(get_help_url());

        return true;
    }

    return false;
}

void MONO_Controller::on_clicked(bool do_realy_click_)
{
    if (is_click_blocked())
    {
        handle_blocked_click();
    }
    else
    {
        MultidragSource *const multidrag_source =
            _app_instance_store->editor_config.multidrag_source;
        if (!multidrag_source)
        {
            if (do_realy_click_)
                on_clicked_top();
        }
        else
        {
            if (_app_instance_store->editor_config.multidrag_source->controller_type_ident !=
                get_controller_type_ident())
            {
                if (do_realy_click_)
                    on_clicked_top();
            }
            _app_instance_store->editor_config.multidrag_source = nullptr;
        }
    }
}

void MONO_Controller::on_long_mouse_down()
{
    if (use_default_multi_drag())
    {
        MultidragSource *const multidrag_source =
            new MultidragSource(get_controller_type_ident(), this);
        multidrag_source->source_state = get_value();
        multidrag_source->alreay_handled_controllers.add(this);
        multidrag_source->is_drag_started = false;
        _app_instance_store->editor_config.multidrag_source = multidrag_source;
    }
}
bool MONO_Controller::should_start_multi_drag()
{
    MultidragSource *const multidrag_source = _app_instance_store->editor_config.multidrag_source;
    if (multidrag_source)
        if (!multidrag_source->is_drag_started)
            if (multidrag_source->controller_type_ident == get_controller_type_ident())
            {
                multidrag_source->alreay_handled_controllers.clear();
                multidrag_source->controller = this;
                multidrag_source->source_state = get_value();
                multidrag_source->alreay_handled_controllers.add(this);
                multidrag_source->is_drag_started = true;
                return true;
            }

    return false;
}
void MONO_Controller::get_label_text(String &string_) const
{
    if (_app_instance_store->midi_in_map.is_in_learning_mode())
        return;

    MultidragSource *const multidrag_source = _app_instance_store->editor_config.multidrag_source;
    if (multidrag_source)
    {
        if (multidrag_source->controller_type_ident == get_controller_type_ident())
        {
            if (multidrag_source->controller != this)
                string_ = String(".T.");
            else
                string_ = String(".S.");
        }
    }
    else
        get_label_text_top(string_);
}
bool MONO_Controller::is_interested_in_drag_source(
    const DragAndDropTarget::SourceDetails &dragSourceDetails_)
{
    if (_app_instance_store->midi_in_map.is_in_learning_mode())
        return false;

    if (dragSourceDetails_.sourceComponent.get()->getName().compare("TlR") == 0)
    {
        if (are_you_rubberable())
        {
            return true;
        }

        return false;
    }
    else if (dragSourceDetails_.sourceComponent.get()->getName().compare("TlQ") == 0)
    {
        return true;
    }
    else
    {
        MultidragSource *const multidrag_source =
            _app_instance_store->editor_config.multidrag_source;
        if (multidrag_source)
        {
            if (multidrag_source->controller_type_ident == get_controller_type_ident())
            {
                bool this_is_already_setted = false;
                for (int i = 0; i != multidrag_source->alreay_handled_controllers.size(); ++i)
                {
                    if (multidrag_source->alreay_handled_controllers.getUnchecked(i) == this)
                    {
                        this_is_already_setted = true;
                        break;
                    }
                }
                if (!this_is_already_setted)
                {
                    multidrag_source->alreay_handled_controllers.add(this);
                    on_value_changed(multidrag_source->source_state);
                }
            }
        }
    }
    return false;
}
#include "UIHtmlView.h"
void MONO_Controller::item_dropped(const DragAndDropTarget::SourceDetails &dragSourceDetails_)
{
    if (dragSourceDetails_.sourceComponent.get()->getName().compare("TlR") == 0)
    {
        rubber_droped();
    }
    else if (dragSourceDetails_.sourceComponent.get()->getName().compare("TlQ") == 0)
    {
        if (_app_instance_store->editor)
        {
            if (!_app_instance_store->editor_config.manual_editor)
                _app_instance_store->editor_config.manual_editor =
                    new UIHtmlView(_app_instance_store);

            _app_instance_store->editor_config.manual_editor->try_open_url(get_help_url());
        }
    }
    else
    {
        item_dropped_top(dragSourceDetails_);
    }
}

const String MONO_Controller::get_help_url()
{
    PodParameterBase *const param = get_parameter();
    if (param)
        return MANUAL_URL + param->get_help_url();

    return MANUAL_URL;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
UIBase::UIBase() : _controller(nullptr), _model(nullptr), _text(HAS_NO_TEXT_VALUE) {}

UIBase::~UIBase() {}

void UIBase::set_controller(MONO_Controller *const controller_, ModelBase *model_)
{
    _controller = controller_;
    _model = model_;
}
