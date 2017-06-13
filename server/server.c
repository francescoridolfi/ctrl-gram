/*
FILE server.c
Made by SourceCode2 and ridolfino
Github repository : https://github.com/ctrlTab/ctrl-gram.git
LICENSE GPLv3
*/

/*== Davide Magno ==*/
#include "../moduli/core.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

/** Prototype function **/
void *connection_handler(void *);
void ctrl_send();
/** Global variables **/


int main(int argc , char *argv[]){
    /*== INIT ==*/
    im_server();
    check_args(argc, argv);
    control();
    info();
    init();

    /*== Declare ==*/
    int socket_desc , new_socket , c , *new_sock;
    struct sockaddr_in server , client;
    char *message;
    pid_t send_pid; int send_status;
    int port = atoi(argv[1]);

    /*== Create socket ==*/
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if(socket_desc == -1){
        printf("Could not create socket");
    }

    /*== Prepare the sockaddr_in structure ==*/
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( port );

    /*== Bind ==*/
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
        puts("bind failed");
        return 1;
    }
    puts("bind done");

    /*== Listen  & Accept ==*/
    listen(socket_desc , 3);
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))){
        puts("Connection accepted\n");
        printf("Client IP address is: %s\n", inet_ntoa(client.sin_addr));
        ip_table[ip_index] = inet_ntoa(client.sin_addr);
        ip_index++;
        new_sock = malloc(1);
        *new_sock = new_socket;

        /*== FORK!! ==*/
        send_pid = fork();
        switch (send_pid){
          case -1:
            fprintf(stderr, "\033[1;31mError fork\033[0;0m\n");
            exit(-1);
          case 0:
            ctrl_send();
          default:
            break;
        }
        /*== Thread ==*/
        pthread_t sniffer_thread;
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0){
            perror("could not create thread");
            return 1;}
        puts("Handler assigned");
    }
    if (new_socket<0){
        perror("accept failed");
        return 1;
    }
    return 0;
}

void ctrl_send(){
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

  server.sin_addr.s_addr = inet_addr(ip_table[ip_index-1]);
  server.sin_family = AF_INET;
  server.sin_port = htons( 5555 );

  //Connect to remote server
  if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
  {
      perror("connect failed. Error");
      exit(-1);
  }
  puts("Connected\n");
  while(1){
    write(sock ,"\nciao\n",sizeof("\nciao\n"));
  }

}
void *connection_handler(void *socket_desc){
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
