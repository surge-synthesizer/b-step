
#include "ControllerMidiLearn.h"

#include "UiMainWindow.h"
#include "MIDILearn.h"

void ControllerMIDILearn::refresh_ui()
{
    MIDIInToControllerMap& map = _app_instance_store->midi_in_map;
    MONO_Controller*const learning_controller = map.get_learning_controller();
    if( learning_controller )
    {
        const Component*const learning_view = learning_controller->get_ui_peer();
        if( learning_view )
        {
            int cc_type = map.get_last_learned_cc_type(learning_controller);

            Rectangle< int > pos;
            pos = learning_view->localAreaToGlobal(learning_view->getLocalBounds());
            pos.setX( pos.getX() - _app_instance_store->editor->getScreenX() );
            pos.setY( pos.getY() - _app_instance_store->editor->getScreenY() );

            int bigger_width = pos.getWidth() * 1.5;
            int bigger_height = pos.getHeight() * 1.5;

            pos.setX( pos.getX() - (bigger_width-pos.getWidth())/2 );
            pos.setY( pos.getY() - (bigger_height-pos.getHeight())/2 );
            pos.setWidth( bigger_width );
            pos.setHeight( bigger_height );

            _midi_learn_focus->setVisible( true );
            _midi_cc_value->setVisible( true );

            _midi_learn_focus->setBounds ( pos  );
            _midi_cc_value->setBounds ( pos );

            _midi_cc_value->setText( String(cc_type), dontSendNotification );
            _midi_learn_focus->setToggleState(true, dontSendNotification);
        }
    }
    else
    {
        _midi_learn_focus->setVisible( false );
        _midi_cc_value->setVisible( false );
    }
}
ControllerMIDILearn::~ControllerMIDILearn() {}

ControllerMIDILearn::ControllerMIDILearn
(
    AppInstanceStore*const app_instance_store_,
    ImageButton*const midi_learn_focus_,
    Label*const midi_cc_value_
)
    : _app_instance_store( app_instance_store_ ),
      _midi_learn_focus( midi_learn_focus_ ),
      _midi_cc_value( midi_cc_value_ )
{
    _midi_learn_focus->setToggleState(false,dontSendNotification);

    Drawable*drawable = Drawable::createFromImageData (BinaryData::select_svg, BinaryData::select_svgSize).release();
    Image image = drawable->createComponentSnapshot( drawable->getBounds() );
    _midi_learn_focus->setImages(true,true,true,
                                 image,1,Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR),
                                 image,1,Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR),
                                 image,1,Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    _midi_learn_focus->toFront( false );
    _midi_cc_value->toFront( false );

    if( drawable )
        delete drawable;
}

