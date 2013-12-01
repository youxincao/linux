#include <iostream>

#include "InputEvent.hpp"
#include "InputOperation.hpp"

using namespace std;

int openInputDevice( int num )
{
    char name[64];
    int ret = 0 ;
    
    sprintf( name , "/dev/input/event%d" , num );

    ret = open( name , O_RDWR , 0 );
    if ( ret < 0)
    {
        cerr << "Open " << name << " failed " << endl ;
        return -1 ; 
    }
    return ret ;
}

int main(int argc, char *argv[])
{
    int fd = openInputDevice( 0 ) ;

    if ( fd < 0   )
    {
        return -1 ; 
    }
    
    InputOperation operation( fd );
    
    operation.addInputEvent( InputEvent( 0x3 , 0x35 , 0x44 ) ) ;
    operation.addInputEvent( InputEvent( 0x3 , 0x36 , 0x3b ) ) ;
    operation.addInputEvent( InputEvent( 0x3 , 0x39 , 0x0  ) ) ;
    operation.addInputEvent( InputEvent( 0x3 , 0x30 , 0x0  ) ) ;
    operation.addInputEvent( InputEvent( 0x3 , 0x32 , 0x0  ) ) ;
    operation.addInputEvent( InputEvent( 0x0 , 0x2  , 0x0  ) ) ;
    operation.addInputEvent( InputEvent( 0x0 , 0x0  , 0x0  ) ) ;
    operation.addInputEvent( InputEvent( 0x0 , 0x2  , 0x0  ) ) ;
    operation.addInputEvent( InputEvent( 0x0 , 0x0  , 0x0  ) ) ;
    operation.execute() ;
   
    return 0;
}
