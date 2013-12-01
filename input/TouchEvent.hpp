
#ifndef _TOUCHEVENT_H_
#define _TOUCHEVENT_H_

#include "Position.hpp"
#include "InputOperation.hpp"

#include <memory>

#include <linux/input.h>

using namespace std;


class TouchEvent
{
private :
    Position mPos ;
    
public:

    TouchEvent( Position position ) :
        mPos( position ) {}

    // Generate the InputOperation
    shared_ptr<InputOperation> generateOperation ( int fd ) ; 
};

shared_ptr<InputOperation> TouchEvent::generateOperation( int fd )
{
    shared_ptr<InputOperation> pOperation( new InputOperation( fd) );

    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_POSITION_X , mPos.getPositionX() ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_POSITION_Y , mPos.getPositionY() ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_TRACKING_ID , 0 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_TOUCH_MAJOR , 0 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_WIDTH_MAJOR , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_MT_REPORT , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_REPORT , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_MT_REPORT , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_REPORT , 0 ));

    return pOperation ; 
}

#endif /* _TOUCHEVENT_H_ */
