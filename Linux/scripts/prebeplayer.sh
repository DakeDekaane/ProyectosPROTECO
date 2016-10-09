#!/bin/bash

salir='N'
nivellista=0

function cambiadir(){
	cd "$1"
}

function listadir() {
	cnt=0
	for file in "$PWD"/*; do
		if [[ -d "$file" ]]; then
			nombre=`echo -e "$file" | grep -E -o "[][a-zA-Z0-9_─–\.\+\(\)\ \'\!\-]*$"`
			echo -e " ── \E[1;34m$nombre\E[0m"
		elif [[ `echo -e "$file" | grep -E -o "[][a-zA-Z0-9_─–\.\+\(\)\ \'\!\-]+.mp3"` ]]; then
			nombre=`echo -e "$file" | grep -E -o "[][a-zA-Z0-9_─–\.\+\(\)\ \'\!\-]+.mp3"`
			echo -e " ── \E[1;37m$nombre\E[0m"
			let cnt=cnt+1
		fi
	done
	if [[ cnt -eq 0 ]]; then
			echo -e "\n\E[1;34mNo se encontraron canciones en este directorio :(\E[0m"
	fi
}

function muestra_controles(){
	echo -e "\E[1;35mReproduciendo carpeta\E[0m"
	echo -e "\n\t$(tput bold)CONTROLES$(tput sgr0)"
	echo -e "	[espacio] pausa		[f] pista siguiente	[d] pista anterior"
	echo -e "	[b] reiniciar canción	[q] detener		[+] subir volumen"
	echo -e "	[.] adelantar		[,] rebobinar		[-] bajar volumen"
	echo -e "	[t] información sobre la canción		[h] más comandos"
	echo -e "	[l] mostrar lista de reproduccion actual"
}

while [[ $salir != "S" ]]; do 	
	if [[ -f /usr/bin/mpg123 ]]; then

		echo -n `clear`
		echo -e "\E[1;35m	_________________________________________________________________"
		echo -e "\E[1;35m	____|  _ \__ ______| |________|  _ \| |__________________________"
        echo -e "\E[1;35m	____| |_) | '__/ _ \ '_ \ / _ \ |_) | |/ _\` | | | |/ _ \ '__|____"
        echo -e "\E[1;35m	____|  __/| |_|  __/ |_) |  __/  __/| | (_| | |_| |  __/ |_______"
        echo -e "\E[1;35m	____|_|___|_|__\___|_.__/_\___|_|___|_|\__,_|\__, |\___|_|_______"
        echo -e "\E[1;35m	                                             |___/               "

		echo -e "\E[1;33mMenú: \E[0m"
		echo -e "\E[1;36m    1. Lista canciones y subdirectorios en la carpeta actual\E[0m"
		echo -e "\E[1;36m    2. Reproducir carpeta actual en orden secuencial\E[0m"
		echo -e "\E[1;36m    3. Reproducir carpeta actual en orden aleatorio\E[0m"
		echo -e "\E[1;36m    4. Cambiar de directorio\E[0m"
		echo -e "\E[1;36m    5. Ayuda\E[0m"
		echo -e "\E[1;36m    6. Salir\E[0m"
		echo -e "\E[1;35m    Directorio actual:\E[1;30m $PWD\E[0m"
		echo -en "\E[1;33m¿Qué desea realizar? Ingrese una opción: \E[0m"
		read opcion
		case $opcion in
			1) 
				echo -e "\n\E[1;36mLista de canciones y subdirectorios\E[0m"
				listadir
				echo -e -n "\n\E[1;36mPulse Enter para continuar.\E[0m"
				read
				;;
			2)
				muestra_controles
				mpg123 -qC *
				;;
			3)
				muestra_controles
				mpg123 -qzC *
				;;
			4)	
				echo -en "\n\E[1;36mIngresa el directorio:\E[0m "
				read  directorio_nuevo
				cambiadir $directorio_nuevo
				echo -e -n "\n\E[1;36mPulse Enter para continuar.\E[0m"
				;;
			5)	
				echo -e "\n\t$(tput bold)AYUDA$(tput sgr0)"
				echo -e "\n\tIngrese el número de la acción que desee realizar."
				echo -e "\tQue la Fuerza te acompañe."
				echo -e -n "\n\E[1;36mPulse Enter para continuar.\E[0m"
				read
				;;
			6)	
				echo `clear`
				salir='S'
				;;
			*)
				echo -e -n "\n\E[1;36mOpción inválida. Pulse Enter para continuar.\E[0m"
				read
				;;
		esac
	else
		echo -e "\E[1;31mEl paquete mpg123 no está instalado.\E[0m"
		echo -e -n "\E[1;32mPulse Enter para iniciar la instalación\E[0m"
		read
		sudo apt-get install mpg123
		echo -e -n "\E[1;34mInstalación terminada. Pulse Enter para continuar.\E[0m"
		read
	fi
done
