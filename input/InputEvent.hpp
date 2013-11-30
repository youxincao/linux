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

    static const InputEvent SYNC_EVENT ; 
};

const InputEvent InputEvent::SYNC_EVENT = InputEvent( 0x0 , 0x2 , 0x0 );

#endif /* _INPUTEVENT_H_ */
