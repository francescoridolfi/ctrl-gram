/*
FILE server.c
Made by SourceCode2 and ridolfino
Github repository : https://github.com/SourceCode2/Zitagram.git
LICENSE GPLv3
*/

//Davide Magno
#include"../moduli/core.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h> //for threading

// Global variable
// Prototype function
void *connection_handler(void *);


// START !!

int main(int argc , char *argv[])
{
    control();
    info();
    init();
    printf("%s\n",identity);
    int socket_desc , new_socket , c , *new_sock;
    struct sockaddr_in server , client;
    char *message;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted\n");
        printf("Client IP address is: %s\n", inet_ntoa(client.sin_addr));
        ip_table[ip_index] = inet_ntoa(client.sin_addr);
        ip_index++;
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;

        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }

        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( sniffer_thread , NULL);
        puts("Handler assigned");
    }

    if (new_socket<0)
    {
        perror("accept failed");
        return 1;
    }

    return 0;
}
int verifica1(char message[4]) {
      printf("Hai scritto : %s", message);
      if(!strncmp(message, "join",4)) {
      printf("Hai scritto join !");
      }
      return 0;
}
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[1024];
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 1024 , 0)) > 0 )
    {
        //Send the message back to client
        write(sock , client_message, sizeof(client_message));
        printf("Client : %s\n", client_message);
        verifica1(client_message);
        memset(client_message, 0 , strlen(client_message));
        fflush(stdout);
    }

    if(read_size == 0)
    {
        puts("Client disconnected\n");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed\n");
    }

    //Free the socket pointer
    free(socket_desc);
    return 0;
}
