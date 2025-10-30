#include <string.h>     /* Función strlen() */
#include <fcntl.h>      /* Modos de apertura y función open()*/
#include <stdlib.h>
#include <stdio.h> 
 
int main(int argc, char *argv[]){
 
  /* Variables */
  int fd, nBytesLeidos, salida;
  char buffer[10];
  char saludo[]=" Saludo....!!!!";
 
   /* Escribimos en el archivo */
  fd = open("texto.txt", 1);
  if (fd==-1){
    printf("Error en apertura para escritura de archivo");
    salida = -1;
  } else {
    printf("Voy a Escribir el saludo.\n");
    write(fd, saludo, strlen(saludo));
    printf("Saludo escrito en el fichero.\n");
    close(fd);
    fd=open("texto.txt", 0);
    if (fd==-1){
        printf("Error apertura para lectura de archivo");
        salida = -2;
    }else{
        //leemos el fichero
        printf("Voy a leer el saludo del fichero.\n\t");
        while (((nBytesLeidos = read(fd, buffer, 1))) > 0){
            printf("%1c",buffer[0]);
        }
        printf("\nMensaje leído del fichero.\n");
        close(fd);
        salida=1;
    }  
  }
  printf("/nFin del programa......\n");
  return salida;
}