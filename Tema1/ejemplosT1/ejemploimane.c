#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int fd[2];
    char buffer[30];//aqui guardaremos el mensaje que lee el padre
    pid_t pid;//guardaremos el id del proceso hijo
    int salida;
    char quienSoy[15];


    pipe(fd); //creamos el pipe

    pid = fork();

    switch (pid){
        case -1: //por si hay error al crear el proceso
            printf("Error al crear el proceso hijo\n");
            salida = -1;
            break;
        case 0: // Proceso hijo
            strcpy(quienSoy,"Hijo");
            printf("El proceso HIJO escribe en la tubería...\n"); //mensaje qu escribe el hijo en el pipe
            write(fd[1], "Hola papi", 10);
            salida=1;
            break;
        default:
            strcpy(quienSoy,"Padre");
            wait(NULL); //el padre espera a que termine el hijo
            printf("El proceso PADRE lee de la tubería...\n");
            read(fd[0], buffer, 10);
            printf("\nEl mensaje es: %s\n", buffer); //el padre lee lo que el hijo ha escrito
            salida=1;
            break;
    }
    printf("\nFIN del programa %s\n", quienSoy);
    return salida;
}