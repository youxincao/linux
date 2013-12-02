#ifndef _MOVEEVENT_H_
#define _MOVEEVENT_H_

#include "Position.hpp"
#include "InputOperation.hpp"

#include <memory>

#include <linux/input.h>
using namespace std;

class MoveEvent
{
private :
    Position mBegin ;
    Position mEnd ; 
public:
    MoveEvent( Position begin , Position end ):
        mBegin( begin ) , mEnd ( end ) { }

    shared_ptr<InputOperation> generateOperation( int fd ) ; 
};

shared_ptr<InputOperation> MoveEvent::generateOperation( int fd )
{
    shared_ptr<InputOperation> pOperation( new InputOperation ( fd ) ) ;

    int middle_x = (mBegin.getPositionX() + mEnd.getPositionX() ) / 2 ;
    int middle_y = (mBegin.getPositionY() + mEnd.getPositionY() ) / 2 ;


    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_POSITION_X , mBegin.getPositionX() ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_POSITION_Y , mBegin.getPositionY() ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_TRACKING_ID , 0 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_TOUCH_MAJOR , 0 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_WIDTH_MAJOR , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_MT_REPORT , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_REPORT , 0 ));

    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_POSITION_X , ( mBegin.getPositionX() + middle_x ) / 2 ) ) ;
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_POSITION_Y , ( mBegin.getPositionY() + middle_y ) / 2 ) ) ;
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_TRACKING_ID , 0 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_TOUCH_MAJOR , 0 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_WIDTH_MAJOR , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_MT_REPORT , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_REPORT , 0 ));

    

    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_POSITION_X , middle_x ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_POSITION_Y , middle_y ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_TRACKING_ID , 0 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_TOUCH_MAJOR , 0 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_WIDTH_MAJOR , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_MT_REPORT , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_REPORT , 0 ));

   
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_POSITION_X , ( mEnd.getPositionX() + middle_x ) / 2 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_POSITION_Y , ( mEnd.getPositionY() + middle_y ) / 2 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_TRACKING_ID , 0 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_TOUCH_MAJOR , 0 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_WIDTH_MAJOR , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_MT_REPORT , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_REPORT , 0 ));

    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_POSITION_X , mEnd.getPositionX() ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_POSITION_Y , mEnd.getPositionY() ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_TRACKING_ID , 0 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_TOUCH_MAJOR , 0 ));
    pOperation->addInputEvent( InputEvent( EV_ABS , ABS_MT_WIDTH_MAJOR , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_MT_REPORT , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_REPORT , 0 ));

    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_MT_REPORT , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_REPORT , 0 ));
    
    return pOperation ;
    
}

#endif /* _MOVEEVENT_H_ */
