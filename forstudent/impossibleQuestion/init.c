#include "fcntl.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/stat.h"
#include <time.h>


int main() { 
  struct stat st; FILE* fd; 
  
  if(!stat("number.txt", &st)) { 
     printf("file already exists\n Removing old file.\n"); 
     remove("number.txt");
   } 
  fd = fopen("number.txt", "ax");
  srand((unsigned int)time(NULL));

  // Generate a random number between 45 and 145
  int randomNumber = rand() % 101 + 45;    
  fprintf(fd, "%d", randomNumber);
  fflush(fd);
  fclose(fd); 
  sleep(2);
  chmod("number.txt", S_IREAD | S_IWRITE); 
  chown("number.txt",0,0);
  printf("Number generated\n");
  return 0;
}

