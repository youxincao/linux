#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdlib.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

// The socket 
static int s ;
static int gPacketSize ;
static int gPacketCount ;
static int gSleepTime ; 
static char* gSendBuf ;
static char* gRecvBuf ; 

#define MAX_PACKET_SIZE 725

int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 };
    int  status;
    char dest[18] = "00:1A:7D:DA:71:06";

    if( argc != 2 )
    {
        fprintf( stderr , "Please give us a bluetooth address ! \n") ;
        return -1 ; 
    }

    sprintf( dest , "%s" , argv[1]);
    
    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	int sndbuf = 70 * 1024 ;
	if( setsockopt( s , SOL_SOCKET, SO_SNDBUF , &sndbuf , sizeof(sndbuf) ) ) 
	{
		fprintf( stderr , "SetSockOpt(SO_SNDBUF) failed \n" );
		return -2 ; 
	}

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 11;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
	char buf[512] = { 0  };

    // get the test parameter
    printf("Packet Size : " );
    scanf("%d" , &gPacketSize );
    printf("Packet Count :");
    scanf("%d" , &gPacketCount );
    printf("Sleep time : ");
    scanf("%d" , &gSleepTime );

    if( gPacketSize > MAX_PACKET_SIZE || gPacketSize <= 0 )
        gPacketSize = MAX_PACKET_SIZE ;

    // malloc the buffer 
    gSendBuf = ( char * )malloc( gPacketSize * sizeof( char )) ;
    if (gSendBuf == NULL )
    {
        fprintf( stderr , "Malloc the send buffer failed \n");
        return -1 ; 
    }

    gRecvBuf = ( char * )malloc( gPacketSize * sizeof( char )) ;
    if ( gRecvBuf == NULL )
    {
        fprintf( stderr , "Malloc the send buffer failed \n");
        return -1 ; 
    }

    // Initilie the send buf
    for ( int i = 0  ;  i < gPacketSize ; ++i)
    {
        gSendBuf[ i  ] = ( char ) i % 256 ; 
    }

    int err_count = 0 ; 
    // send a message
    if( status == 0 ) {
       
		for (int i = 0; i < gPacketCount; ++i)
        {
            for ( int i = 0  ;  i < gPacketSize ; ++i)
            {
                gSendBuf[ i  ] = ( char ) i % 256 ; 
            }
            status = write(s, gSendBuf ,  gPacketSize );
            int redLen = read( s , gRecvBuf  , gPacketSize );            
			sleep( gSleepTime );

            int ret = memcmp( gSendBuf , gRecvBuf , gPacketSize ) ;
            if( ret != 0 )
            {
                printf("%d FALSE\n" , i  ) ;
                err_count ++ ; 
            }
            else
            {
                printf("%d OK \n" , i );
            }
        }
    }

    if( status < 0 ) perror("uh oh");

    printf("Send %d Packets(size=%d) , err %d \n" ,
           gPacketCount , gPacketSize , err_count );
    
    close(s);
    return 0;
}
