#ifndef _POWERKEYEVENT_H_
#define _POWERKEYEVENT_H_

#include "InputOperation.hpp"

#include <memory>
using namespace std;

class PowerKeyEvent{

public :
    PowerKeyEvent( ) {} 

    shared_ptr<InputOperation> generateOperation( int fd ) ; 
};

shared_ptr<InputOperation> PowerKeyEvent::generateOperation( int fd )
{
    shared_ptr<InputOperation> pOperation( new InputOperation( fd) );

    pOperation->addInputEvent( InputEvent( EV_KEY , KEY_POWER , 1 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_REPORT , 0 ));
    pOperation->addInputEvent( InputEvent( EV_KEY , KEY_POWER , 0 ));
    pOperation->addInputEvent( InputEvent( EV_SYN , SYN_REPORT , 0 ));

    return pOperation ; 

}

#endif /* _POWERKEYEVENT_H_ */
