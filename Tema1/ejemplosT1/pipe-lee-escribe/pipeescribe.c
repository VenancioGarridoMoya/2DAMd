#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(){
    int salida=0;
    int fp;
    const char *nombreArchivo = "FIFO2";
    char *mensaje = "\n\t\t***Este mensaje se envió desde pipeescribe***\n";

    FILE *archivo = fopen(nombreArchivo, "r"); // para comprobar si el archivo existe (podría ser un archivo normal))
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
            printf("Error al abrir la pipe pipe '%s' para escritura.\n", nombreArchivo);
            salida=-1;
        }
        printf("Se mandan datos a la pipe....\n");
        write(fp,mensaje, strlen(mensaje));
        close (fp);
        printf("Datos enviados a la pipe '%s' con éxito.\n", nombreArchivo);
    }
    return salida;
    
}