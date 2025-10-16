#include <stdio.h>

#define MAX_LEN 100

int main() {
    char cadena[MAX_LEN];

    printf("Introduce una cadena: ");
    fgets(cadena, MAX_LEN, stdin);

    printf("La cadena introducida es: %s", cadena);
    printf("Fin del programa.\n");

    return 0;
}