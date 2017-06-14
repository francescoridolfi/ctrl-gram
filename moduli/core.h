/* FILE core.h
Made by SourceCode2 and ridolfino
Github repository : https://github.com/ctrlTab/ctrl-gram.git
LICENSE GPLv3 */
#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <inttypes.h>
#define MAXCLIENTS 10
/*== Prototype function ==*/
void init();
void control();
void info();
void im_server();
void check_args(int argc, char *argv[]);
int control_cmd(char *message);

/*== Global variable ==*/
char *my_ip; int ip_index = 0; char *ip_table[100];
typedef enum { false, true } bool;
char identity[100]; char user[40]; char ip[15];
char *client_connected[MAXCLIENTS]; int nr_connected = 0;
int mod = 0;
int i;
int is_cmd; char *da_mandare;
/*==# Function #==*/
void init(){
  printf("\033[1;0m");
  system("cat /etc/ctrl-gram/banner.txt");
  printf("\033[0;0m");
}
void info(){
  int errore = 0;
  int rc;

  /*== Search IP  ==*/
  rc = access("/tmp/IP", F_OK);
  if(access==0) {
    system("rm /tmp/IP");
  }
  system("wget -q http://www.indirizzo-ip.com/ip.php?.txt -O /tmp/IP");
	FILE *searchIP;
	searchIP = fopen ( "/tmp/IP" , "r" );
	if(searchIP){
		fscanf(searchIP,"%s", &ip);
		fclose(searchIP);
	}
	else {
	  fprintf(stderr, "\033[1;31m[ERROR]\tOpening /tmp/IP failed\n\033[0;0m");
	  fclose(searchIP);
	  errore = 1;
	}

	/*== Search User  ==*/
	FILE *searchUser;
	searchUser = fopen("/etc/ctrl-gram/config","r");
	if(searchUser){
		fscanf(searchUser ,"%s",&user);
		fclose(searchUser);
	}
  else {
    fprintf(stderr, "\033[1;31m[ERROR]\tOpening /etc/ctrl-gram/config failed\n\033[0;0m");
    fclose(searchUser);
	  errore = 1;
	}

	/*== Search log  ==*/
	FILE *searchLog;
	char buffer[100];
	char trans[18] = "\033[40m\033[1;33m";
	searchLog = fopen("/tmp/ctrl-log","r");
	if(searchLog){
		fscanf(searchLog,"%s",&identity);
		fclose(searchLog);
		strcpy(buffer, identity);
		strcpy(identity,trans);
		strncat(identity, buffer, sizeof(buffer));
  }
	else {
	  fprintf(stderr, "\033[1;31m[ERROR]\tOpening /tmp/ctrl-log failed\n\033[0;0m");
	  fclose(searchLog);
	  errore = 1;
	}

	/*== Make identity  ==*/
	if(errore == 1){
		control();
	}
	else{
		strncat(identity, "\033[1;36m  ", sizeof("\033[1;36m  "));
		strncat(identity, user, sizeof(user));
		strncat(identity, "  \033[1;4;37m", sizeof("  \033[1;4;37m"));
		strncat(identity, ip, sizeof(ip));
    strncat(identity, "\033[0;0m\n", sizeof("\033[0;0m]\n"));
  }
}
void control(){
  /*== check /etc/ctrl-gram/ ==*/
  int rc = access("/etc/ctrl-gram/", F_OK);
  if(rc==-1){
    fprintf(stderr, "\033[1;31m[ERROR]\tMissing the ctrl-gram folder, \033[1;32mfixing\033[0;0m");
    system("sudo mkdir /etc/ctrl-gram");
  }

  /*== check /etc/ctrl-gram/banner.txt ==*/
  rc = access("/etc/ctrl-gram/banner.txt", F_OK);
  if(rc==-1) {
    fprintf(stderr, "\033[1;31m[ERROR]\tNot found /etc/ctrl-gram/banner.\n\033[0;0m");
    printf("\033[1;32mDownloading ...\n\033[0;0m");
    system("sudo wget -q ctrltab.github.io/banner.txt -O /etc/ctrl-gram/banner.txt");
  }
  /*== check /etc/ctrl-gram/config ==*/
  rc = access("/etc/ctrl-gram/config", F_OK);
  if(rc==-1){
    char *user;
    fprintf(stderr, "\033[1;31m[ERROR]\tNot found the configuration file of ctrl-gram.\n\033[0;0m");
    printf("\033[1;33mCreate a new config.\033[0;0m\n");
    scanf("\033[1;36mUsername: \033[1;0m%s\033[0;0m\n",user);
    system("sudo touch /etc/ctrl-gram/config");
    FILE *fd;
    fd = fopen("/etc/ctrl-gram/config","w");
    fprintf(fd,"%s",user);
    fclose(fd);
  }
  /*== check /tmp/log ==*/
  rc = access("/tmp/ctrl-log", F_OK);
  if(rc==-1){
    system("date '+[%d/%m/%g]:[%X]' > /tmp/ctrl-log");
  }
}
void im_server(){
  mod = 1;
}
void check_args(int argc, char *argv[]){
  if(!mod) {
    if(argc < 3) {
      fprintf(stderr,"\033[1;31m Error too few args\nUsage : client <ip_server> <port>\n\033[0;0m");
      exit(-1);
    }
    if(argc > 3) {
      fprintf(stderr,"\033[1;31mError too many args\nUsage : client <ip_server> <port>\n\033[0;0m");
      exit(-1);
    }
  }
  else {
    if(argc < 2){
      fprintf(stderr, "\033[1;31mError too few args\nUsage : server <port>\n\033[0;0m");
      exit(-1);
    }
    if(argc > 2){
      fprintf(stderr, "\033[1;31mError too many args\nUsage : server <port>\n\033[0;0m");
      exit(-1);
    }
  }
}
int control_cmd(char *message){
  if(!strncmp(message,"/alive",6)){
    is_cmd = 1;
    strcpy(da_mandare,client_connected[nr_connected]);
  }

}
#endif // CORE_H_INCLUDED
