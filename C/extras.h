/*
	extras.h
	Autor: David Yaxkin Sánchez Neri
	Biblioteca que contiene utilidades extra:
	- Limpiador de pantalla (clear screen)
	- Validaciones de tipo
	- Conversión de tipo
	- Formato de impresión
	- Pausa
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
	void clearScreen() {
		system("cls");
	} 
#elif __linux__
	void clearScreen() {
		system("clear");
	} 
#endif 

enum boolean{false, true};

enum boolean validarEntero(char buffer[]);
enum boolean validarFlotante(char buffer[]);
char* enteroACadena(int numero);
char* flotanteACadena(float numero);
void imprimirDatoCadena(char cadena[]);
void imprimirDatoEntero(int numero);
void imprimirDatoFlotante(float numero);

void pausa();

enum boolean validarEntero(char buffer[]) {
	int i = 0;
	while (i < strlen(buffer)) {
		if (!isdigit(buffer[i])) {
			printf("Dato inválido. Ingrese un número entero positivo.\n");
			return false;
		}
		i++;
	}
	return true;
}

enum boolean validarFlotante(char buffer[]) {
	int i = 0;
	if (buffer[i] == '.' && strlen(buffer) == 1) {
		printf("Dato inválido. Ingrese un número positivo.\n");
		return false;
	}
	while (i < strlen(buffer)) {
		if (!isdigit(buffer[i]) && buffer[i] != '.') {
			printf("Dato inválido. Ingrese un número positivo.\n");
			return false;
		}
		i++;
	}
	return true;
}

char* enteroACadena(int numero){
	char* cadena = (char*)calloc(10,sizeof(char));
	sprintf(cadena,"%i",numero);
	return cadena;
}

char* flotanteACadena(float numero){
	char* cadena = (char*)calloc(10,sizeof(char));
	sprintf(cadena,"%.2f",numero);
	return cadena;
}

void imprimirDatoCadena(char cadena[]) {
	int tamano_campo = 32;
	int num_espacios = tamano_campo - strlen(cadena);
	int i;
	printf("%s",cadena);
	for(i = 0; i < num_espacios-1; i++) {
		printf(" ");
	}
}

void imprimirDatoEntero(int numero) {
	int tamano_campo = 10;
	char* cadena = enteroACadena(numero);
	int num_espacios = tamano_campo - strlen(cadena);
	int i;
	for(i = 0; i < num_espacios-1; i++) {
		printf(" ");
	}
	printf("%s",cadena);
}

void imprimirDatoFlotante(float numero) {
	int tamano_campo = 10;
	char* cadena = flotanteACadena(numero);
	int num_espacios = tamano_campo - strlen(cadena);
	int i;
	for(i = 0; i < num_espacios-1; i++) {
		printf(" ");
	}
	printf("%s",cadena);
}

void pausa() {
	printf("Presione Enter para continuar...");
	getchar();
	getchar();
}