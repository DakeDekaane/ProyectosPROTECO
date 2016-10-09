#!/bin/bash

function valida_usuario() {
	cadena_magica=$(sudo grep "^$1:" /etc/shadow | cut -d ':' -f 2)
	sudo grep -q "^$1:$(mkpasswd -H SHA-512 -S ${cadena_magica:3:8} $2)" /etc/shadow
	if [[ $? -eq 0 ]]; then
		usuario_valido=1
	else
		usuario_valido=0
	fi
}

sudo -v
echo -e `clear`
echo -e "\t\t\tBienvenido a la PrebeShell."
echo -e -n "\n\tUsuario: "
read usuario
echo -e -n "\n\tContraseña: "
read -s contrasena
valida_usuario $usuario $contrasena
if [[ $usuario_valido -eq 1 ]]; then

	origen=`echo "$PWD/scripts"`
	echo -e "\n\n\t\t\t\E[1;32mBienvenido, $usuario\n\E[0m"
	while :; do
		trap '' 2
		trap '' SIGTSTP
		prompt="\E[1;33m$USER \e[1;30m\\ \E[1;34m$PWD:\E[0m "
		trap '' 2
		trap '' SIGTSTP
		echo -en "$prompt"
		read comando
		read -r arg0 arg1 arg2 <<< "$comando"
		case $arg0 in
			ahorcado )		#Completo
				$origen/ahorcado.sh $origen;;
			arbol )			#Completo
				$origen/arbol.sh;;
			infosis )		#Completo
				$origen/infosis.sh;;
			ayuda )			#Completo
				$origen/ayuda.sh;;
			fecha )			#Completo
				$origen/fecha.sh;;
			hora )			#Completo
				$origen/hora.sh;;
			busca )			#Completo
				$origen/busqueda.sh $arg1 $arg2;;
			prebeplayer )	#Completo
				$origen/prebeplayer.sh;;
			creditos )
				$origen/creditos.sh $origen;;
			salir )		
				exit 0;;
			* )
				eval "$comando"
				;;
		esac
	done

else
	echo -e "\n\n\t\t\E[1;31m ¡Usuario/contraseña inválido(s)!\n"
	exit 1
fi

# This example script, and much of the above explanation supplied by
# Stéphane Chazelas (thanks again).