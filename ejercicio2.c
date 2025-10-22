#include <stdio.h>
#include <string.h>
#include <ctype.h>

void posicion_signo (char *palabra, int *ptr_posiciones, char *signos) {
	int longitud_str = strlen (palabra);
	
	if (ispunct (palabra [0])) {
		*ptr_posiciones = 1; //Si el primer elemento del string es un signo de puntiación guarda 1 en el primer espacio del arreglo
		signos [0] = palabra [0];
	}
	
	if (ispunct (palabra [longitud_str - 1])) {
		*(ptr_posiciones + 1) = 1; //Si el último elemento del string es un signo de puntiación guarda 1 en el último espacio del arreglo
		signos [1] = palabra [longitud_str - 1] ;
	}
}

void quitar_signo (char *palabra, int *ptr_posiciones) {
	int longitud_str = strlen (palabra);

	if ( *ptr_posiciones == 1) {
		for (int i = 0; i < longitud_str; i++) {
		       palabra [i] = palabra [i + 1]; //Si el primer espacio del arreglo es 1, borra el primer elemento del string
		}
		palabra [longitud_str - 1] = '\0';
	}

 	if (*(ptr_posiciones + 1) == 1) {
		palabra [strlen (palabra) - 1] = '\0'; //Si el último espacio del arreglo es 1, borra el último elemento del string
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
		int posiciones_signos [2] = {0, 0};
		char signos [2];
			
		strcpy (palabra_limpia, palabra); 
		posicion_signo (palabra_limpia, &posiciones_signos [0], signos); //Guarda las posiciones de los signos de puntuación en el arreglo posiciones_signos
		quitar_signo (palabra_limpia, &posiciones_signos [0]); //Quita los signos basándose en las posiciones guardadas en el arreglo posiciones_signos
		
		if (strcasecmp (palabra_limpia, palabra_buscar) == 0) {
			if (posiciones_signos [0] == 1) {
				fputc (signos [0], archivo_salida);
			}

			fputs (palabra_reemplazo, archivo_salida); //Si la palabra sin signos es igual a la buscada de agrega el reemplazo en la salida
			
			if (posiciones_signos [1] == 1) {
				fputc (signos [1], archivo_salida);
                        }

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
		return 1;
	}
		
	char *nombre_archivo = argv [1];
	char *palabra_buscar = argv [2];
	char *palabra_reemplazo = argv [3];
	
	reemplazar_palabra (nombre_archivo, palabra_buscar, palabra_reemplazo);
	
	return 0;
}
