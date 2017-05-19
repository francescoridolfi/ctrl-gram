/* FILE core.h
Made by SourceCode2 and ridolfino
Github repository : https://github.com/SourceCode2/Voicegram.git
LICENSE GPLv3 */
#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global variable
char *commands[100] = {"/join","cioa"};
int ip_index = 0;
char *ip_table[100]; int i;
char *pwd;

// Prototype function
int pwd();
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
int pwd(){
  const char* daeseg = "pwd";
  FILE * f = popen( daeseg, "r" );
  if ( f == 0 ) {
   fprintf( stderr, "Error console\n" );
   return 1;
  }
  while( fgets( pwd, strlen(pwd), f ) ) {}
  pclose( f );
  return 0;
}
int control_banner() {
  FILE *stream;
  char *pathbanner = pwd + "/Banner";
  stream=fopen("pathbanner", "r");
  if (stream == 0) {
    fprintf(stderr, "Error Banner not found\n");
  }
  fclose(stream);
}
#endif // CORE_H_INCLUDED
