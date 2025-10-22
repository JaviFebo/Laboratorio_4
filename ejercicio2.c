#include <stdio.h>
#include <string.h>
#include <ctype.h>

void posicion_signo (char *palabra, int *ptr_posiciones) {
	int longitud_str = strlen (palabra);
	
	if (ispunct (palabra [0])) {
		*ptr_posiciones = 1;
	}
	
	if (ispunct (palabra [longitud_str - 1])) {
		*(ptr_posiciones + 1) = 1;
	}
}

void quitar_signo (char *palabra, int *ptr_posiciones) {
	int longitud_str = strlen (palabra);

	if ( *ptr_posiciones == 1) {
		for (int i = 0; i < longitud_str; i++) {
		       palabra [i] = palabra [i + 1];
		}
		palabra [longitud_str - 1] = '\0';
	}

 	if (*(ptr_posiciones + 1) == 1) {
		palabra [strlen (palabra) - 1] = '\0';
	}		
}

void agregar_espacio_blanco (FILE *archivo_entrada, FILE *archivo_salida) {
	int c = fgetc (archivo_entrada);
	
	if (c == '\n') {
		fputc ('\n', archivo_salida); //Si lee un salto de línea en la entrada lo pone en la salida
	}
	
	else if (c == ' ') {
		fputc (' ', archivo_salida); //Si lee un espacio en la entrada lo pone en la salida
	}
	
	if (c != EOF && c != '\n' && c != ' ') {
		ungetc(c, archivo_entrada);
	}
}

void reemplazar_palabra (char *nombre_archivo, char *palabra_buscar, char *palabra_reemplazo) {
	FILE *archivo_entrada = fopen (nombre_archivo, "r");
	FILE *archivo_salida = fopen ("archivo_salida.txt", "w");
	
	if (!archivo_entrada || !archivo_salida) {
		printf ("Error no se pudieron abrir los archivos de entrada o salida");
	}
	
	char palabra [100];
	char palabra_limpia [100];
	int contador = 0;
	
	while (fscanf (archivo_entrada, "%99s", palabra) == 1) {
		int posiciones [2] = {0, 0};
			
		strcpy (palabra_limpia, palabra); 
		posicion_signo (palabra_limpia, &posiciones [0]);
		quitar_signo (palabra_limpia, &posiciones [0]); 
		printf ("%s\n", palabra_limpia);	
		if (strcasecmp (palabra_limpia, palabra_buscar) == 0) {
			fputs (palabra_reemplazo, archivo_salida); //Si la palabra sin signos es igual a la buscada de agrega el reemplazo en la salida
			contador++;
		}
		
		else {
			fputs (palabra, archivo_salida); //Si la palabra sin signos no es igual a la buscada se pasa directamente a la salida
		}
		
		agregar_espacio_blanco (archivo_entrada, archivo_salida);
        }
	
	printf ("Palabra %s encontrada %d veces\n", palabra_buscar, contador);
	printf ("Palabra %s reemplazada por %s\n", palabra_buscar, palabra_reemplazo);
	
	fclose (archivo_salida);
	fclose (archivo_entrada);
}

int main (int argc, char *argv []) {
	if (argc != 4) {
		printf ("Error argumentos inválidos");
	}
		
	char *nombre_archivo = argv [1];
	char *palabra_buscar = argv [2];
	char *palabra_reemplazo = argv [3];
	
	reemplazar_palabra (nombre_archivo, palabra_buscar, palabra_reemplazo);
	
	return 0;
}
