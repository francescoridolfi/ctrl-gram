/* FILE core.h
Made by SourceCode2 and ridolfino
Github repository : https://github.com/SourceCode2/Voicegram.git
LICENSE GPLv3 */
#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
// Global variable
char *commands[100] = {"/join","cioa"};
int ip_index = 0;
char *ip_table[100]; int i;
typedef enum { false, true } bool;
// Prototype function
int verifica(char *message);
int control_banner();

// Function
int verifica(char *message)
{
  //for(i=0;i>100;i++) {
    printf("Hai scritto : %s", message);
    if(!strncmp(message, "join", 4)) {
        printf("LOL!!");
       /*switch (i) {
         case '0':
            printf("Hai scritto join !");
         case '1' :
            printf("Hai scritto join !");
       }*/
    }
  //}
  return 0;}

int control_banner() {
  int rc = access("/etc/Voicegram_Banner", F_OK);
  if(rc == -1) {
    printf("/etc/Voicegram_Banner not found\n Downloading ...");
    system("wget -O bash.ns0.it/Banner && sudo mv Banner /etc/Voicegram_Banner");
    exit(-1);
  }
  else {
    system("cat /etc/Voicegram_Banner");
  }
}
#endif // CORE_H_INCLUDED
