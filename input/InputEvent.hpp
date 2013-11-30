#ifndef _INPUTEVENT_H_
#define _INPUTEVENT_H_

#include <linux/input.h>

class InputEvent {
    
private :
    int mType ; 
    int mCode ;
    int mValue ;

public :
    InputEvent( int type , int code , int value ) :
        mType( type ) , mCode( code ) , mValue( value ) { }

    // Member function
    int getInputEventType() { return mType ; }
    int getInputEventCode() { return mCode ; }
    int getInputEventValue() { return mValue ; }

    void format( struct input_event * );

    static const InputEvent SYNC_EVENT ;

};

// static member
const InputEvent InputEvent::SYNC_EVENT = InputEvent( 0x0 , 0x0 , 0x0 );

void InputEvent::format( struct input_event *event )
{
    event->type = mType ;
    event->code = mCode ;
    event->value = mValue ; 
}

#endif /* _INPUTEVENT_H_ */
