#include <stdio.h>

void cambiar (int *a, int *b) { //Función que cambia el valor de dos variables
	int temp = *b;
	*b = *a;
	*a = temp;
}

void imprimir_arr (int *ptr_arr, int elementos) { //Función que imprime un arreglo
	for (int i = 0; i < elementos; i++) {
		printf("%d ", *(ptr_arr + i));
	}
    	printf ("\n");
}

void imprimir_mat (int *ptr_mat, int filas, int columnas) { //Función que imprime una matriz
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			printf ("%d ", *(ptr_mat + j + i * columnas)); //Se imprime el elemento [i][j] de la matriz
		}
		printf ("\n");
	}
}

void ordenar (int *ptr, int elementos) { //Función que ordena un arreglo de menor a mayor
        for (int i = 0; i < elementos; i++) {
                for (int j = 0; j < elementos; j++) {
                        if (*(ptr + j) > *(ptr + i)) { //Si el elemento j es mayor al elemento i
                                cambiar (ptr + j, ptr + i); //Se cambia ele elemento j por el i
                        }
                }
        }
}


void mat_a_arr (int *ptr_mat, int *ptr_arr, int elementos) { //Función que transforma una matriz en un arreglo unidimensional
	for (int i = 0; i < elementos; i++) {
		*(ptr_arr + i) = *(ptr_mat + i); 
	}
}

void arr_a_mat (int *ptr_mat, int *ptr_arr, int elementos) { //Función que transforma un arreglo unidimensional a una matriz
	for (int i = 0; i < elementos; i++) {
		*(ptr_mat + i) = *(ptr_arr + i);
	}
}

int main () {
        int matriz [3][3] = {
                {4, 15, 9},
                {7, 6, 1},
                {12, 6, 3}
        };
	int elementos_matriz = sizeof (matriz) / sizeof (matriz [0][0]); //Tamaño de matriz entre tamaño de un solo elemento
	int filas_matriz = sizeof (matriz) / sizeof (matriz [0]); //Tamaño de matriz entre tamaño de una sola fila
	int columnas_matriz = sizeof (matriz [0]) / sizeof (matriz [0][0]); //Tamaño de una sola fila entre tamaño de un solo elemento
	int arreglo_matriz [elementos_matriz];
	
	printf ("Matriz original: \n");	
	imprimir_mat (&matriz [0][0], filas_matriz, columnas_matriz);
	
	printf ("\nArreglo unidimensional: \n");
	mat_a_arr (&matriz [0][0], &arreglo_matriz [0], elementos_matriz);
	imprimir_arr (&arreglo_matriz [0], elementos_matriz);
	
	printf ("\nArreglo unidimensional ordenado: \n");
	ordenar (&arreglo_matriz [0], elementos_matriz);
	imprimir_arr (&arreglo_matriz [0], elementos_matriz);
	
	printf ("\nMatriz ordenada: \n");
	arr_a_mat (&matriz [0][0], &arreglo_matriz [0], elementos_matriz);
	imprimir_mat (&matriz [0][0], filas_matriz, columnas_matriz);
}
