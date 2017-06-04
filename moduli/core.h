/* FILE core.h
Made by SourceCode2 and ridolfino
Github repository : https://github.com/SourceCode2/Zitagram.git
LICENSE GPLv3 */
#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Prototype function
void init();
void control();
void info();

// Global variable
char *my_ip;
char *commands[100] = {"/join","cioa"};
int ip_index = 0;
char *ip_table[100]; int i;
typedef enum { false, true } bool;
char identity[100];
char user[40];
char ip[15];
// Function
void init() {
  system("cat /etc/ctrl-gram/banner.txt");
}
void info(){
  int errore = 0;

  /*== Search IP  ==*/
	system("rm /tmp/IP");
	system("wget -q http://www.indirizzo-ip.com/ip.php?.txt -O /tmp/IP");
	FILE *searchIP;
	searchIP = fopen ( "/tmp/IP" , "r" ) ;
	if(searchIP){
		fscanf(searchIP,"%s", &ip);
		fclose(searchIP);
	}
	else {
	  fprintf(stderr, "Error opening /tmp/IP.\n");
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
    fprintf(stderr, "Error opening /etc/ctrl-gram/config.\n");
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
	  fprintf(stderr, "Error opening /tmp/ctrl-log.\n");
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
    strncat(identity, "\033[0;0m", sizeof("\033[0;0m]"));
  }
}
void control() {
  /*== check /etc/ctrl-gram/ ==*/
  int rc = access("/etc/ctrl-gram/", F_OK);
  if(rc==-1){
    fprintf(stderr, "Missing the ctrl-gram folder, fixing");
    system("sudo mkdir /etc/ctrl-gram");
  }

  /*== check /etc/ctrl-gram/banner.txt ==*/
  rc = access("/etc/ctrl-gram/banner.txt", F_OK);
  if(rc==-1) {
    fprintf(stderr, "Not found /etc/ctrl-gram/banner.\n");
    printf("Downloading ...\n");
    system("wget ctrltab.github.io/banner.txt && sudo mv banner.txt /etc/ctrl-gram/banner.txt");
    exit(-1);
  }
  /*== check /etc/ctrl-gram/config ==*/
  rc = access("/etc/ctrl-gram/config", F_OK);
  if(rc==-1){
    char *user;
    fprintf(stderr, "Not found the configuration file of ctrl-gram.\n");
    printf("Create a new config.\n");
    scanf("Username: %s",user);
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
#endif // CORE_H_INCLUDED
