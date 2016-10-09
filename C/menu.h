/*
	menu.h
	Autor: David Yaxkin Sánchez Neri
	Biblioteca que contiene los menús y submenus del programa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "disco.h"
//#include "usuario.h"

void menuAdmin();
void menuUsuario();
void menuOrdenar();
void menuBusqueda();

void menuAdmin(){
	char artista[32];
	char nombre_disco[32];
	float precio;
	int anio_lanzamiento;
	char nombre_usuario[32];
	char contrasena[32];
	int edad;
	char buffer[32] = {'\0'};
	enum boolean salir_sesion = false;
	int opcion;
	do{
		clearScreen();
		printf("\n\tBienvenido, admin.\n\n\n");
		printf("\n\tMenú del administrador.\n\n");
		printf("\t1. Mostrar todos los discos.\n");
		printf("\t2. Agregar un disco.\n");
		printf("\t3. Remover un disco.\n");
		printf("\t4. Modificar los datos de un disco.\n");
		printf("\t5. Buscar discos.\n");
		printf("\t6. 0rdenar los discos.\n");
		printf("\t7. Ver lista de usuarios.\n");
		printf("\t8. Agregar usuario.\n");
		printf("\t9. Remover usuario.\n");
		printf("\t0. Salir.\n\n");
		do {
			printf("Ingrese una opción: ");
			scanf("%s",buffer);
		} while (!validarEntero(buffer));
		opcion = atoi(buffer);
		switch(opcion) {
			case 1:
				mostrarDiscos();
				pausa();
				break;
			case 2:
				registrarDisco();
				pausa();
				break;
			case 3:
				printf("Ingrese nombre del disco: ");
				scanf(" %[^\n]",nombre_disco);
				if (discoEnLista(nombre_disco)) {
					printf("\"%s\" ha sido removido.\n",removerDisco(nombre_disco)->nombre_disco);
				}
				else {
					printf("Disco \"%s\" no encontrado.\n",nombre_disco);
				}
				pausa();
				break;
			case 4:
				printf("Ingrese nombre del disco: ");
				scanf(" %[^\n]",nombre_disco);
				modificarDisco(nombre_disco);
				pausa();
				break;
			case 5:
				menuBusqueda();
				pausa();
				break;
			case 6:
				menuOrdenar();
				pausa();
				break;
			case 7:
				mostrarUsuarios();
				pausa();
				break;
			case 8:
				registrarUsuario();
				guardarListaUsuarios();
				pausa();
				break;
			case 9:
				printf("Ingrese nombre de usuario: ");
				scanf(" %[^\n]",nombre_usuario);
				if(nombreUsuarioRegistrado(nombre_usuario)) {
					printf("\"%s\" ha sido removido.\n",removerUsuario(nombre_usuario)->nombre_usuario);
				}
				else {
					printf("Usuario \"%s\" no encontrado.\n",nombre_usuario);
				}
				guardarListaUsuarios();
				pausa();
				break;
			case 0:
				printf("\n\tHasta luego, admin.\n\n");
				pausa();
				salir_sesion = true;
				break;
			default:
				printf("\nOpción inválida.\n");
				pausa();
		}
		guardarInventario();
	} while (salir_sesion == false);
}

void menuOrdenar() {
	int opcion;
	char buffer[32] = {'\0'};
	printf("\n\tMenú de ordenamiento.\n\n");
	printf("\t1. Por nombre.\n");
	printf("\t2. Por artista.\n");
	printf("\t3. Por precio.\n");
	printf("\t4. Por año.\n");
	printf("\t5. Por número de compras.\n");
	printf("\tOtro. Cancelar.\n\n");
	do {
		printf("Ingrese una opción: ");
		scanf(" %[^\n]",buffer);
	} while (!validarEntero(buffer));
	opcion = atoi(buffer);
	switch(opcion) {
		case 1:
			ordenarDiscosNombre();
		break;
		case 2:
			ordenarDiscosArtista();
		break;
		case 3:
			ordenarDiscosPrecio();
		break;
		case 4:
			ordenarDiscosAnio();
		break;
		case 5:
			ordenarDiscosNumCompras();
		break;
	}
}

void menuBusqueda(){
	int opcion;
	char buffer[32] = {'\0'};
	float precio;
	int anio;
	printf("\n\tMenú de búsqueda.\n\n");
	printf("\t1. Por nombre.\n");
	printf("\t2. Por artista.\n");
	printf("\t3. Por precio.\n");
	printf("\t4. Por año.\n");
	printf("\tOtro. Cancelar.\n\n");
	do {
		printf("Ingrese una opción: ");
		scanf(" %[^\n]",buffer);
	} while (!validarEntero(buffer));
	opcion = atoi(buffer);
	switch(opcion) {
		case 1:
			printf("Ingrese el nombre del disco: ");
			scanf(" %[^\n]",buffer);
			buscarDiscoNombre(buffer);
		break;
		case 2:
			printf("Ingrese el artista del disco: ");
			scanf(" %[^\n]",buffer);
			buscarDiscoArtista(buffer);
		break;
		case 3:
			do {
				printf("Ingrese el precio: ");
				scanf(" %[^\n]",buffer);
			} while (!validarFlotante(buffer));
			precio = atof(buffer);

			printf("\nSubmenú: (1) Precio menor a | (2) Precio mayor a | (3) Precio igual a\n");
			enum boolean f_busqueda = true;
			do {
				do {
					printf("Ingrese una opción: ");
					scanf(" %[^\n]",buffer);
				} while (!validarEntero(buffer));
				opcion = atoi(buffer);

				switch(opcion) {
					case 1:
						buscarDiscoPrecioMenor(precio);
					break;
					case 2:
						buscarDiscoPrecioMayor(precio);
					break;
					case 3:
						buscarDiscoPrecioIgual(precio);
					break;
					default:
						printf("Opción invalida.\n");
						f_busqueda = false;
				}
			} while (f_busqueda == false);
		break;
		case 4:
			do {
			printf("Ingrese el año: ");
				scanf(" %[^\n]",buffer);
			} while (!validarEntero(buffer));
			anio = atoi(buffer);
			buscarDiscoAnio(anio);
		break;
	}
}

void menuUsuario(Usuario* usuarioActual) {
	char artista[32];
	char nombre_disco[32];
	float precio;
	int anio_lanzamiento;
	char nombre_usuario[32];
	char contrasena[32];
	int edad;
	char buffer[32] = {'\0'};
	enum boolean salir_sesion = false;
	int opcion;
	do { 
		clearScreen();
		printf("\n\tBienvenido, %s.\n\n\n",usuarioActual->nombre_usuario);
		printf("\tMenú del usuario.\n\n");
		printf("\t1. Mostrar todos los discos.\n");
		printf("\t2. Buscar discos.\n");
		printf("\t3. Comprar un disco.\n");
		printf("\t4. Ver perfil de usuario.\n");
		printf("\t5. Editar perfil de usuario.\n");
		printf("\t0. Salir.\n\n");
		do {
			printf("Ingrese una opción: ");
			scanf("%s",buffer);
		} while (!validarEntero(buffer));
		opcion = atoi(buffer);
		switch(opcion) {
			case 1:
				mostrarDiscos();
				pausa();
				break;
			case 2:
				menuBusqueda();
				pausa();
				break;
			case 3:
				printf("Ingrese el nombre del disco que desea comprar: ");
				scanf(" %[^\n]",buffer);
				comprarDisco(usuarioActual->nombre_usuario,buffer);
				pausa();
				break;
			case 4:
				mostrarUsuario(usuarioActual->nombre_usuario);
				pausa();
				break;
			case 5:
				modificarUsuario(usuarioActual->nombre_usuario);
				guardarListaUsuarios();
				pausa();
				break;
			case 0:
				printf("\n\tHasta luego, %s.\n\n",usuarioActual->nombre_usuario);
				pausa();
				salir_sesion = true;
				break;
			default:
				printf("\nOpción inválida.\n");
				pausa();
		}
		guardarListaUsuarios();
		guardarInventario();
	} while (salir_sesion == false);
}