/*
	extras.h
	Autor: David Yaxkin Sánchez Neri
	Biblioteca que contiene la validación de usuario.
*/

#include <stdio.h>
//#include "usuario.h"

Usuario* validaUsuario();

Usuario* validaUsuario(){

	int intentos = 3;
	char usuarioIngresado[32]={'\0'};
	char contrasenaIngresada[32]={'\0'};
	printf("\n\tIngrese su usuario y contraseña para continuar.\n\n");
	do {
		printf("\t\tUsuario: ");
		scanf(" %[^\n]",usuarioIngresado);
		printf("\t\tContraseña: ");
		scanf(" %[^\n]",contrasenaIngresada);
		if(listaUsuariosVacia()) {
			printf("No hay usuarios.\n");
		}
		else {
			Usuario* aux = lista_usuarios_inicio;
			while(aux != NULL && strcmp(aux->nombre_usuario,usuarioIngresado) != 0) {
				aux = aux->siguiente;
			}
			if (aux != NULL && strcmp(aux->contrasena,contrasenaIngresada) == 0) {
				return aux;
			}
		}
		printf("\n\tAcceso denegado. Verifique sus datos\n\n");
		intentos--;
	} while(intentos > 0);
	if (intentos == 0) printf("Ha realizado 3 intentos fallidos. Se le regresará al menú principal.\n");
	pausa();
	return NULL;
}