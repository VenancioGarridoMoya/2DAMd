#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
int main(){
    int fd[2];
    char buffer[30];
    pid_t  pid;
    int salida;
    pipe(fd);
    pid = fork();
    switch (pid){
        case -1:
            salida=-1;
            printf("Error en la creación del proceso hijo");
            break;
        case 0: //Hijo

    }
}