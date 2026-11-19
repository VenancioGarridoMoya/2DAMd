#include <string.h>     /* Función strlen() */
#include <fcntl.h>      /* Modos de apertura y función open()*/
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>   
#include <sys/stat.h> 
#include <sys/types.h> 

 
int main(int argc, char *argv[]){
 
  /* Variables */
  int fp, nBytesLeidos, salida=0;
  char buffer[10];
  struct stat estructura;
  const char *nombreArchivo = "FIFO2";
  if (stat(nombreArchivo, &estructura) == -1) { // para comprobar si el archivo existe (podría ser un archivo normal))
        printf("La pipe '%s'  NO existe, voy a crearla.\n", nombreArchivo);
        if ((mkfifo ("FIFO2",S_IFIFO|0666)==-1)){
           salida=-1;
        } else{
            printf("La pipe '%s' se ha creado con éxito.\n", nombreArchivo);
        }
  } else {
        if (!S_ISFIFO(estructura.st_mode)) {
            printf("Error: '%s' existe pero no es una pipe.\n", nombreArchivo);
            salida=-1;
        } else{
            printf("La pipe '%s' ya existe.\n", nombreArchivo);
        }
 } 
 if (salida==0){
    printf("pipelee con PID: %d.\n", getpid());
    fp = open(nombreArchivo, 0); // se bloquea hasta que otro proceso abra la pipe para escritura
    printf("Se abre la pipe '%s' para lectura.\n", nombreArchivo);
    if (fp==-1){
      printf("Error en apertura de la pipe en modo lectura");
      salida = -1;
    } else {
      while(1){
        while (((nBytesLeidos = read(fp, buffer, 1))) > 0){ //leemos caracter a caracter
            printf("%1c",buffer[0]);
        }
      }
      close(fp);   
    }
  }  
  printf("/nFin del programa pipelee......\n");
  return salida;
}