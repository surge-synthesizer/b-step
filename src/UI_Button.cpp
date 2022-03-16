/*
  ==============================================================================

    UiButton.cpp
    Created: 28 May 2014 9:47:28am
    Author:  monotomy

  ==============================================================================
*/

#include "_H_UiElements.h"
#include "Controller.h"
#include "AppStyles.h"

UiButton::UiButton():
    is_mouse_down(false),
    is_simple_drag_valid(false),
    is_multi_drag_valid(false),
    was_dragging(false),
    drop_source(nullptr),
    _foreground_color_1( 0x00000000 ),
    _foreground_color_2( 0x00000000 ),
    _outline_color( 0x00000000 )
{
    setRepaintsOnMouseActivity(false);
    //setBufferedToImage(false);
    setPaintingIsUnclipped(true);
}
#include INCLUDE_USER_DEBUG
void UiButton::mouseDown( const MouseEvent& e_ )
{
    USER_OUT( LOG_BUTTON_EVENTS, "mouseDown @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

    bool escape = false;
    if( _controller )
        escape = _controller->on_pre_mouse_down_escape( e_ );

    if( escape )
        return;

    is_mouse_down = true;

    if( e_.mods == ModifierKeys::rightButtonModifier && GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_AT_RIGHT_MOUSE )
    {
        if( GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE )
            timerCallback();
    }
    else
    {
        if( ! GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_AT_RIGHT_MOUSE )
            startTimer( GLOBAL_VALUE_HOLDER::getInstance()->LONG_MOUSE_DOWN_INTERVAL );

        if( e_.mods == ModifierKeys::leftButtonModifier && GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_AT_RIGHT_MOUSE )
            //    if( _controller )
            //        if( _controller->are_you_simple_dragable() )
            is_simple_drag_valid = true;
    }

    USER_OUT( LOG_BUTTON_EVENTS, "mouseDownFuEnd @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

    repaint(0,0,getWidth(),getHeight());
}

void UiButton::timerCallback( )
{
    stopTimer();
    if( ! is_simple_drag_valid )
    {
        if( _controller )
        {
            _controller->on_long_mouse_down();
            USER_OUT( LOG_BUTTON_EVENTS, "onLongMouseDown @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );
        }

        is_multi_drag_valid = true;
    }
    else
        USER_OUT( LOG_BUTTON_EVENTS, "isSimpleDragValid @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );
}

void UiButton::mouseUp(const MouseEvent& e_)
{
    USER_OUT( LOG_BUTTON_EVENTS, "mouseUp @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

    is_simple_drag_valid = false;
    is_multi_drag_valid = false;

    if( _controller )
        if( is_mouse_down )
        {
            is_mouse_down = false;

            _controller->on_clicked(!was_dragging);
            _controller->on_mouse_up(e_);
            stopTimer();

            //refresh_image_cache(); // TODO
            repaint(0,0,getWidth(),getHeight());
        }

    was_dragging = false;

    USER_OUT( LOG_BUTTON_EVENTS, "mouseUpFuEnd @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

}

void UiButton::mouseMove(const MouseEvent& e_)
{
    // USER_OUT( LOG_BUTTON_EVENTS, "mouseMove @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"" );

    if( _controller )
        _controller->on_mouse_move( e_ );
}

void UiButton::mouseEnter(const MouseEvent& e_)
{
    //USER_OUT( LOG_BUTTON_EVENTS, "mouseEnter @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"" );

    if( _controller )
        _controller->on_mouse_enter( e_ );
}

void UiButton::mouseExit(const MouseEvent& e_)
{
    //USER_OUT( LOG_BUTTON_EVENTS, "mouseEnter @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"" );

    if( _controller )
        _controller->on_mouse_exit( e_ );
}

void UiButton::mouseDrag(const MouseEvent& e_)
{
    USER_OUT( LOG_BUTTON_EVENTS, "mouseDrag @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

    if( _controller )
    {
        //_controller->on_mouse_drag( e_ );

        if( isTimerRunning() )
        {
            if( e_.getDistanceFromDragStartX() > this->getHeight() * GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_SENSITIVITY
                    || e_.getDistanceFromDragStartY() > this->getHeight() * GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_SENSITIVITY
                    || e_.getDistanceFromDragStartX() < (this->getHeight() * GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_SENSITIVITY)*-1
                    || e_.getDistanceFromDragStartY() < (this->getHeight() * GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_SENSITIVITY)*-1 )
            {
                USER_OUT( LOG_BUTTON_EVENTS, "enableSimpleDrag @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

                is_simple_drag_valid = true;
                stopTimer();
                return;
            }
        }

        if( ! was_dragging )
        {
            if( is_simple_drag_valid )
            {
                if( _controller->are_you_simple_dragable() )
                {
                    if( e_.getDistanceFromDragStartX() > this->getHeight() * GLOBAL_VALUE_HOLDER::getInstance()->SIMPLEDRAG_SENSITIVITY
                            || e_.getDistanceFromDragStartY() > this->getHeight() * GLOBAL_VALUE_HOLDER::getInstance()->SIMPLEDRAG_SENSITIVITY
                            || e_.getDistanceFromDragStartX() < (this->getHeight() * GLOBAL_VALUE_HOLDER::getInstance()->SIMPLEDRAG_SENSITIVITY)*-1
                            || e_.getDistanceFromDragStartY() < (this->getHeight() * GLOBAL_VALUE_HOLDER::getInstance()->SIMPLEDRAG_SENSITIVITY)*-1 )
                    {
                        USER_OUT( LOG_BUTTON_EVENTS, "startDrag @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

                        is_simple_drag_valid = false;
                        is_multi_drag_valid = false;
                        was_dragging = true;

                        Image img( Image::RGB, 0, 0, false );
                        drop_source = _controller->get_dragNdrop_source();
                        startDragging ( _controller->get_dragNdrop_ident(), drop_source, _model->get_drag_image(img), true );
                    }
                }
            }
            else if( is_multi_drag_valid )
            {
                if( _controller->should_start_multi_drag() )
                {
                    USER_OUT( LOG_BUTTON_EVENTS, "startMultiD @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

                    is_simple_drag_valid = false;
                    is_multi_drag_valid = false;
                    was_dragging = true;

                    Image img( Image::RGB, 0, 0, false );
                    if( _controller->are_you_simple_dragable() ) {
                        drop_source = _controller->get_dragNdrop_source();
                        startDragging ( _controller->get_multi_dragNdrop_ident(), drop_source, _model->get_drag_image(img), true );
                    }
                    else
                        startDragging ( _controller->get_multi_dragNdrop_ident(), this, _model->get_drag_image(img), true );


                }
            }
        }
    }

    USER_OUT( LOG_BUTTON_EVENTS, "mouseDragFuEnd @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

}

void UiButton::mouseDoubleClick(const MouseEvent& e_)
{
    USER_OUT( LOG_BUTTON_EVENTS, "mouseDoubleClick @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

    //if( _controller )
    //   _controller->on_mouse_double_click( e_ );


    USER_OUT( LOG_BUTTON_EVENTS, "mouseDoubleClickFuEnd @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );
}

void UiButton::mouseWheelMove(const MouseEvent& e_, const MouseWheelDetails& wheel_)
{
    USER_OUT( LOG_BUTTON_EVENTS, "mouseWheelMove @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

    if( _controller )
        _controller->on_mouse_wheel_move( e_, wheel_ );

    USER_OUT( LOG_BUTTON_EVENTS, "mouseWheelMoveFuEnd @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );
}

bool UiButton::isInterestedInDragSource(const DragAndDropTarget::SourceDetails& sd_)
{
    if( _controller )
        return _controller->is_interested_in_drag_source( sd_ );

    return false;
}

void UiButton::itemDropped(const DragAndDropTarget::SourceDetails& sd_)
{
    USER_OUT( LOG_BUTTON_EVENTS, "itemDropped @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

    if( _controller )
    {
        _controller->item_dropped( sd_ );
    }
    USER_OUT( LOG_BUTTON_EVENTS, "itemDroppedFuEnd @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );
}

void UiButton::dragOperationEnded(const DragAndDropTarget::SourceDetails &d) {
    drop_source = nullptr;
    DragAndDropContainer::dragOperationEnded(d);
}

void UiButton::triggerClick() {
    USER_OUT( LOG_BUTTON_EVENTS, "clicked @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

    if( _controller )
        _controller->on_clicked();
}

void UiButton::clicked()
{
    USER_OUT( LOG_BUTTON_EVENTS, "clicked @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );

    if( _controller )
        _controller->on_clicked();
    USER_OUT( LOG_BUTTON_EVENTS, "clickedFuEnd @@@ ", _controller ? _controller->get_controller_name() : "unknown", _controller ? (_controller->get_parameter() ? _controller->get_parameter()->get_param_unique_ident() :"" ) :"", "" );
}

void UiButton::resized(int w_, int h_)
{
    this->setBounds( 0, 0, w_, h_ );
}

bool UiButton::refresh_foreground()
{
    if( ! _model || ! _controller)
        return false;

    bool should_be_repainted = false;

    uint32 new_foreground_color = _controller->get_current_color_low();
    uint32 new_foreground_color_1 = is_mouse_down ? Colour(new_foreground_color).darker (0.2f).getARGB() : Colour(new_foreground_color).brighter (0.1f).getARGB();
    uint32 new_foreground_color_2 = is_mouse_down ? Colour(new_foreground_color).brighter (0.1f).getARGB() : Colour (new_foreground_color).darker (0.1f).getARGB();
    if( _foreground_color_1 != new_foreground_color_1 )
    {
        _foreground_color_1 = new_foreground_color_1;
        _foreground_color_2 = new_foreground_color_2;
        should_be_repainted = true;
    }

    uint32 new_outline_color = _model->_style->get_element_border_color();
    if( _outline_color != new_outline_color )
    {
        _outline_color = new_outline_color;
        should_be_repainted = true;
    }

    String new_value_as_label = HAS_NO_TEXT_VALUE;
    _controller->get_label_text( new_value_as_label );
    if( _text != new_value_as_label )
    {
        _text = new_value_as_label;
        should_be_repainted = true;
    }

    return should_be_repainted;
}

void UiButton::cache_paint( Graphics& g, uint32 background_colour_ )
{
    // App Style Butto Paint
    if( ! _controller )
        return;

    if( ! _model->isVisible() )
        return;



    // PAINT THE BUTTON
    if( _model )
    {
        int width = getWidth();
        int height = getHeight();
        float center_offset_x = 0;
        float center_offset_y = 0;

        if( _controller->is_rect_style_else_fill_area() )
        {
            if( width > height )
            {
                center_offset_x =  float(width-height)/2;
                width = height;
            }
            else
            {
                center_offset_y = float(height-width)/2;
                height = width;
            }
        }

        if( _model->get_style() )
        {
            g.fillAll(Colour(background_colour_));

            float radius = 6.f*(1.f/40*width);
            float line = 1.5*(1.f/40*width);

            // BUTON ITSELFT
            g.setGradientFill (ColourGradient (Colour(_foreground_color_1), 0.0f, 0.0f, Colour(_foreground_color_2), 0.0f, height, false));
            g.fillRoundedRectangle (1+center_offset_x,
                                    1+center_offset_y,
                                    width-2,
                                    height-2,
                                    radius);

            // OUTLINE
            g.setColour (Colour(_outline_color));
            g.drawRoundedRectangle (1+center_offset_x,
                                    1+center_offset_y,
                                    width-2,
                                    height-2,
                                    radius, line);
        }

        // LABEL IF EXIST
        if( _text != HAS_NO_TEXT_VALUE )
        {
            AppStyle* style = _controller->get_custom_label_style();
            if( ! style )
                style = _model->get_style();

            if( style )
            {
                // TODO hack for higher labels
                if( _controller->is_rect_style_else_fill_area() )
                    AppStyle::paint_outline_label( g, *this, _text, style, Justification::centred, 0.1,0.1, 0.8, 0.8 );
                else
                    AppStyle::paint_outline_label( g, *this, _text, style, Justification::centred, 0.1,0.1, 0.8, 0.8, false );
            }
        }

        // IMAGE IF EXIST
        {
            const Image*const img = _controller->get_current_image();
            if( img )
            {
                g.drawImageWithin (*img,
                                   1+center_offset_x,
                                   1+center_offset_y,
                                   width-2,
                                   height-2,
                                   RectanglePlacement::fillDestination,
                                   true);
            }
            else
            {
                const Drawable* drawable = _controller->get_current_drawable();
                if( drawable )
                {
                    float inside_width = 0.5*width;
                    float inside_height = 0.5*height;
                    float inside_center_offset_x = 0.5*getWidth() - 0.5*inside_width;
                    float inside_center_offset_y = 0.5*getHeight() - 0.5*inside_height;

                    drawable->drawWithin (g,
                                          Rectangle<float>( inside_center_offset_x,
                                                            inside_center_offset_y,
                                                            inside_width ,
                                                            inside_height ),
                                          RectanglePlacement::centred,
                                          1);
                }
            }
        }
    }
}

Component* UiButton::get_top_level_component()
{
    return this;
}

void* UiButton::get_top_level_impl()
{
    return this;
}
