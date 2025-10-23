// comando linux para ver los procesos: pstree -c | grep fork

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main(){
    __pid_t pid1,pid2,pidProcesoAbuelo,pidHijo,pidNieto;
    char quienSoy[15];
    int salida=0;
    char caracter=0;
    pid1 = fork();
    
    switch (pid1) {
    case -1:
        printf("Error, no se pudo crear el proceso Hijo");
        salida=-1;
        break;
    case 0: // estoy en el proceso padre para crear el nieto
        pid2= fork();
        switch(pid2){
            case -1: 
                printf("Error, no se pudo crear el Nieto");
                salida=-1;
                break;
            case 0: // estoy en el proceso nieto 
                strcpy(quienSoy,"nieto");
                printf("Soy el proceso nieto\n \t Mi PID  es %d, y el PID de mi padre es %d.",
                getpid(), getppid());
                printf("\nPulsa intro para continuar: ");
                caracter=getchar();
                break;
            default: //estoy en el hijo....
                strcpy(quienSoy,"hijo");
                pidNieto = wait(NULL);
                printf("Soy el proceso hijo\n \t Mi PID  es %d, y el PID de mi padre es %d.",
                getpid(), getppid());
                 break;
        }
        break;
    default: //estoy en el proceso Abuelo (el valor es el de el pid del hijo)
        strcpy(quienSoy,"abuelo");
        printf("Espero a que termine mi hijo.\n");
        pidHijo= wait(NULL);
        printf("\nSoy el proceso Abuelo\n \t Mi PID  es %d\n, \tEl PID de mi hijo es es %d.\n ",
         getpid(), pidHijo);
        printf("\t El PID de mi padre es: %d.\n", getppid());
        break;
    }
    printf("\nFin del programa %s\n",quienSoy);
    return(salida);
}