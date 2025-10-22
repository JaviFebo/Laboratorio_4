#include <stdio.h>
#include <string.h>
#include <ctype.h>

int posicion_signo (char *palabra) {
	int longitud_str = strlen (palabra);

	for (int i = 0; i < longitud_str; i++) {
		if (ispunct (palabra [i])) {
			return i; //Si el caracter es un signo de puntuación devuelve la posición del caracter
		}
	}	
	return -1; //Si no hay signos de puntuación devuelve -1
}

void quitar_signo (char *palabra, int posicion) {
	int longitud_str = strlen (palabra);
	
	if (posicion == -1) {
		return; //Si la posición es -1 sale de la función
	}
	
	for (int i = posicion; i < longitud_str; i++) {
		palabra [i] = palabra [i + 1]; //Mueve los caractéres hacia la izquierda en la posición del signo de puntuación
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
		printf ("Error no se pudieron abrir los archivos de entrada o salida\n");
		return;
	}
	
	char palabra [100];
	char palabra_limpia [100];
	int contador = 0;
	
	while (fscanf (archivo_entrada, "%99s", palabra) == 1) {
		int posicion = posicion_signo(palabra); 
		
		strcpy (palabra_limpia, palabra); 
		quitar_signo (palabra_limpia, posicion); 
		
		if (strcmp (palabra_limpia, palabra_buscar) == 0) {
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
		printf ("Error argumentos inválidos\n");
		return;
	}
		
	char *nombre_archivo = argv [1];
	char *palabra_buscar = argv [2];
	char *palabra_reemplazo = argv [3];
	
	reemplazar_palabra (nombre_archivo, palabra_buscar, palabra_reemplazo);
	
	return 0;
}
