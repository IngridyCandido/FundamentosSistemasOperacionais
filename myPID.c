#include <stdio.h>
#include <unistd.h>
/* #include <sys/type.h> */

int main(void) {
   pid_t childpid;
   pid_t mypid;

   mypid = getpid();
   childpid = fork();
   if (childpid == -1) {
	//perror("Failed to fork");
	perror("Falha na criacao do fork");
	return 1;
   }
   if (childpid == 0) 
        printf("Eu sou o processo filho %ld, ID = %ld\n",(long int)  getpid(), (long int) mypid);
   else
	printf("Eu sou o processo pai %ld, ID = %ld\n", (long int) getpid(), (long int) mypid);  return 0;
}
