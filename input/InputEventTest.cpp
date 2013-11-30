#include <iostream>

#include "InputEvent.hpp"
#include "InputOperation.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    InputOperation operation( 0 );
    if(operation.openDevice() )
    {
        operation.addInputEvent( InputEvent( 0x3 , 0x35 , 0x44 ) ) ;
        operation.addInputEvent( InputEvent( 0x3 , 0x36 , 0x3b ) ) ;
        operation.addInputEvent( InputEvent( 0x3 , 0x39 , 0x0  ) ) ;
        operation.addInputEvent( InputEvent( 0x3 , 0x30 , 0x0  ) ) ;
        operation.addInputEvent( InputEvent( 0x3 , 0x32 , 0x0  ) ) ;
        operation.addInputEvent( InputEvent( 0x0 , 0x2  , 0x0  ) ) ;
        operation.addInputEvent( InputEvent( 0x0 , 0x0  , 0x0  ) ) ;
        operation.addInputEvent( InputEvent( 0x0 , 0x2  , 0x0  ) ) ;
        operation.execute() ;
    }
 

    
    return 0;
}
