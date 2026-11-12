#include <string.h>     /* Función strlen() */
#include <fcntl.h>      /* Modos de apertura y función open()*/
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>    
 
int main(int argc, char *argv[]){
 
  /* Variables */
  int fp, nBytesLeidos, salida=0;
  char buffer[10];
  const char *nombreArchivo = "FIFO2";
  int seguirLeyendo = 1;
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
  printf("/nFin del programa pipelee......\n");
  return salida;
}