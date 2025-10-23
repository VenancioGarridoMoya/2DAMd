#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
void main(){
    pid_t pid, pidHijo;
    int retorno=0;
    pid = fork();
    if (pid == -1){
        printf("Error-> no se pudo crear el proceso hijo");
        retorno=-1;
    } else{
        if (pid ==0){ //estoy en el proceso hijo
            printf("Soy el proceso hijo: \n\t mi pid es %d, el pid de mi padre es %d.\n",
            getpid(), getppid());
        } else { //esty en el proceso padre
            pidHijo = wait(NULL);
            printf("Soy el proceso padre:\n\t  mi pid es %d, el pid de mi padre es %d.",
            getpid(), getppid());
            printf("Mi hijo terminó con su pid %d\n", pid);
        }
    }
    printf("Fin del programa\n\n");
    exit(retorno);
}