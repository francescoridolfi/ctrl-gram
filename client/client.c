/*
FILE client.c
Made by SourceCode2 and ridolfino
Github repository : https://github.com/ctrlTab/ctrl-gram.git
LICENSE GPLv3
*/

/*== Davide magno ==*/
#include "../moduli/core.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#define MY_PORT 4444

/*== Prototype functions ==*/
void *connection_handler(void *);
void ctrl_recv();

int main(int argc , char *argv[]){
    /*== INIT ==*/
    check_args(argc, argv);
    control();
    info();
    init();

    /*== Declare ==*/
    int sock;
    struct sockaddr_in server;
    char message[1024] , server_reply[1024];
    pid_t recv_pid; int recv_status;
     
    /*== FORK!! ==*/
    recv_pid = fork();
    switch (recv_pid) {
      case -1:
        fprintf(stderr, "\033[1;31m[ERROR]\tFork failure\033[0;0m\n");
        exit(-1);
      case 0:
        ctrl_recv();
      default:
        //sleep(1);
        break;
    }
    
    /*== Create socket ==*/
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1) {
        fprintf(stderr, "\033[1;31m[ERROR]\tCould not create socket\033[0;0m\n");
        exit(-1);
    } printf("\033[1;32m[OK]\tSocket created\033[0;0m\n");

    /*== Settings ==*/
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));

    /*== Connect to remote server ==*/
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        fprintf(stderr, "\033[1;31m[ERROR]\tConnect failed\033[0;0m\n");
        exit(-1);
    } printf("\033[1;32m[OK]\tConnected\033[0;0m\n");

    /*== Communicating with server ==*/
    send(sock, identity, sizeof(identity),0);
    while(1)
    {
        printf("$> ");
        fgets(message, sizeof(message),stdin);
        if( send(sock , message , 1024 , 0) < 0) {
            fprintf(stderr, "\033[1;31m[ERROR]\tSend failed\033[0;0m\n");
            return 1;
        }
        memset(message, 0 , strlen(message));
    }

        close(sock);
        return 0;
}
void ctrl_recv(){
  int socket_desc , new_socket , c , *new_sock;
  struct sockaddr_in server , client;
  char *message;

  /*== Create socket ==*/
  socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if (socket_desc == -1){
      fprintf(stderr, "\033[1;31m[ERROR]\tCould not create socket (for recv)\033[0;0m\n");
  } printf("\033[1;32m[OK]\tSocket created (for recv)\033[0;0m\n");

  /*== Prepare the sockaddr_in structure ==*/
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(MY_PORT);

  /*== Bind ==*/
  if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
      fprintf(stderr, "\033[1;31m[ERROR]\tBind failed (for recv)\033[0;0m\n");
      exit(-2);
  } printf("\033[1;32m[OK]\tBind done (for recv)\033[0;0m\n");

  /*== Listen ==*/
  listen(socket_desc , 3);

  /*== Accept and incoming connection ==*/
  printf("\033[1;36m[INFO]\tWaiting for incoming connections...\033[0;0m\n");
  c = sizeof(struct sockaddr_in);
  while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
  {
      puts("\033[1;32m[OK]\tConnection accepted (for recv)\033[0;0m\n");
      pthread_t handler_thread;
      new_sock = malloc(1);
      *new_sock = new_socket;

      if( pthread_create( &handler_thread , NULL ,  connection_handler , (void*) new_sock) < 0){
          fprintf(stderr, "\033[1;31m[ERROR]\tCould not create thread (for recv)\033[0;0m\n");
          exit(-2);
      }
      else {
        pthread_join(handler_thread, NULL);
      }
  }

  if (new_socket<0){
      fprintf(stderr, "\033[1;31m[ERROR]\tAccept failed (for recv)\033[0;0m\n");
      exit(-2);
  }
}
void *connection_handler(void *socket_desc){
    
    /*== Declare ==*/
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[1024];
    
    /*== Receive a message from client ==*/
    while( (read_size = recv(sock , client_message , 1024 , 0)) > 0 )
    {
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
