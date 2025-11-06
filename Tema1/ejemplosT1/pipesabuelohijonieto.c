// Abuelo-hijo-nieto se envían en los dos sentidos
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
int main(){
    __pid_t pidProceso1, pidProceso2,pidHijo, pidPadre, pidNieto;
    int salida=0;
    char caracter=0;
    char saludoAbuelo[]="Saludos del Abuelo...\n"; 
    char saludoHijo[]="Saludos del Hijo...\n";
    char saludoNieto[]="Saludos del Nieto...\n";
    
    char buffer[50];
    int fd1[2];
    int fd2[2];
    pipe(fd1); //abuelo->hijo hijo<-nieto
    pipe(fd2); //abuelo<-hijo hijo->nieto

    pidProceso1 = fork(); //Abuelo va a crear el Hijo
    switch(pidProceso1) {
    case -1:
        printf("Error, no se pudo crear el proceso Hijo");
        salida=-1;
        break;
    case 0: // estoy en el proceso hijo
//************* */
        pidProceso2 = fork(); //Hijo va a crear el Nieto
        switch(pidProceso2) {
            case -1:
                printf("Error, no se pudo crear el proceso Nieto");
                salida=-2;
                break;
            case 0: // estoy en el proceso Nieto
                //Nieto recibe
                close(fd2[1]); //  nieto va a leer
                read(fd2[0], buffer, sizeof(buffer));
                printf("\t\tEl NIETO recibe mensaje del HIJO (su padre): %s\n", buffer);
                //Nieto envía
                printf("\t\tEl NIETO envía mensaje al HIJO.....\n");
                close(fd1[0]); //  nieto va a escribir
                write(fd1[1], saludoNieto, strlen(saludoNieto));
                break;
            default: //estoy en el proceso Hijo)
                //Hijo recibe
                close(fd1[1]); //  Hijo va a leer del Abuelo
                read(fd1[0], buffer, sizeof(buffer));
                printf("\tEl Hijo recibe mensaje del Abuelo: %s\n", buffer);
                //Hijo envía al nietp
                printf("\tEl Hijo envía mensaje al Nieto.....\n");
                close(fd2[0]); //  Hijo va a escribir al Nieto
                write(fd2[1], saludoHijo, strlen(saludoHijo));
                pidNieto=wait(NULL); //espero a que termine el Nieto
                //Hijo recibe de su Nieto
                close(fd1[1]);
                read(fd1[0], buffer, sizeof(buffer));
                printf("\tEl Hijo recibe mensaje del Nieto: %s\n", buffer);

                // Hijo envía al Abuelo
                printf("\tHIJO envía mensaje a su padre....\n");
                close(fd2[0]); // cierra el descriptor de e/ ya que no va a escribir
                write(fd2[1],saludoHijo,strlen(saludoHijo));
                break;
            }
        break;
    default: //estoy en el proceso abuelo (el valor es el de el pid del hijo)
        //Abuelo envía
        printf("ABUELO envía mensaje al HIJO....\n");
        close(fd1[0]); // cierra el descriptor de s/ ya que no va a leer
        write(fd1[1],saludoAbuelo,strlen(saludoAbuelo));
        pidHijo=wait(NULL);
        //Abuelo recibe
        close(fd2[1]); // cierra el descriptor de s/ ya que no va a escribir
        read(fd2[0], buffer, sizeof(buffer));
        printf("El ABUELO recibe mensaje del HIJO: %s\n", buffer);
        break;
    }
    printf("Termina el proceso %d\n", getpid());
    return(salida);
}