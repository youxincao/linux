#include "iostream"

#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
using namespace std;

void usage()
{
    cerr << "Usage : sendevent devnum type code value " << endl; 
}

typedef struct _event_data {
	int type ;
	int code ; 
	int value ; 
} event_data ; 

int main(int argc, char *argv[])
{
    if( argc != 5 )
    {
        usage( );
        return -1 ; 
    }

    int dev_num ;
    char dev_path [64];
	event_data *input_data = NULL ;  
	int data_size = 0 ;

    sscanf( argv[1] , "%d" , &dev_num );
	if( (strlen( argv[2] ) == 2) && (strncmp( argv[2] , "-f" , 2 ) == 0 ) )
	{
			
	}
	else 
	{
		
		data_size = 1 ; 
		input_data = ( event_data * )malloc( sizeof( event_data ) );

		sscanf( argv[2] , "%d" , &(input_data->type) ) ;
		sscanf( argv[3] , "%d" , &(input_data->code) ) ;
		sscanf( argv[4] , "%d" , &(input_data->value) ) ;
	}

    sprintf( dev_path , "/dev/input/event%d" , dev_num ) ;
    
    int fd = open( dev_path , O_WRONLY , 0 ) ;
    if( fd < 0 )
    {
        cerr << "Open " << dev_path << " failed ! " << endl ;
        return -1 ; 
    }
    struct input_event event ;
   	
	for( int i = 0 ; i < data_size ; i ++  )
	{
		event_data data = input_data[i] ; 

	    event.type = data.type ;
	    event.code = data.code ;
	    event.value = data.value ;

		printf( "[Test] Type : %d , code %d , value %d \n" , 
				data.type , data.code , data.value ); 

		int ret = write( fd ,  (void *)&event , sizeof ( struct input_event ));
		if( ret < sizeof( struct input_event ) )
		{
			fprintf( stderr , "Write to device failed \n" );
			return -1 ;
		}
	
	}
    
    close( fd );
    return 0;
}
