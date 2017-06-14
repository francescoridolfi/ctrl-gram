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
#define CLIENT_PORT 5555
/** Prototype function **/
void *connection_handler(void *);
void ctrl_send();
/** Global variables **/
int socket_send;
int socket_recv;

int main(int argc , char *argv[]){
    /*== INIT ==*/
    im_server();
    check_args(argc, argv);
    control();
    //info();
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
        fprintf(stderr, "\033[1;0m[\033[1;31mERROR\033[1;1m]\033[1;31m\tCould not create socket\033[0;0m\n");
        exit(-1);
    } printf("\033[1;0m[\033[1;32mOK\033[1;0m]\033[1;32m\tSocket created\033[0;0m\n");

    /*== Settings ==*/
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    /*== Bind ==*/
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
        fprintf(stderr,"\033[1;0m[\033[1;31mERROR\033[1;0m]\033[1;31m\tBind failed\033[0;0m\n");
        return 1;
    } printf("\033[1;0m[\033[1;32mOK\033[1;0m]\033[1;32m\tBind done\033[0;0m\n");

    /*== Listen  & Accept ==*/
    listen(socket_desc , 3);
    printf("\033[1;0m[\033[1;36mINFO\033[1;0m]\033[1;36m\tWaiting for incoming connections...\033[0;0m\n");
    c = sizeof(struct sockaddr_in);
    while((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))){
        printf("\033[1;0m[\033[1;32mOK\033[1;0m]\033[1;32m\tConnection accepted\033[0;0m\n");
        printf("\033[1;0m[\033[1;36mINFO\033[1;0m]\033[1;36m\tClient IP address is: \033[1;34m%s\033[0;0m\n", inet_ntoa(client.sin_addr));
        ip_table[ip_index] = inet_ntoa(client.sin_addr);
        ip_index++;
        new_sock = malloc(1);
        *new_sock = new_socket;

        /*== FORK!! ==*/
        send_pid = fork();
        switch (send_pid){
          case -1:
            fprintf(stderr, "\033[1;0m[\033[1;31mERROR\033[1;0m]\033[1;31m\tFork failure\033[0;0m\n");
            exit(-1);
          case 0:
            ctrl_send();
          default:
            break;
        }
        /*== Thread ==*/
        pthread_t sniffer_thread;
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0){
            fprintf(stderr, "\033[1;0m[\033[1;31mERROR\033[1;0m]\033[1;31m\tCould not create thread\033[0;0m\n");
            exit(-1);
        } printf("\033[1;0m[\033[1;32mOK\033[1;0m]\033[1;32m\tHandler assigned\033[0;0m\n");
    }
    if (new_socket<0){
        fprintf(stderr, "\033[1;0m[\033[1;31mERROR\033[1;0m]\033[1;31m\tAccept failed\033[0;0m\n");
        exit(-1);
    }
    return 0;
}
void ctrl_send(){
  /*== Declare ==*/
  struct sockaddr_in server;
  char message[1024] , server_reply[1024];

  printf("\033[1;0m[\033[1;36mINFO\033[1;0m]\033[1;36m\tI'm the child process\033[0;0m\n");

  /*== Create socket ==*/
  socket_send = socket(AF_INET , SOCK_STREAM , 0);
  if(socket_send == -1){
      fprintf(stderr, "\033[1;0m[\033[1;31mERROR\033[1;0m]\033[1;31m\tCould not create socket (for send)\033[0;0m\n");
      exit(-2);
  } printf("\033[1;0m[\033[1;32mOK\033[1;0m]\033[1;32m\tSocket created (for send)\033[0;0m\n");

  /*== Settings ==*/
  server.sin_addr.s_addr = inet_addr(ip_table[ip_index-1]);
  server.sin_family = AF_INET;
  server.sin_port = htons(CLIENT_PORT);

  /*== Connect to client ==*/
  if (connect(socket_send, (struct sockaddr *)&server , sizeof(server)) < 0){
      fprintf(stderr, "\033[1;0m[\033[1;31mERROR\033[1;0m]\033[1;31m\tConnect to client failed\033[0;0m\n");
      exit(-2);
  } printf("\033[1;0m[\033[1;32mOK\033[1;0m]\033[1;32m\tConnected to client\033[0;0m\n");
  while(1){
    write(socket_send,"ciao\n",sizeof("\nciao\n"));
  }
}
void *connection_handler(void *socket_desc){

    /*== Get the socket descriptor ==*/
    socket_recv = *(int*)socket_desc;
    int read_size;
    char *message , client_message[1024];

    /*== Save identity client ==*/
    recv(socket_recv, client_connected[nr_connected], sizeof(client_connected[nr_connected]), 0);
    nr_connected++;

    /*== Receive message from client ==*/
    while( (read_size = recv(socket_recv , client_message , 1024 , 0)) > 0 )
    {
        printf("\033[1;36mClient : \033[0;0m%s\n", client_message);
        memset(client_message, 0 , strlen(client_message));
        fflush(stdout);
        control_cmd(client_message);
    }

    if(read_size == 0){
        printf("\033[1;0m[\033[1;36mINFO\033[1;0m]\033[1;36m\tClient disconnected\033[0;0m\n");
        fflush(stdout);}
    else if(read_size == -1){
        fprintf(stderr, "\033[1;0m[\033[1;31mOK\033[1;0m]\033[1;31m\tRecv failed\033[0;0m\n");}

    /*== Free the socket pointer ==*/
    free(socket_desc);
    return 0;
}
