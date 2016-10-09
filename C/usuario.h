/*
	usuario.h
	Autor: David Yaxkin Sánchez Neri
	Biblioteca que contiene la estructura básica de un Usuario
	y las funciones en las que se ve involucrado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "extras.h"
#include "disco.h"

//enum boolean{false,true};

typedef struct Usuario {
	char nombre_usuario[32];
	char contrasena[32];
	int edad;
	int num_compras;
	char **discos_comprados;
	struct Usuario* siguiente;
}Usuario;

Usuario* lista_usuarios_inicio = NULL;
Usuario* lista_usuarios_final = NULL;
int num_usuarios = 0;

Usuario* crearUsuario(char nombre_usuario[], char contrasena[], int edad, int num_compras, char **discos_comprados);
enum boolean listaUsuariosVacia();
void agregarUsuario(Usuario* usuario);
void modificarUsuario(char nombre_usuario[]);
Usuario* removerUsuario(char nombre_usuario[]);

enum boolean nombreUsuarioRegistrado(char nombre_usuario[]);
void registrarUsuario();
void comprarDisco(char nombre_usuario[], char nombre_disco[]);
void mostrarUsuarios();
void mostrarUsuario(char nombre_usuario[]);
void cargarListaUsuarios();
void leerArchivoUsuario(char nombre_archivo[]);
void guardarListaUsuarios();
void escribirArchivoUsuario(char nombre_archivo[],Usuario* usuario);
void eliminarArchivoUsuario(Usuario* usuario);

Usuario* crearUsuario(char nombre_usuario[], char contrasena[], int edad, int num_compras, char **discos_comprados) {
	int i;
	Usuario* nuevo = (Usuario*)malloc(sizeof(Usuario));
	strcpy(nuevo->nombre_usuario,nombre_usuario);
	strcpy(nuevo->contrasena,contrasena);
	nuevo->edad = edad;
	nuevo->num_compras = num_compras;
	nuevo->discos_comprados = discos_comprados;
	nuevo->siguiente = NULL;
	return nuevo;
}

enum boolean listaUsuariosVacia() {
	if(lista_usuarios_inicio == NULL && lista_usuarios_final == NULL) {
		return true;
	}
	else { 
		return false;
	}
}

void agregarUsuario(Usuario* usuario) {
	if (lista_usuarios_inicio == NULL){
		lista_usuarios_inicio = usuario;
	}
	else {
		lista_usuarios_final->siguiente = usuario;
	}
	lista_usuarios_final = usuario;
	num_usuarios++;
}

void modificarUsuario(char nombre_usuario[]) {
	if(listaUsuariosVacia()) {
		printf("No hay usuarios.\n");
	}
	else {
		int opcion;
		char buffer[8]={'\0'};
		Usuario* scout = lista_usuarios_inicio;
		while( strcmp(scout->nombre_usuario,nombre_usuario) != 0 ) {
			scout = scout->siguiente;
			if (scout == NULL) {
				printf("Usuario \"%s\" no encontrado.\n",nombre_usuario);
				return;
			}
		}
		printf("Ingrese sus nuevos datos.\n");
		printf("Contraseña: ");
		scanf(" %[^\n]",scout->contrasena);
		do {
			printf("Edad: ");
			scanf("%s",buffer);
		} while (!validarEntero(buffer));
		scout->edad = atoi(buffer);
	}
}

Usuario* removerUsuario(char nombre_usuario[]) {
	if(listaUsuariosVacia()) {
		return (Usuario*)NULL;
	}
	Usuario* aux = lista_usuarios_inicio;
	if (lista_usuarios_inicio == lista_usuarios_final && strcmp(aux->nombre_usuario,nombre_usuario) == 0) {
		lista_usuarios_inicio = NULL;
		lista_usuarios_final = NULL;
		eliminarArchivoUsuario(aux);
		num_usuarios--;
		return aux;
	}
	else if (strcmp(aux->nombre_usuario,nombre_usuario) == 0) {
		lista_usuarios_inicio = lista_usuarios_inicio->siguiente;
		aux->siguiente = NULL;
		eliminarArchivoUsuario(aux);
		num_usuarios--;
		return aux;
	}
	else {
		Usuario* scout = lista_usuarios_inicio;
		while(strcmp(scout->nombre_usuario,nombre_usuario) != 0) {
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
		eliminarArchivoUsuario(scout);
		num_usuarios--;
		return scout;
	}
}

enum boolean nombreUsuarioRegistrado(char nombre_usuario[]) {
	Usuario* aux = lista_usuarios_inicio;
	while(aux != NULL && strcmp(aux->nombre_usuario,nombre_usuario) != 0) {
		aux = aux->siguiente;
	}
	if (aux != NULL && strcmp(aux->nombre_usuario,nombre_usuario) == 0) {
		return true;
	}
	else {
		return false;
	}
}

void registrarUsuario() {
	char nombre_usuario[32];
	char contrasena[32];
	int edad;
	char buffer[32] = {'\0'};
	do {
		if(nombreUsuarioRegistrado(nombre_usuario)){
			printf("Nombre de usuario ya registrado.\n");
		}
		printf("Ingrese nombre de usuario: ");
		scanf(" %[^\n]",nombre_usuario);
	} while (nombreUsuarioRegistrado(nombre_usuario));
	printf("Ingrese contrasena de usuario: ");
	scanf(" %[^\n]",contrasena);
	do {
		printf("Edad: ");
		scanf("%s",buffer);
	} while (!validarEntero(buffer));
	edad = atoi(buffer);
	agregarUsuario(crearUsuario(nombre_usuario,contrasena,edad,0,NULL));
	printf("Usuario agregado.\n");
}

void comprarDisco(char nombre_usuario[], char nombre_disco[]) {
	Usuario* usuario = lista_usuarios_inicio;
	Disco* disco = lista_discos_inicio;
	if(listaUsuariosVacia() || listaDiscosVacia()) {
		printf("No hay usuarios o discos.\n");
	}
	else if (discoEnLista(nombre_disco)) {
		while(usuario != NULL && strcmp(usuario->nombre_usuario,nombre_usuario) != 0) {
			usuario = usuario->siguiente;
		}
		while(disco != NULL && strcmp(disco->nombre_disco,nombre_disco) != 0) {
			disco = disco->siguiente;
		}
		if (usuario != NULL && disco != NULL) {
			strcpy(usuario->discos_comprados[usuario->num_compras],disco->nombre_disco);
			usuario->num_compras++;
			disco->num_compras++;
			printf("Compra de \"%s\" realizada.\n",disco->nombre_disco);
		}
	}
	else {
		printf("Disco \"%s\" no encontrado.\n",nombre_disco);
	}
}

void mostrarUsuarios() {
	//Si la lista está vacía.
	if(listaUsuariosVacia()) {
		printf("No hay usuarios.\n");
	}
	else {
		Usuario* aux = lista_usuarios_inicio;
		printf("\n\tLista de usuarios:\n");
		while(aux != NULL) {
			printf("- %s\n", aux->nombre_usuario);
			aux = aux->siguiente;
		}	
	}
}

void mostrarUsuario(char nombre_usuario[]) {
	if(listaUsuariosVacia()) {
		printf("No hay usuarios.\n");
	}
	else {
		Usuario* aux = lista_usuarios_inicio;
		while(aux != NULL && strcmp(aux->nombre_usuario,nombre_usuario) != 0 ) {
			aux = aux->siguiente;
		}
		printf("\nNombre de usuario: %s \n",aux->nombre_usuario);
		printf("Edad: %d \n",aux->edad);
		printf("Compras realizadas:\n");
		int i;
		for(i = 0; i < aux->num_compras; i++) {
			printf("- %s\n",aux->discos_comprados[i]);
		}
		printf("\n");
	}
}

void cargarListaUsuarios() {
	DIR* directorio;
	struct dirent *ent;
	char nombre_carpeta[40] =  {'\0'};
	directorio = opendir("./usuarios/");
	if (directorio == NULL) {
		printf("Error al cargar directorio.\n");
	}
	else {
		while ((ent = readdir(directorio)) !=  NULL) {
			strcpy(nombre_carpeta,"./usuarios/");
			if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0)) {
				strcat(nombre_carpeta,ent->d_name);
				leerArchivoUsuario(nombre_carpeta);
			}
		}
		closedir(directorio);
	}
}

void leerArchivoUsuario(char nombre_archivo[]) {
	FILE* archivo_usuario = fopen(nombre_archivo,"r");
	if (archivo_usuario == NULL) {
		printf("Error al cargar. Verifique el archivo.\n");
	}
	else {
		char nombre_usuario[32];
		char contrasena[32];
		int edad;
		int num_compras;
		int i;
		char test[32]={'\0'};
		char **discos_comprados = (char**)calloc(32,sizeof(char*));
		for (i = 0; i<32; i++) {
			discos_comprados[i] = (char*)calloc(32,sizeof(char));
		}
		fscanf(archivo_usuario," %[^\n]\n",nombre_usuario);
		fscanf(archivo_usuario," %[^\n]\n",contrasena);
		fscanf(archivo_usuario,"%d\n",&edad);
		fscanf(archivo_usuario,"%d\n",&num_compras);
		for(i = 0; i< num_compras; i++) {
			fscanf(archivo_usuario," %[^\n]\n",discos_comprados[i]);
		}
		agregarUsuario(crearUsuario(nombre_usuario,contrasena,edad,num_compras,discos_comprados));
		fclose(archivo_usuario);
	}
}

void guardarListaUsuarios() {
	char nombre_carpeta[40];
	Usuario* aux = lista_usuarios_inicio;
	while (aux != NULL) {
		strcpy(nombre_carpeta,"./usuarios/");
		strcat(nombre_carpeta,aux->nombre_usuario);
		strcat(nombre_carpeta,".txt");
		escribirArchivoUsuario(nombre_carpeta,aux);
		aux = aux->siguiente;
	}
}

void escribirArchivoUsuario(char nombre_archivo[],Usuario* usuario) {
	int i;
	FILE* archivo_usuario = fopen(nombre_archivo,"w");
	if (archivo_usuario == NULL) {
		printf("Error al guardar el inventario. Verifique el archivo.\n");
	}
	else {
		fprintf(archivo_usuario,"%s\n",usuario->nombre_usuario);
		fprintf(archivo_usuario,"%s\n",usuario->contrasena);
		fprintf(archivo_usuario,"%d\n",usuario->edad);
		fprintf(archivo_usuario,"%d\n",usuario->num_compras);
		for(i = 0; i< usuario->num_compras; i++) {
			fprintf(archivo_usuario,"%s\n",usuario->discos_comprados[i]);
		}
		fclose(archivo_usuario);
	}
}

void eliminarArchivoUsuario(Usuario* usuario) {
	char nombre_archivo[40] =  "./usuarios/";
	strcat(nombre_archivo,usuario->nombre_usuario);
	strcat(nombre_archivo,".txt");
	remove(nombre_archivo);
}