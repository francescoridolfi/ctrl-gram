/*
FILE client.c
Made by SourceCode2 and ridolfino
Github repository : https://github.com/SourceCode2/Voicegram.git
LICENSE GPLv3
*/
#include"../moduli/core.h"
#include<stdlib.h>
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr

int main(int argc , char *argv[])
{
    control_banner();
    int sock;
    struct sockaddr_in server;
    char message[1024] , server_reply[1024];

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

    //keep communicating with server
    while(1)
    {

        printf("$> ");
        fgets(message, sizeof(message),stdin);

        //Send some data
        if( send(sock , message , 1024 , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        memset(message, 0 , strlen(message));
        //Receive a reply from the server
        if( recv(sock , server_reply , strlen(server_reply) , 0) < 0)
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
