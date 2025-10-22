#include <stdio.h>
#include <string.h>

void buscar_reemplazar (char *nombre_archivo, char *palabra_buscar, char *palabra_reemplazo) {
	FILE *archivo_entrada = fopen (nombre_archivo, "r");
	FILE *archivo_salida = fopen ("archivo_salida.txt", "w");

	char palabra [100];
        while (fscanf (archivo_entrada, "%99s", palabra) == 1) {
                if (strcmp (palabra, palabra_buscar) == 0) {
                       fputs (palabra_reemplazo, archivo_salida);
		       fputs (" ", archivo_salida);
                }

		else {
			fputs (palabra, archivo_salida);
			fputs (" ", archivo_salida);
		}
        }
	
	fclose (archivo_salida);
	fclose (archivo_entrada);
}

int main (int argc, char *argv []) {
	char *nombre_archivo = argv [1];
	char *palabra_buscar = argv [2];
	char *palabra_reemplazo = argv [3];
	
	buscar_reemplazar (nombre_archivo, palabra_buscar, palabra_reemplazo);
	return 0;
}
