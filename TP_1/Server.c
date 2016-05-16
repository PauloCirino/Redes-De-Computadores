//
//  Server.c
//  Tp_01
//
//  Created by Paulo Cirino on 06/05/16.
//  Copyright © 2016 Paulo Cirino. All rights reserved.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

#include "ranking.h"

#define MESSEGE_SIZE 100
#define MAX_CONNECTION_NUM 10
#define TRUE 1

int main(int argc, char ** argv){
    
    //Checks if arguments are valid
    if(argc != 2)
    {
        printf("Wrong Number of Arguments. \n");
        printf("Correct usde would be \n ./Server [Port]\n");
        return 300;
    }

    //Checks if port is a positive value
    int Port = atoi(argv[1]);
    if(Port <= 0)
    {
      printf("Invalid Port Error!!!! \n\n");
      return 127;
    }

    /**************** Initializes and Sets Variables and Structures ****************/

    // String used to store recived and sent messeges
    int messegeSize = MESSEGE_SIZE;
    char * exchangedMessege = (char *) malloc(messegeSize * sizeof(char));

    // Socket's Descriptros and it`s initialization
    int socketDescriptor;
    socketDescriptor = socket(AF_INET6, SOCK_STREAM, 0);
 
 	// Structure used to save information about the server and it's initialization
    struct sockaddr_in6 serverAddress;
    bzero( &serverAddress, sizeof(serverAddress));
    serverAddress.sin6_family = AF_INET6;
    serverAddress.sin6_addr = in6addr_any; // Loop back Address
    serverAddress.sin6_port = htons(Port);
 
 	// Binds the socket assigning it's address
    bind(socketDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
 
 	// Starts listening for connections
 	int maxConnectionNum = MAX_CONNECTION_NUM;
    listen(socketDescriptor, maxConnectionNum);
 	

	while(TRUE)
	{
		printf("Waiting for Connection\n");
		//Initializes Clients Socket addres Structures
	    struct sockaddr_in6 clinetAddress;
	    unsigned int sizeClientAddress = sizeof(clinetAddress);
	    char IPString [INET6_ADDRSTRLEN];
	    bzero( &clinetAddress, sizeClientAddress);

	 	// Accepts connections 
	    int connectionDescriptor;
	    if((connectionDescriptor = accept(socketDescriptor, (struct sockaddr*) NULL, NULL) ) < 0)
      	{
        	perror("Failed to Accept()");
         	break;
      	}

	    printf("Connection Accepted\n");

	    getpeername(connectionDescriptor, (struct sockaddr *)&clinetAddress, &sizeClientAddress);
	    // Just a messege to let one know what is going on in the server side
	    inet_ntop(AF_INET6, &clinetAddress.sin6_addr, IPString, sizeof(IPString)) ;
	   	printf("Just Started a new connection with : \n");
	    printf("Ip Adress : %s\n", IPString);
	    printf("Port : %d \n\n", ntohs(clinetAddress.sin6_port) );
	    
	 	
	 	// Initializes queue that mantains the ranking
	    queue ranking = queueInit();

	    int Time;
	    do
	    {
	    	// Clean the memory of the messe String and recives the new messege from 
	    	// the client that is currently connected
	        bzero( exchangedMessege, messegeSize);
	        read(connectionDescriptor, exchangedMessege, messegeSize);

	        // Parses string to into so it can be included in the rank
	        Time = atoi(exchangedMessege);
	        int rank  = queueInclude(ranking, Time);

	        // Just a messege to let one know what is going on in the server side
	        printf("Echoing back Rank - %d\n", rank);
	       
	        // Parses int rank result to string,so in can be passed to through messege in the socket
	        sprintf(exchangedMessege, "%d", rank);

	        //Writes
	        write(connectionDescriptor, exchangedMessege, strlen(exchangedMessege)+1);
	    }while(Time != -1);

		// Closes a particullar connection (Just one)
	    close(connectionDescriptor);

	    // Free ranking so it can be initialized from 0 in the next connection
		freeQueue(ranking);
	}

	//Closes the Socket
	close(socketDescriptor);

	//Frees the messege allocated memmory
    free(exchangedMessege);

    return 1;
}
