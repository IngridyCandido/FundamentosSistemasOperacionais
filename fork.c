#include <stdio.h>
#include <unistd.h>

int main (void) {
  int x;
  
  x=0;
  fork();
  x=1;
  printf("Eu sou o processo %Id e meu x é %d\n", (long)getpid(),x);
  
  return 0;
}
