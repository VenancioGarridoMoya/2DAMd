#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main(){
    __pid_t pidProceso,pidHijo, pidPadre;
    int  numero=6;
    int salida=0;
    char caracter=0;
    pidProceso = fork();
    
    switch (pidProceso) {
    case -1:
        printf("Error, no se pudo crear el proceso");
        salida=-1;
        break;
    case 0: // estoy en el proceso hijo
        printf("Soy el proceso hijo con pid %d,la variable vale %d", getpid(), numero);
        printf("\n\t la decremento en 5, ahora tiene un valor de: %d\n ",numero-=5);
         printf("\nPulsa intro para continuar: ");
         caracter=getchar();
         break;
    default: //estoy en el proceso padre (el valor es el de el pid del hijo)
        printf("Espero a que termine mi hijo.\n");
        pidHijo= wait(NULL);
        printf("Soy el proceso padre con pid %d,la variable vale %d", getpid(), numero);
        printf("\n\t la incremento en 5, ahora tiene elvalor de: %d\n ", numero+=5);
        break;
    }
    printf("Proceso %d terminado.\n", getpid());
    return(salida);
}