#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static double factorial(int n) {
	double resultado = 1.0;

	for (int valor = 2; valor <= n; valor++) {
		resultado *= valor;
	}

	return resultado;
}

int main(void) {
	int fd[2]={0, 0};
	int x = 0;
	int limite = 0;
	int salida = 0;
    double valor_factorial = 0.0;
	long double suma = 0.0L;
	pid_t pid = -1;
	const char *quienSoy = "Padre";

	printf("Introduce el valor entero de x: ");
	if (scanf("%d", &x) != 1) {
		printf("El valor de x debe ser un entero.\n");
		salida = -1;
	} else {
		printf("Introduce N (5 < N <= 10): ");
		if (scanf("%d", &limite) != 1 || limite <= 5 || limite > 10) {
			printf("Error: N debe ser un entero mayor que 5 y menor o igual que 10.\n");
			salida = -2;
		} else {
			fflush(stdout);
			if (pipe(fd) == -1) {
				printf("Error al crear el pipe");
				salida = -3;
			} else {
				pid = fork();
				switch (pid) {
				case -1: 
					printf("Error al crear el proceso hijo");
					salida = -4;
					break;
				case 0: // Proceso hijo
					quienSoy = "Hijo";
					close(fd[0]);
					for (int n = 0; n <= limite; n++) {
						valor_factorial = factorial(n);
						printf("\tProceso hijo: %d! = %.0f\n", n, valor_factorial);
						fflush(stdout);
						write(fd[1], &valor_factorial, sizeof(valor_factorial));
					}
					close(fd[1]);
					fflush(stdout);
					break;;
				default: {  // Proceso padre
					close(fd[1]);
					fd[1] = -1;
                    double potencia = 1.0;
                    for (int n = 0; n <= limite; n++) {
                        double valor_factorial = 0.0;
                        read(fd[0], &valor_factorial, sizeof(valor_factorial));
                        double parcial = potencia / valor_factorial;
                        suma += parcial;
                        printf("Proceso padre: x^%d/%d! = %.10f; Suma parcial = %.10Lf\n",
                                n, n, parcial, suma);
                        potencia *= x;
                    }
					}
					close(fd[0]);
					fd[0] = -1;
					wait(NULL); // Espera a que el proceso hijo termine
					printf("e^%d aproximado con N=%d: %.10Lf\n", x, limite, suma);
					printf("e^%d con exp(): %.10f\n", x, exp((double) x));
					break;
				}
			}
		}
	}
	printf("Fin del proceso %s.\n", quienSoy);
	return salida;
}
