#include <stdio.h>

void arr_uni (int *ptr, int *ptr_arr, int elementos) {

	for (int i = 0; i < elementos; i++) {
		*(ptr_arr + i) = *(ptr + i);
	}
}

int main () {
        int matriz [3][3] = {
                {4, 1, 8},
                {2, 6, 3},
                {9, 7, 5}
        };
	int elementos = sizeof (matriz) / sizeof (matriz [0][0]);
	int arreglo [elementos];
	
	arr_uni (&matriz [0][0], &arreglo [0], elementos);
}
