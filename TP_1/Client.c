//
//  Client.c
//  Tp_01
//
//  Created by Paulo Cirino on 06/05/16.
//  Copyright © 2016 Paulo Cirino. All rights reserved.
//

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#include "readingTime.h"
 
#define TRUE 1
#define FALSE 0
#define EXIT_FLAG -1
#define MESSEGE_SIZE 100

int main(int argc,char ** argv)
{
    //Checks if arguments are valid
    if(argc != 3)
    {
        printf("Wrong Number of Arguments. \n");
        printf("Correct usde would be \n ./Server [ip/nome] [Port]\n");
        return 300;
    }

    //Checks if port is a positive value
    int Port = atoi(argv[2]);
    if(Port <= 0)
    {
    	printf("Invalid Port Error!!!! \n\n");
    	return 12;
    }

    /**************** Initializes and Sets Variables and Structures ****************/

    // Auxiliary addrinfo declaration
    struct addrinfo addressInfo;
    memset(&addressInfo, 0x00, sizeof(addressInfo));
    addressInfo.ai_flags    = AI_NUMERICSERV;
    addressInfo.ai_family   = AF_UNSPEC;
    addressInfo.ai_socktype = SOCK_STREAM;
 
 	// Check if we were provided the address of the server converting the text to binary  
 	// If numeric we prevent getaddrinfo() of doing name resolution
    int flagVal;
    struct sockaddr_in6 destAddress;
    flagVal = inet_pton(AF_INET, argv[1], &destAddress);

    // If IPv4
    if( flagVal == 1)
    {
        addressInfo.ai_family = AF_INET;
        addressInfo.ai_flags |= AI_NUMERICHOST;
    }
    
    // If IPv6
    else
    {
        flagVal = inet_pton(AF_INET6, argv[1], &destAddress);
        if (flagVal == 1) 
        {
	        addressInfo.ai_family = AF_INET6;
	        addressInfo.ai_flags |= AI_NUMERICHOST;
        }
    }

    // Get the address information for the server 
    struct addrinfo * auxAdressInfo = NULL;
    flagVal = getaddrinfo(argv[1], argv[2], &addressInfo, &auxAdressInfo);
    if (flagVal != 0)
    {
        printf("Host not found --> %s\n", gai_strerror(flagVal));
        return 3;
    }

    // Inicializes the connection socket
    int socketDescriptor;
    socketDescriptor = socket(auxAdressInfo->ai_family, auxAdressInfo->ai_socktype, auxAdressInfo->ai_protocol);
    if (socketDescriptor < 0)
    {
        perror("socket() failed");
        return 1;
    }

    // Connects to the server
    if ( (flagVal = connect(socketDescriptor, auxAdressInfo->ai_addr, auxAdressInfo->ai_addrlen ) ) < 0 )
    {
        printf("Error in setting the connection\n");
        printf("Are your shure your are using the right port ?\n");
        return 2;
    }
 
 	// Messege string thats gonna be used to send and recive data
    int messegeSize = MESSEGE_SIZE;
    char * exchangedMessege = (char *) malloc(messegeSize * sizeof(char));

    while(TRUE)
    {
        printf("Cliente :> ");
        
        // Reads Client Ipunt
        int ReadTime = readLine();

        // Cleans exchangedMessege string and parse ReadTime saving in it
        bzero( exchangedMessege, messegeSize);
        sprintf(exchangedMessege, "%d", ReadTime);

        // Sends Messege to Server
        write(socketDescriptor, exchangedMessege, strlen(exchangedMessege)+1);
        
        // If the exit flag is 
        if(ReadTime == EXIT_FLAG)
        {
            break;
        }

		// Cleans exchangedMessege string and Reads the server messege
        bzero( exchangedMessege, messegeSize);
        read(socketDescriptor, exchangedMessege, messegeSize);

        // Prints Server Response
        printf("Servidor :> %s\n\n", exchangedMessege);
    }
    
    // Closes connection socket
    close(socketDescriptor);

    // Freeing variables
    free (exchangedMessege);
    freeaddrinfo(auxAdressInfo);

    return 0;
}