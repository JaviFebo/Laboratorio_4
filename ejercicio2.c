#include <stdio.h>
#include <string.h>
#include <ctype.h>

int posicion_signo (char *palabra) {
	int longitud_str = strlen (palabra);

	for (int i = 0; i < longitud_str; i++) {
		if (ispunct (palabra [i])) {
			return i;
		}
	}	
	return -1;
}

void quitar_signo (char *palabra, int posicion) {
	int longitud_str = strlen (palabra);
	
	if (posicion == -1) {
		return;
	}

	for (int i = posicion; i < longitud_str; i++) {
		palabra [i] = palabra [i + 1];
	}
}

void agregar_espacio_blanco (FILE *archivo_entrada, FILE *archivo_salida) {
	int c = fgetc (archivo_entrada);

	if (c == '\n') {
		fputc ('\n', archivo_salida);
	}

	else if (c == ' ') {
		fputc (' ', archivo_salida);
	}

	if (c != EOF && c != '\n' && c != ' ') {
		ungetc(c, archivo_entrada);
	}
}

void reemplazar_palabra (char *nombre_archivo, char *palabra_buscar, char *palabra_reemplazo) {
	FILE *archivo_entrada = fopen (nombre_archivo, "r");
	FILE *archivo_salida = fopen ("archivo_salida.txt", "w");
	
	char palabra [100];
	char palabra_limpia [100];
	int contador = 0;

	while (fscanf (archivo_entrada, "%99s", palabra) == 1) {
		int posicion = posicion_signo(palabra);
		
		strcpy (palabra_limpia, palabra);
		quitar_signo (palabra_limpia, posicion);
		
		if (strcmp (palabra_limpia, palabra_buscar) == 0) {
			fputs (palabra_reemplazo, archivo_salida);
			contador++;
		}
		
		else {
			fputs (palabra, archivo_salida);
		}
		
		agregar_espacio_blanco (archivo_entrada, archivo_salida);
        }
	
	printf ("Palabra %s encontrada %d veces\n", palabra_buscar, contador);
	printf ("Palabra %s reemplazada por %s\n", palabra_buscar, palabra_reemplazo);

	fclose (archivo_salida);
	fclose (archivo_entrada);
}

int main (int argc, char *argv []) {
	char *nombre_archivo = argv [1];
	char *palabra_buscar = argv [2];
	char *palabra_reemplazo = argv [3];
	
	reemplazar_palabra (nombre_archivo, palabra_buscar, palabra_reemplazo);

	return 0;
}
