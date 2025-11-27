#include <string.h>     /* Función strlen() */
#include <fcntl.h>      /* Modos de apertura y función open()*/
#include <stdlib.h>
#include <stdio.h> 
 
int main(int argc, char *argv[]){
 
  /* Variables */
  int fp, nBytesLeidos, salida;
  char buffer[10];
  const char *nombreArchivo = "FIFO2";
  
  fp = open(nombreArchivo, 0);
  if (fp==-1){
    printf("Error en apertura de la pipe en modo lectura");
    salida = -1;
  } else {
        //leemos de la pipe
        printf("Voy a leer de la pipe de modo permanente.\n\t");
        while (1){
            fp = open(nombreArchivo, 0);
            while (((nBytesLeidos = read(fp, buffer, 1))) > 0){
                printf("%1c",buffer[0]);
            }
            close(fp);
        }
        
        printf("\nSe han leído todos los mensajes.\n");
        close(fp);
        salida=1;
 }  
  printf("/nFin del programa......\n");
  return salida;
}