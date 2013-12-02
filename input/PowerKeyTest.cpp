#include <iostream>

#include "InputEvent.hpp"
#include "InputOperation.hpp"
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

    int keyFd = openInputDevice( 1 );
    if ( keyFd < 0   )
    {
        return -1 ; 
    }

    int count ;
    int sleepTime ; 

    printf("Input Press Count :") ;
    scanf( "%d" , &count );
    printf("Input Sleep Time :") ;
    scanf("%d" , &sleepTime  ) ;
    
    PowerKeyEvent powerEvent;
    shared_ptr<InputOperation> powerOp = powerEvent.generateOperation( keyFd ) ;

    for (int i = 0; i < count ; ++i)
    {
        printf("Press %d count \n" , i ) ;
        powerOp->execute() ;
        sleep( sleepTime );
    }
   
    close( keyFd );
    return 0;
}

