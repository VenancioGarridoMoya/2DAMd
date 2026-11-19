#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
// Manejador de señal

void funcionManejadorHijo(int segnal){
    printf("\t\t Soy el Hijo, recibo %d\n", segnal);
}
void funcionManejadorPadre(int segnal){
    printf("\t Soy el Padre, recibo %d\n", segnal);
}
int main(){
    const int ITERACIONES= 5;
    __pid_t pidProceso;
    int salida=0;
    char caracter=0;
    
    pidProceso = fork();
    
    switch (pidProceso) {
    case -1:
        printf("Error, no se pudo crear el proceso\n");
        salida=-1;
        break;
    case 0: // estoy en el proceso hijo
        printf("\t\tSoy el proceso hijo con pid %d\n", getpid());
        signal(SIGUSR1, funcionManejadorHijo);
        printf("\t\tSe ha asignado la función funcionManejadorHijo a la señal SIGUSR1\n");
        for (int i=1; i<=ITERACIONES;i++){
            sleep(1);
            printf("\t\tHijo %d",i);
            kill (getppid(), SIGUSR1);
            pause();
        }; 
        break;
    default: //estoy en el proceso padre (el valor es el de el pid del hijo)
        printf("\tSoy el proceso padre %d\n",getpid());
        int i=1;
        printf("\tPadre %d",i);
        signal(SIGUSR1, funcionManejadorPadre);
        printf("\t Se ha asignado la función funcionManejadorPadre a la señal SIGUSR1\n");
        for (i++;i<=ITERACIONES;i++){
            pause();
            printf("\tPadre %d",i);
            sleep(1);
            kill (pidProceso, SIGUSR1);
        }; 
        break;
    }
    printf("\nProceso %d terminado.\n", getpid());
    return(salida);
}