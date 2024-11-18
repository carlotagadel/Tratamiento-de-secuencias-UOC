#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

#define NUM_MAX 100
#define FILAS_COLS 10
#define NUMS_FILA 2
#define ASCII 219
#define NUMSXCARTON 20

void inicializaMenosUno(int n, int arr[]) {
	for (int i = 0; i < n; i++) {
		arr[i] = -1;
	}
}

void generaCarton(int arr[]) {
	for (int fila = 0; fila < FILAS_COLS; fila++) { //recorremos todas las filas
		for (int j = 0; j < NUMS_FILA; j++) { //generamos dos numeros aleatorios por fila
			int columna = rand() % 5 + j * 5; //asignamos en una columna aleatoria, entre 0 y 4 o 5 y 9
			int indice = fila * FILAS_COLS + columna; //calculamos el indice en el que se guardara cada valor aleatorio
			arr[indice] = indice; //guardamos el valor en el array
		}
	}
}

int generaNumerosAleatorios(int arr[], int *recuento) {
	int num_aleatorio;
	bool repetido;
	do {
		num_aleatorio = rand() % NUM_MAX;
		repetido = false;
		for (int i = 0; i < *recuento; i++) {
			if (arr[i] == num_aleatorio) { //comprobamos que el numero no este repetido
				repetido = true;
				break; //salimos del bucle si esta repetido
			}
		}
	} while (repetido); //repetimos el bucle hasta que salga un numero nuevo

	arr[*recuento] = num_aleatorio; //guardamos el valor en el array
	(*recuento)++;
	return num_aleatorio;
}

int marcaAciertos(int arr[], int num, int* aciertos) {
	for (int i = 0; i < NUM_MAX; i++) {
		if (arr[i] == num) {
			arr[i] = ASCII;
			(*aciertos)++;
		}
	}

	return *aciertos;
}

void imprimeCarton(int arr[], int *aciertos) {
	for (int i = 0; i < FILAS_COLS; i++) { //lineas superiores
		printf(" ____");
	}
	printf("\n");

	for (int i = 0; i < NUM_MAX; i++) {
		if (i % FILAS_COLS == 0) { //filas
			printf("|");
		}

		if (arr[i] == ASCII) {
			printf(" %c  |", ASCII); //dejamos espacio para el ASCII
		}
		else if (arr[i] == -1) {
			printf("    |"); //espacio vacio si no hay numero
		}
		else {
			printf(" %2d |", arr[i]); //espacio para los numeros pendientes de recibir ASCII
		}

		if ((i + 1) % FILAS_COLS == 0) {
			printf("\n");
			for (int j = 0; j < FILAS_COLS; j++) {
				printf("|____"); //lineas inferiores
			}
			printf("|\n");
		}
	}
	printf("Numeros encontrados en el carton: %d\n", *aciertos);
	printf("\n");
}

int main() {
	srand(time(NULL)); //generador nums aleatorios
	int cartonJugador[NUM_MAX];
	int cartonMaquina[NUM_MAX];
	int numGenerados[NUM_MAX]; //cambiamos el array de 20 a 100 para generar numeros hasta que un carton las acierte todas
	int recuento = 0;
	bool ganador = false;
	int recuentoJugador = 0;
	int recuentoMaquina = 0;

	inicializaMenosUno(NUM_MAX, cartonJugador);
	inicializaMenosUno(NUM_MAX, cartonMaquina);

	generaCarton(cartonJugador);
	generaCarton(cartonMaquina);

	while (!ganador) {
		int num_aleatorio = generaNumerosAleatorios(numGenerados, &recuento);

		recuentoJugador = marcaAciertos(cartonJugador, num_aleatorio, &recuentoJugador);
		recuentoMaquina = marcaAciertos(cartonMaquina, num_aleatorio, &recuentoMaquina);
		

		system("cls"); //limpiamos la pantalla por cada vuelta

		printf("Ha salido el %d\n", num_aleatorio);

		printf("\n");
		printf("Mi carton:\n");
		imprimeCarton(cartonJugador, &recuentoJugador);
		printf("Tu carton:\n");
		imprimeCarton(cartonMaquina, &recuentoMaquina);
	

		printf("Numeros que han salido: \n");
		for (int i = 0; i < 10; i++) {
			printf(" ____");
		}
		printf("\n");

		for (int i = 0; i < recuento; i++) {
			if (i % 10 == 0) {
				printf("|");
			}

			printf(" %2d |", numGenerados[i]);

			if ((i + 1) % 10 == 0) {
				printf("\n");
				for (int j = 0; j < 10; j++) {
					printf("|____");
				}
				printf("|\n");
			}
		}
		printf("\n");

		if (recuentoJugador == NUMSXCARTON || recuentoMaquina == NUMSXCARTON) { //comprobamos si uno de los dos cartones ha llegado a los 20 nums acertados
			printf("\n");
			ganador = true;
			if (recuentoJugador == NUMSXCARTON) { //mensaje segun quien haya ganado
				printf("\n");
				printf("He ganado yo!\n");
			}
			else {
				printf("Has ganado tu!\n");
			}
		}

		printf("\n");

		Sleep(1000); //pausa entre impresion e impresion
	}

	return 0;
}
