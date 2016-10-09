/*
	disco.h
	Autor: David Yaxkin Sánchez Neri
	Biblioteca que contiene la estructura básica de un Disco
	y las funciones en las que se ve involucrado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "extras.h"

//enum boolean{false,true};

typedef struct Disco {
	char nombre_disco[24];
	char artista[24];
	float precio;
	int anio_lanzamiento;
	int num_compras;
	struct Disco* siguiente;
}Disco;

Disco* lista_discos_inicio = NULL;
Disco* lista_discos_final = NULL;
int num_discos = 0;

Disco* crearDisco(char nombre_disco[], char artista[], float precio, int anio_lanzamiento, int num_compras);
enum boolean listaDiscosVacia();
void agregarDisco(Disco* disco);
void modificarDisco(char nombre_disco[]);
Disco* removerDisco(char nombre_disco[]);

enum boolean discoEnLista(char nombre_disco[]);
void registrarDisco();
void mostrarDiscos();
void imprimirDisco(Disco* disco);
void copiarDisco(Disco* destino, Disco* origen);
void ordenarDiscosNombre();
void ordenarDiscosArtista();
void ordenarDiscosPrecio();
void ordenarDiscosAnio();
void ordenarDiscosNumCompras();
void buscarDiscoNombre(char nombre_disco[]);
void buscarDiscoArtista(char artista[]);
void buscarDiscoAnio(int anio);
void buscarDiscoPrecioMenor(float precio);
void buscarDiscoPrecioMayor(float precio);
void buscarDiscoPrecioIgual(float precio);
void cargarInventario();
void leerArchivoDisco(char nombre_archivo[]);
void guardarInventario();
void escribirArchivoDisco(char nombre_archivo[],Disco* disco);
void eliminarArchivoDisco(Disco* disco);
void renombrarArchivoDisco(char nombre_antiguo[],char nombre_nuevo[]);

Disco* crearDisco(char nombre_disco[], char artista[], float precio, int anio_lanzamiento, int num_compras) {
	Disco* nuevo = (Disco*)malloc(sizeof(Disco));
	strcpy(nuevo->nombre_disco,nombre_disco);
	strcpy(nuevo->artista,artista);
	nuevo->precio = precio;
	nuevo->anio_lanzamiento = anio_lanzamiento;
	nuevo->num_compras = num_compras;
	nuevo->siguiente = NULL;
	return nuevo;
}

enum boolean listaDiscosVacia() {
	if(lista_discos_inicio == NULL && lista_discos_final == NULL) {
		return true;
	}
	else {
		return false;
	}
}

void agregarDisco(Disco* disco) {
	if(listaDiscosVacia()) {
		lista_discos_inicio = disco;
	}
	else {
		lista_discos_final->siguiente = disco;
	}
	lista_discos_final = disco;
	num_discos++;
}

void modificarDisco(char nombre_disco[]) {
	if(listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		int opcion;
		char buffer[24]={'\0'};
		Disco* scout = lista_discos_inicio;
		while( strcmp(scout->nombre_disco,nombre_disco) != 0 ) {
			scout = scout->siguiente;
			if (scout == NULL) {
				printf("Disco \"%s\" no encontrado.\n",nombre_disco);
				return;
			}
		}
		char backup[24];
		strcpy(backup,scout->nombre_disco);
		printf("Ingrese nuevos datos del disco:\n");
		printf("Artista: ");
		scanf(" %[^\n]",scout->artista);
		printf("Nombre del disco: ");
		scanf(" %[^\n]",scout->nombre_disco);
		do {
			printf("Precio: ");
			scanf("%s",buffer);
		} while (!validarFlotante(buffer));
		scout->precio = atof(buffer);
		do {
			printf("Año de lanzamiento: ");
			scanf("%s",buffer);
		} while (!validarEntero(buffer));
		scout->anio_lanzamiento = atoi(buffer);
		renombrarArchivoDisco(backup,scout->nombre_disco);
		printf("Modificación finalizada.\n");
	}
}

Disco* removerDisco(char nombre_disco[]) {
	if(listaDiscosVacia()) {
		return (Disco*)NULL;
	}
	Disco* aux = lista_discos_inicio;
	if (lista_discos_inicio == lista_discos_final && strcmp(aux->nombre_disco,nombre_disco) == 0 ) {
		lista_discos_inicio = NULL;
		lista_discos_final = NULL;
		eliminarArchivoDisco(aux);
		num_discos--;
		return aux;
	}
	else if (strcmp(aux->nombre_disco,nombre_disco) == 0) {
		printf("Entre aqui\n");
		lista_discos_inicio = lista_discos_inicio->siguiente;
		aux->siguiente = NULL;
		eliminarArchivoDisco(aux);
		num_discos--;
		return aux;
	}
	else {
		Disco* scout = lista_discos_inicio;
		while(strcmp(scout->nombre_disco,nombre_disco) != 0) {
			scout = scout->siguiente;
			if(scout == NULL) {
				return NULL;
			}
		}
		while(aux->siguiente != scout) {
			aux = aux->siguiente;
		}
		aux->siguiente = scout->siguiente;
		scout->siguiente = NULL;
		eliminarArchivoDisco(scout);
		num_discos--;
		return scout;
	}
}

enum boolean discoEnLista(char nombre_disco[]) {
	Disco* aux = lista_discos_inicio;
	while(aux != NULL && strcmp(aux->nombre_disco,nombre_disco) != 0) {
		aux = aux->siguiente;
	}
	if (aux != NULL && strcmp(aux->nombre_disco,nombre_disco) == 0) {
		return true;
	}
	else {
		return false;
	}
}

void registrarDisco() {
	char nombre_disco[24];
	printf("Ingrese nombre del disco: ");
	scanf(" %[^\n]",nombre_disco);
	if (discoEnLista(nombre_disco)) {
		printf("\"%s\" ya se encuentra en la tienda.\n", nombre_disco);
		return;
	}
	char artista[24];
	float precio;
	int anio_lanzamiento;
	char buffer[24];
	printf("Ingrese artista: ");
	scanf(" %[^\n]",artista);
	do {
		printf("Precio: ");
		scanf("%s",buffer);
	} while (!validarFlotante(buffer));
	precio = atof(buffer);
	do {
		printf("Año de lanzamiento: ");
		scanf("%s",buffer);
	} while (!validarEntero(buffer));
	anio_lanzamiento = atoi(buffer);
	agregarDisco(crearDisco(nombre_disco,artista,precio,anio_lanzamiento,0));
	printf("Disco agregado.\n");
}

void mostrarDiscos() {
	if(listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		Disco* aux = lista_discos_inicio;
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		printf("| Artista\t\t\t | Nombre del Disco\t\t  | Precio    | Año       | Comprados |\n");
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		while(aux != NULL) {
			imprimirDisco(aux);
			aux = aux->siguiente;
		}
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
	}
}

void imprimirDisco(Disco* disco) {
	printf("| ");
	imprimirDatoCadena(disco->artista);
	printf("| ");
	imprimirDatoCadena(disco->nombre_disco);
	printf("| ");
	imprimirDatoFlotante(disco->precio);
	printf(" | ");
	imprimirDatoEntero(disco->anio_lanzamiento);
	printf(" | ");
	imprimirDatoEntero(disco->num_compras);
	printf(" |");
	printf("\n");
}

void copiarDisco(Disco* destino, Disco* origen) {
	strcpy(destino->nombre_disco,origen->nombre_disco);
	strcpy(destino->artista,origen->artista);
	destino->precio = origen->precio;
	destino->anio_lanzamiento = origen->anio_lanzamiento;
	destino->num_compras = origen->num_compras;
}

void ordenarDiscosNombre() {
	enum boolean lista_ordenada;
	Disco* aux = NULL;
	Disco* menor_ordenado = NULL;
	Disco* backup = (Disco*)malloc(sizeof(Disco));
	if (listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		do {
			lista_ordenada = true;
			aux = lista_discos_inicio;
			while (aux->siguiente != menor_ordenado) {
				if (strcmp(aux->nombre_disco,aux->siguiente->nombre_disco) > 0) { 
					//backup->dato = aux->dato;
					copiarDisco(backup,aux);
					//aux->dato = aux->siguiente->dato;
					copiarDisco(aux,aux->siguiente);
					//aux->siguiente->dato = backup->dato;
					copiarDisco(aux->siguiente,backup);
					lista_ordenada = false;
				}
				aux = aux->siguiente;
			}
			menor_ordenado = aux;
		} while (lista_ordenada == false);
	}
	printf("Lista ordenada.\n");
}

void ordenarDiscosArtista() {
	enum boolean lista_ordenada;
	Disco* aux = NULL;
	Disco* menor_ordenado = NULL;
	Disco* backup = (Disco*)malloc(sizeof(Disco));
	if (listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		do {
			lista_ordenada = true;
			aux = lista_discos_inicio;
			while (aux->siguiente != menor_ordenado) {
				if (strcmp(aux->artista,aux->siguiente->artista) > 0) { 
					//backup->dato = aux->dato;
					copiarDisco(backup,aux);
					//aux->dato = aux->siguiente->dato;
					copiarDisco(aux,aux->siguiente);
					//aux->siguiente->dato = backup->dato;
					copiarDisco(aux->siguiente,backup);
					lista_ordenada = false;
				}
				aux = aux->siguiente;
			}
			menor_ordenado = aux;
		} while (lista_ordenada == false);
	}
	printf("Lista ordenada.\n");
}

void ordenarDiscosPrecio() {
	enum boolean lista_ordenada;
	Disco* aux = NULL;
	Disco* menor_ordenado = NULL;
	Disco* backup = (Disco*)malloc(sizeof(Disco));
	if (listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		do {
			lista_ordenada = true;
			aux = lista_discos_inicio;
			while (aux->siguiente != menor_ordenado) {
				if (aux->precio > aux->siguiente->precio) { 
					//backup->dato = aux->dato;
					copiarDisco(backup,aux);
					//aux->dato = aux->siguiente->dato;
					copiarDisco(aux,aux->siguiente);
					//aux->siguiente->dato = backup->dato;
					copiarDisco(aux->siguiente,backup);
					lista_ordenada = false;
				}
				aux = aux->siguiente;
			}
			menor_ordenado = aux;
		} while (lista_ordenada == false);
	}
	printf("Lista ordenada.\n");
}

void ordenarDiscosAnio() {
	enum boolean lista_ordenada;
	Disco* aux = NULL;
	Disco* menor_ordenado = NULL;
	Disco* backup = (Disco*)malloc(sizeof(Disco));
	if (listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		do {
			lista_ordenada = true;
			aux = lista_discos_inicio;
			while (aux->siguiente != menor_ordenado) {
				if (aux->anio_lanzamiento > aux->siguiente->anio_lanzamiento) { 
					//backup->dato = aux->dato;
					copiarDisco(backup,aux);
					//aux->dato = aux->siguiente->dato;
					copiarDisco(aux,aux->siguiente);
					//aux->siguiente->dato = backup->dato;
					copiarDisco(aux->siguiente,backup);
					lista_ordenada = false;
				}
				aux = aux->siguiente;
			}
			menor_ordenado = aux;
		} while (lista_ordenada == false);
	}
	printf("Lista ordenada.\n");
}

void ordenarDiscosNumCompras() {
	enum boolean lista_ordenada;
	Disco* aux = NULL;
	Disco* menor_ordenado = NULL;
	Disco* backup = (Disco*)malloc(sizeof(Disco));
	if (listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		do {
			lista_ordenada = true;
			aux = lista_discos_inicio;
			while (aux->siguiente != menor_ordenado) {
				if (aux->num_compras > aux->siguiente->num_compras) { 
					//backup->dato = aux->dato;
					copiarDisco(backup,aux);
					//aux->dato = aux->siguiente->dato;
					copiarDisco(aux,aux->siguiente);
					//aux->siguiente->dato = backup->dato;
					copiarDisco(aux->siguiente,backup);
					lista_ordenada = false;
				}
				aux = aux->siguiente;
			}
			menor_ordenado = aux;
		} while (lista_ordenada == false);
	}
	printf("Lista ordenada.\n");
}

void buscarDiscoNombre(char nombre_disco[]) {
	if(listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		Disco* aux = lista_discos_inicio;
		int contador = 0;
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		printf("| Artista\t\t\t | Nombre del Disco\t\t  | Precio    | Año       | Comprados |\n");
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		while(aux != NULL && strcmp(aux->nombre_disco,nombre_disco) != 0 ) {
			aux = aux->siguiente;
		}
		imprimirDisco(aux);
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
	}
}

void buscarDiscoArtista(char artista[]) {
	if(listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		Disco* aux = lista_discos_inicio;
		int contador = 0;
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		printf("| Artista\t\t\t | Nombre del Disco\t\t  | Precio    | Año       | Comprados |\n");
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		while(aux != NULL) {
			if (strcmp(aux->artista,artista) == 0) {
				imprimirDisco(aux);
				contador++;
			}
			aux = aux->siguiente;
		}
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		printf("%d resultados.\n", contador);
	}
}

void buscarDiscoAnio(int anio) {
	if(listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		Disco* aux = lista_discos_inicio;
		int contador = 0;
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		printf("| Artista\t\t\t | Nombre del Disco\t\t  | Precio    | Año       | Comprados |\n");
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		while(aux != NULL) {
			if (aux->anio_lanzamiento == anio) {
				imprimirDisco(aux);
				contador++;
			}
			aux = aux->siguiente;
		}
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		printf("%d resultados.\n", contador);
	}
}

void buscarDiscoPrecioMenor(float precio) {
	if(listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		Disco* aux = lista_discos_inicio;
		int contador = 0;
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		printf("| Artista\t\t\t | Nombre del Disco\t\t  | Precio    | Año       | Comprados |\n");
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		while(aux != NULL) {
			if (aux->precio < precio) {
				imprimirDisco(aux);
				contador++;
			}
			aux = aux->siguiente;
		}
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		printf("%d resultados.\n", contador);
	}
}

void buscarDiscoPrecioMayor(float precio) {
	if(listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		Disco* aux = lista_discos_inicio;
		int contador = 0;
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		printf("| Artista\t\t\t | Nombre del Disco\t\t  | Precio    | Año       | Comprados |\n");
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		while(aux != NULL) {
			if (aux->precio > precio) {
				imprimirDisco(aux);
				contador++;
			}
			aux = aux->siguiente;
		}
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		printf("%d resultados.\n", contador);
	}
}

void buscarDiscoPrecioIgual(float precio) {
	if(listaDiscosVacia()) {
		printf("No hay discos.\n");
	}
	else {
		Disco* aux = lista_discos_inicio;
		int contador = 0;
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		printf("| Artista\t\t\t | Nombre del Disco\t\t  | Precio    | Año       | Comprados |\n");
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		while(aux != NULL) {
			if (aux->precio == precio) {
				imprimirDisco(aux);
				contador++;
			}
			aux = aux->siguiente;
		}
		printf("+--------------------------------+--------------------------------+-----------+-----------+-----------+\n");
		printf("%d resultados.\n", contador);
	}
}

void cargarInventario() {
	DIR* directorio;
	struct dirent *ent;
	char nombre_carpeta[40] = {'\0'};
	directorio = opendir("./discos/");
	if (directorio == NULL) {
		printf("Error al cargar directorio.\n");
	}
	else {
		while ((ent = readdir(directorio)) !=  NULL) {
			strcpy(nombre_carpeta,"./discos/");
			if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0)) {
				strcat(nombre_carpeta,ent->d_name);
				leerArchivoDisco(nombre_carpeta);
			}
		}
		closedir(directorio);
	}
}

void leerArchivoDisco(char nombre_archivo[]) {
	FILE* archivo_disco = fopen(nombre_archivo,"r");
	if (archivo_disco == NULL) {
		printf("Error al cargar. Verifique el archivo.\n");

	}
	else {	
		char nombre_disco[24];
		char artista[24];
		float precio;
		int anio_lanzamiento;
		int num_compras;
		fscanf(archivo_disco," %[^\n]\n",nombre_disco);
		fscanf(archivo_disco," %[^\n]\n",artista);
		fscanf(archivo_disco,"%f\n",&precio);
		fscanf(archivo_disco,"%d\n",&anio_lanzamiento);
		fscanf(archivo_disco,"%d\n",&num_compras);
		agregarDisco(crearDisco(nombre_disco,artista,precio,anio_lanzamiento,num_compras));
		fclose(archivo_disco);
	}
}

void guardarInventario() {
	char nombre_carpeta[40];
	Disco* aux = lista_discos_inicio;
	while (aux != NULL) {
		strcpy(nombre_carpeta,"./discos/");
		strcat(nombre_carpeta,aux->nombre_disco);
		strcat(nombre_carpeta,".txt");
		escribirArchivoDisco(nombre_carpeta,aux);
		aux = aux->siguiente;
	}
}

void escribirArchivoDisco(char nombre_archivo[],Disco* disco) {
	FILE* archivo_disco = fopen(nombre_archivo,"w");
	if (archivo_disco == NULL) {
		printf("Error al guardar el inventario. Verifique el archivo.\n");
		return;
	}
	else {
		fprintf(archivo_disco,"%s\n",disco->nombre_disco);
		fprintf(archivo_disco,"%s\n",disco->artista);
		fprintf(archivo_disco,"%.2f\n",disco->precio);
		fprintf(archivo_disco,"%d\n",disco->anio_lanzamiento);
		fprintf(archivo_disco,"%d\n",disco->num_compras);
		fclose(archivo_disco);
	}
}

void eliminarArchivoDisco(Disco* disco) {
	char nombre_archivo[40] = "./discos/";
	strcat(nombre_archivo,disco->nombre_disco);
	strcat(nombre_archivo,".txt");
	remove(nombre_archivo);
}

void renombrarArchivoDisco(char nombre_antiguo[],char nombre_nuevo[]) {
	char nombre_archivo1[40] = "./discos/";
	char nombre_archivo2[40] = "./discos/";
	strcat(nombre_archivo1,nombre_antiguo);
	strcat(nombre_archivo2,nombre_nuevo);
	strcat(nombre_archivo1,".txt");
	strcat(nombre_archivo2,".txt");
	rename(nombre_archivo1,nombre_archivo2);
}