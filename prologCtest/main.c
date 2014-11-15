#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define SOCKET_ERROR        -1
#define BUFFER_SIZE         100
#define HOST_NAME_SIZE      20

int  main(int argc, char* argv[])
{
    int hSocket;                 /* handle to socket */
    struct hostent* pHostInfo;   /* holds info about a machine */
    struct sockaddr_in Address;  /* Internet socket address stuct */
    long nHostAddress;
    char pBuffer[BUFFER_SIZE];
    unsigned nReadAmount;
    char strHostName[HOST_NAME_SIZE];
    int nHostPort;
    printf("Enter Host: ");
    scanf("%s",strHostName);
    printf("Enter Port: ");
    scanf("%d", &nHostPort);
    
    
    printf("\nMaking a socket");
    /* make a socket */
    hSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    
    if(hSocket == SOCKET_ERROR)
    {
        printf("\nCould not make a socket");
        return 0;
    }

    /* get IP address from name */
    pHostInfo=gethostbyname(strHostName);
    /* copy address into long */
    memcpy(&nHostAddress,pHostInfo->h_addr,pHostInfo->h_length);


    /* fill address struct */
    Address.sin_addr.s_addr=nHostAddress;
    Address.sin_port=htons(nHostPort);
    Address.sin_family=AF_INET;

    /* connect to host */
    if(connect(hSocket,(struct sockaddr*)&Address,sizeof(Address))
       == SOCKET_ERROR)
    {
        printf("\nCould not connect to host\n");
        return 0;
    }
    printf("\nConnected to port: %d",nHostPort);
    
    /* read from socket into buffer
     ** number returned by read() and write() is the number of bytes
     ** read or written, with -1 being that an error occured */
    char sendMessage[] = "grandmother(liz,chas).";
    
    printf("\nSending \"%s\" to port 7777",sendMessage);
    write(hSocket,sendMessage, strlen(sendMessage));
    
    nReadAmount=read(hSocket,pBuffer,BUFFER_SIZE);
    //char * buffer = "";
    //strcpy(buffer, pBuffer);
    printf("\nReceived \"%s\" from server\n",pBuffer);
    /* write what we received back to the server */
    
    //printf("\nWriting \"%s\" to server",pBuffer);
    
    printf("\nClosing socket\n");
    /* close socket */
    if(close(hSocket) == SOCKET_ERROR)
    {
        printf("\nCould not close socket\n");
        return 0;
    }
}



