#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

//variable global para contar señales recibidas
int contadorSenales=0;
int fd[2];


// Padre manejador para la señal SIGUSR1
void manejadorPadre(int senal){
    read(fd[0],&contadorSenales,sizeof(int)); // padre lee contador del pipe
    printf("\n%d El PADRE (%d) recibe la señal %d \n",contadorSenales+1, getpid(), senal);
}

//principal
int main(){
    __pid_t pidProceso,pidHijo, pidPadre;
    int salida=0, i=0;
    char caracter=0;
    int numSenales=0;
    pipe(fd);// pipe para enviar/recibir el contador de señales
    printf("¿Qué número de señales quieres enviar al padre: ");
    scanf("%d", &numSenales);

    pidPadre=getpid();
    pidProceso = fork();
    switch (pidProceso) {
    case -1:
        printf("Error, no se pudo crear el proceso");
        salida=-1;
        break;
    case 0: // estoy en el proceso hijo
        sleep(1);
        for (contadorSenales=0;contadorSenales<numSenales;contadorSenales++){
            write(fd[1],&contadorSenales,sizeof(int)); // hijo escribe contador en pipe
            kill(pidPadre, SIGUSR1); // hijo envía señal al padre
            sleep(1);
        }
        kill (pidPadre,SIGKILL); // hijo mata al padre
        break;
    default: //estoy en el proceso padre (el valor es el de el pid del hijo)
        signal(SIGUSR1,manejadorPadre);    
        while(1){// no hace nada...espera su muerte
            pause(); // espera señal
        }
        break;
    }
    printf("\n--> Termina proceso %d.\n", getpid());
    return(salida);
}