#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
// Manejador de señal

void funcionManejador(int segnal){
    printf("\t El hijo ha recibido la señal %d\n", segnal);
}

int main(){
    __pid_t pidProceso,pidHijo, pidPadre;
    int  numero=6;
    int salida=0;
    char caracter=0;
    pidProceso = fork();
    
    switch (pidProceso) {
    case -1:
        printf("Error, no se pudo crear el proceso\n");
        salida=-1;
        break;
    case 0: // estoy en el proceso hijo
        printf("Soy el proceso hijo con pid %d\n", getpid());
        signal(SIGUSR1, funcionManejador);
        printf(" Se ha asignado la función funcionManejador  la señal SIGUSR1\n");
        while(1){}; //bucle infinito
        break;
    default: //estoy en el proceso padre (el valor es el de el pid del hijo)
        printf("Soy el proceso padre %d y voy a enviar dos señales SIGUSR1\n",getpid());
        sleep(1);
        kill(pidProceso, SIGUSR1); 
        sleep(1);
        kill(pidProceso, SIGUSR1);
        break;
    }
    printf("Proceso %d terminado.\n", getpid());
    return(salida);
}