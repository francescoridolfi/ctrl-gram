/*
FILE server.c
Made by SourceCode2 and ridolfino
Github repository : https://github.com/SourceCode2/Voicegram.git
LICENSE GPLv3
*/

//Davide Magno
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h> //for threading

// Global variable
int ip_index = 0;
char ip[15];
char *ip_table[100];
// Prototype function
void *connection_handler(void *);


// START !!

int main(int argc , char *argv[])
{
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
        puts("Connection accepted");
        //int p1 = client.sin_addr.s_addr&0xFF;
        //int p2 = (client.sin_addr.s_addr&0xFF00)>>8;
        //int p3 = (client.sin_addr.s_addr&0xFF0000)>>16;
        //int p4 = (client.sin_addr.s_addr&0xFF000000)>>24;
        //printf("IP DEBUG = %d.%d.%d.%d\n",p1,p2,p3,p4);
        printf("IP address is: %s\n", inet_ntoa(client.sin_addr));
        printf("port is: %d\n", (int) ntohs(client.sin_port));
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

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[1024];
    //Receive a message from client
    recv(sock, ip , 15 ,0);
    ip_table[ip_index] = ip;
    puts(ip_table[ip_index]);
    ip_index++;
    while( (read_size = recv(sock , client_message , 1024 , 0)) > 0 )
    {
        //Send the message back to client
        write(sock , client_message, sizeof(client_message));
        printf("Client : %s", client_message);
        memset(client_message, 0 , strlen(client_message));
        fflush(stdout);
    }

    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }

    //Free the socket pointer
    free(socket_desc);
    return 0;
}
