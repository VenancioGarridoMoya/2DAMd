#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(){
    int salida=0;
    int fp;
    const char *nombreArchivo = "FIFO2";
    char *mensaje = "Este mensaje se envió desde pipeescribe\n";

    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("La pipe '%s'  NO existe, voy a crearla.\n", nombreArchivo);
        if ((mkfifo ("FIFO2",S_IFIFO|0666)==-1)){
           salida=-1;
        } else{
            printf("La pipe '%s' se ha creado con éxito.\n", nombreArchivo);
        }
    } else {
        printf("La pipe '%s' existe.\n", nombreArchivo);
        fclose(archivo); // Cierra el archivo si se abrió correctamente
    }
    if (salida==0){
        fp = open(nombreArchivo,1);
         if (fp ==-1){
            printf("Error al abrir la pipe pipe '%s'.\n", nombreArchivo);
            salida=-1;
        }
        printf("Mando datos a la pipe....");
        write(fp,mensaje, strlen(mensaje));
    }
    return salida;
    
}