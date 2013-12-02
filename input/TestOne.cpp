#include <iostream>

#include "InputEvent.hpp"
#include "InputOperation.hpp"
#include "TouchEvent.hpp"
#include "MoveEvent.hpp"

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

    int index = 1 ;
    int sleepTime = 1 ;
    int count = 1 ; 
    int pos_x = 62 ;
    int pos_y = 88 ;

    printf("Input Program Index : ");
    scanf( "%d" , &index );
    printf("Input Enter Count : ");
    scanf( "%d" , &count );
    printf("Input Sleep Time : " );
    scanf( "%d" , &sleepTime );

    switch( index )
    {
    case 1 :
        pos_x = 62 ;
        pos_y = 88 ; 
        break ;
        
    case 2 :
        pos_x = 154 ;
        pos_y = 88 ; 
        break ;

    case 3 :
        pos_x = 86 ;
        pos_y = 172 ; 
        break ;

    case 4 :
        pos_x = 176 ;
        pos_y = 172 ; 
        break ;
    
    default :
        break ; 
    }
    

    TouchEvent touchEvent( Position( pos_x , pos_y ));
    shared_ptr<InputOperation> op = touchEvent.generateOperation( screenFd ) ;
    
    
    MoveEvent moveEvent( Position( 44 , 150  ) , Position( 180 , 150 ));
    shared_ptr<InputOperation> moveOp = moveEvent.generateOperation( screenFd ) ;
    
    for (int i = 0; i < count; ++i)
    {
        op->execute() ; 
        printf("==> Enter %d times \n" , i ) ;
        sleep( sleepTime );
        moveOp->execute() ; 
        printf("<== Quit %d times \n" , i ) ;
        sleep( sleepTime );
    }
    
    close( screenFd );
    return 0;
}
