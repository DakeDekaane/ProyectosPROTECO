/*
	main.c
	Autor: David Yaxkin Sánchez Neri
	Programa que implementa un sistema electrónico de una tienda de música.
*/

#include <stdio.h>
//#include "disco.h"
#include "usuario.h"
#include "login.h"
//#include "extras.h"
#include "menu.h"

int main(int argc, char const *argv[]) {
	cargarListaUsuarios();
	cargarInventario();
	int opcion;
	char buffer[32] = {'\0'};
	enum boolean salir_sistema = false;
	do {
		clearScreen();
		printf("\t\t\tBIENVENIDO A MICSHOP\n\n\n");
		printf("\tMenú principal\n\n");
		printf("\t1. Iniciar sesión.\n");
		printf("\t2. Registrar usuario.\n");
		printf("\t0. Salir.\n\n");
		do {
			printf("\tIngrese una opción: ");
			scanf("%s",buffer);
		} while (!validarEntero(buffer));
		opcion = atoi(buffer);
		switch(opcion) {
			case 1:	{
				Usuario* usuarioActual = validaUsuario();
				if (usuarioActual == NULL) {
					//return 1;
				}
				else if (strcmp(usuarioActual->nombre_usuario,"admin") == 0) {
					menuAdmin();
				}
				else {
					menuUsuario(usuarioActual);
				}
			}
			break;
			case 2:
				registrarUsuario();
				guardarListaUsuarios();
				pausa();
			break;
			case 0:
				salir_sistema = true;
			break;
			default:
				printf("Opción inválida.\n");
				pausa();
		}
	} while (salir_sistema == false);
	return 0;
}