#include <iostream>

#include "InputEvent.hpp"
#include "InputOperation.hpp"
#include "TouchEvent.hpp"
#include "MoveEvent.hpp"
#include "PowerKeyEvent.hpp"

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
    int screenFd = openInputDevice( 0 ) ;

    if ( screenFd < 0   )
    {
        return -1 ; 
    }

    int keyFd = openInputDevice( 1 );
    if ( keyFd < 0   )
    {
        return -1 ; 
    }
    

    TouchEvent touchEvent( Position( 62 , 88 ));
    shared_ptr<InputOperation> op = touchEvent.generateOperation( screenFd ) ;
    op->execute() ;

    sleep( 1);
    
    MoveEvent moveEvent( Position( 44 , 150  ) , Position( 180 , 150 ));
    shared_ptr<InputOperation> moveOp = moveEvent.generateOperation( screenFd ) ;
    moveOp->execute() ; 

    PowerKeyEvent powerEvent;
    shared_ptr<InputOperation> powerOp = powerEvent.generateOperation( keyFd ) ;
    powerOp->execute() ;
    
    close( screenFd );
    return 0;
}
