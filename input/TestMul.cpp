#include <iostream>
#include <stdlib.h>

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
	if( argc != 2 )
	{
		fprintf( stderr , "Usage : TestMul  [sleeptime] \n" );
		return -1 ;
	}

    int screenFd = openInputDevice( 0 ) ;

    if ( screenFd < 0   )
    {
        return -1 ; 
    }
	
    int sleepTime = 3 ;

	sleepTime == atoi( argv[1] );

	printf( "[Debug]  sleep time is %d \n" ,  sleepTime );
#if 0
    int sleepTime = 1 ;
    int count = 1 ; 
   
    printf("Input Enter Count : ");
    scanf( "%d" , &count );
    printf("Input Sleep Time : " );
    scanf( "%d" , &sleepTime );
#endif 

   
    TouchEvent touchEvent1( Position( 62 , 88 ));
    shared_ptr<InputOperation> op1 = touchEvent1.generateOperation( screenFd ) ;

    TouchEvent touchEvent2( Position( 154 , 88 ));
    shared_ptr<InputOperation> op2 = touchEvent2.generateOperation( screenFd ) ;

    TouchEvent touchEvent3( Position( 86 , 172 ));
    shared_ptr<InputOperation> op3 = touchEvent3.generateOperation( screenFd ) ;

    TouchEvent touchEvent4( Position( 176 , 172 ));
    shared_ptr<InputOperation> op4 = touchEvent4.generateOperation( screenFd ) ;

    
    MoveEvent moveRightEvent( Position( 92 , 150  ) , Position( 195 , 150 ));
    shared_ptr<InputOperation> moveRightOp = moveRightEvent.generateOperation( screenFd ) ;

    MoveEvent moveLeftEvent( Position( 180 , 120  ) , Position( 44 , 120 ));
    shared_ptr<InputOperation> moveLeftOp = moveLeftEvent.generateOperation( screenFd ) ;

    // for (int i = 0; i < count; ++i)
	while( 1  )
    {

        for( int j = 0 ; j < 3 ;  j ++ )
        {
            
            op1->execute() ; 
            sleep( sleepTime );
            moveRightOp->execute() ; 
            sleep( sleepTime );

            
            op2->execute() ; 
            sleep( sleepTime );
            moveRightOp->execute() ; 
            sleep( sleepTime );


            op3->execute() ; 
            sleep( sleepTime );
            moveRightOp->execute() ; 
            sleep( sleepTime );

            op4->execute() ; 
            sleep( sleepTime );
            moveRightOp->execute() ; 
            sleep( sleepTime );

            moveLeftOp->execute() ;
            sleep(sleepTime );
        }

        moveRightOp->execute() ;
        sleep( 2 ) ;
        moveRightOp->execute( ) ;
        sleep( 2 ) ;
        
    }

    
    close( screenFd );
    return 0;
}
