#include <stdio.h>

void cambiar (int *a, int *b) {
	int temp = *b;
	*b = *a;
	*a = temp;
}

void imprimir_arr (int *arreglo, int elementos) {
	for (int i = 0; i < elementos; i++) {
		printf("%d ", *(arreglo + i));
	}
    	printf ("\n");
}

void ordenar (int *ptr, int elementos) {
        for (int i = 0; i < elementos; i++) {
                for (int j = 0; j < elementos; j++) {
                        if (*(ptr + j) > *(ptr + i)) {
                                cambiar (ptr + j, ptr + i);
                        }
                }
        }
}


void mat_a_arr (int *ptr, int *ptr_arr, int elementos) {

	for (int i = 0; i < elementos; i++) {
		*(ptr_arr + i) = *(ptr + i);
	}
}

int main () {
        int matriz [3][3] = {
                {4, 15, 9},
                {7, 6, 1},
                {12, 6, 3}
        };
	int elementos_matriz = sizeof (matriz) / sizeof (matriz [0][0]);
	int arreglo_matriz [elementos_matriz];
	
	mat_a_arr (&matriz [0][0], &arreglo_matriz [0], elementos_matriz);
	imprimir_arr (&arreglo_matriz [0], elementos_matriz);
	
	ordenar (&arreglo_matriz [0], elementos_matriz);
	imprimir_arr (&arreglo_matriz [0], elementos_matriz);
}
