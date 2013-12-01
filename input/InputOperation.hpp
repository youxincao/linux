#ifndef _INPUTOPERATION_H_
#define _INPUTOPERATION_H_

#include "InputEvent.hpp"
#include <vector>
#include <cstdio>
#include <fcntl.h>
using namespace std;

class InputOperation
{
private :
    vector<InputEvent> mEvents ;
    int mFd  ; 
    
public:
    InputOperation( int fd ) :
        mFd( fd )  { }
    virtual ~InputOperation()
        {
            if ( mFd != -1 )
            {
                close ( mFd  ) ;
                mFd = -1 ; 
            }
        }

    //open the input device 
    void addInputEvent( InputEvent ev )
    {
        mEvents.push_back( ev ) ;
    }
    void execute( );
};

void InputOperation::execute()
{
    vector<InputEvent>::iterator iter ;
    for( iter = mEvents.begin() ; iter != mEvents.end() ; iter ++  )
    {
        InputEvent event = *iter ;
        struct input_event ev ;
        event.format( &ev );
        write( mFd , (void *) &ev , sizeof( struct input_event ) ) ; 
    }
}

#endif /* _INPUTOPERATION_H_ */
