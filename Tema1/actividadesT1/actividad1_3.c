#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>


// Padre manejador para la señal SIGUSR1
void manejadorPadre(int senal){
    printf("\nEl PADRE recibe la señal ... %d proceso: %d).\n",senal,getpid());
}

//principal
int main(){
    __pid_t pidProceso,pidHijo, pidPadre;
    int salida=0, i=0;
    char caracter=0;
    pidPadre=getpid();
    pidProceso = fork();
    
    switch (pidProceso) {
    case -1:
        printf("Error, no se pudo crear el proceso");
        salida=-1;
        break;
    case 0: // estoy en el proceso hijo
        sleep(1);
        for (i=0;i<10;i++){
            kill(pidPadre, SIGUSR1); // hijo envía señal al padre
            sleep(1);
        }
        kill (pidPadre,SIGKILL);
        break;
    default: //estoy en el proceso padre (el valor es el de el pid del hijo)
        signal(SIGUSR1,manejadorPadre);    
        while(1){// no hace nada...espera su muerte
            pause();
        }
        break;
    }
    printf("\n--> Termina proceso %d.\n", getpid());
    return(salida);
}