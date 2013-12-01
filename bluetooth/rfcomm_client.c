#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>



int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = "00:1A:7D:DA:71:06";

    if( argc != 2 )
    {
        fprintf( stderr , "Please give us a bluetooth address !") ;
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

    // send a message
    if( status == 0 ) {
		while ( 1  )
		{
			printf("[rfcomm_clint] : send Hello \n" );
    	    status = write(s, "hello!", 6);
			read( s , buf  , 512  );
			printf("[rfcomm_clint] : recv %s \n" , buf ) ;
			sleep( 2  );
		}		
    }

    if( status < 0 ) perror("uh oh");

    close(s);
    return 0;
}
