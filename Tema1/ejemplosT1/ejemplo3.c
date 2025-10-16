#include <stdio.h>

int main() {
    int n, i;
    unsigned long long factorial = 1;

    printf("Introduce un numero entero: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("El factorial no esta definido para numeros negativos.\n");
    } else {
        for (i = 1; i <= n; ++i) {
            factorial *= i;
        }
        printf("El factorial de %d es %llu\n", n, factorial);
    }
    printf("Fin del programa.\n");

    return 0;
}