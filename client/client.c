/*
FILE client.c
Made by SourceCode2 and ridolfino
Github repository : https://github.com/SourceCode2/Voicegram.git
LICENSE GPLv3
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

// Global variable
char my_ip[15];

// Prototype function
int ip();

// START !!
int main(int argc , char *argv[])
{
    ip();
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");
    puts("Benvenuti in Voicegram!");
    //keep communicating with server
    while(1)
    {

        printf("Enter message: ");
        fgets(message, sizeof(message),stdin);
        //scanf("%s" , message);
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        memset(message, 0 , strlen(message));

        //Receive a reply from the server
        if( recv(sock , server_reply , 1024 , 0) < 0)
        {
            puts("recv failed");
            break;
        }

        printf("Server Reply: %s\n", server_reply);
        server_reply[0]='\0';
        memset(server_reply, 0, strlen(server_reply));
    }

    close(sock);
    return 0;
}
