#include "iostream"

#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

using namespace std;

void usage()
{
    cerr << "Usage : sendevent devnum type code value " << endl; 
}

class FileCloser
{
	private :
		FILE *mFile ; 

	public :
		FileCloser( FILE *file  ) :
			mFile( file  ) {  }
		~FileCloser() { fclose( mFile ); }
};

typedef struct _event_data {
	int type ;
	int code ; 
	int value ; 
} event_data ; 

int main(int argc, char *argv[])
{
    if( argc < 2 )
    {
        usage( );
        return -1 ; 
    }

    int dev_num ;
    char dev_path [64];
	event_data *input_data = NULL ;  
	int data_size = 0 ;

    sscanf( argv[1] , "%d" , &dev_num );
	if( (strlen( argv[2] ) == 2)  && (strncmp( argv[2] , "-f" , 2 ) == 0 ) )
	{
		if( argc < 4  )
		{
			fprintf( stderr , "Error : You should specific a file after -f \n" ) ;
			return -1 ; 
		}
		FILE *file_p = fopen( argv[3] ,  "r" ) ; 
		if( file_p == NULL )
		{
			fprintf( stderr , "Error : Open %s failed : %s \n"  , 
					argv[3] , strerror ( errno ) ) ;
			return -1 ; 
		}
	
		FileCloser fileCloser( file_p );

		fscanf(  file_p ,  "%d\n" , &data_size );
		if( data_size <= 0  )
		{
			fprintf( stderr , "Error : The data size shoud greater than 0 \n" ) ;
			return -1 ; 
		}

		input_data = ( event_data * )malloc( sizeof( event_data ) * data_size );
		for( int i = 0 ; i < data_size ; i ++  )
		{
			event_data *data = &input_data[i];
			fscanf( file_p , "%d %d %d\n" ,  &data->type , &data->code , &data->value ) ;
//			printf( "[Test] data %p Type : %d , code %d , value %d \n" , 
//				&data , data->type , data->code , data->value ); 
		}
	}
	else 
	{
		if( argc < 5 )
		{
			fprintf( stderr , "Error : You shoud specific the code type and value \n" ) ;
			return -1 ; 
		}
		
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
   	
	printf("\n\n");

	for( int i = 0 ; i < data_size ; i ++  )
	{
		event_data data = input_data[i] ; 

	    event.type = data.type ;
	    event.code = data.code ;
	    event.value = data.value ;

//		printf( "[Test] %p Type : %d , code %d , value %d \n" , 
//				&data , data.type , data.code , data.value ); 
//
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
