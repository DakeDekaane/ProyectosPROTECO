#!/bin/bash

#Variables de inicio.
salir='N'
juego_activo=0
origen_diccionario="$1/diccionario.txt"

#Toma una palabra al azar de un "diccionario" y la alista como arreglo de caracteres
function inicializa_palabra(){
	dummy=`shuf -n 1 "$origen_diccionario"`
	for (( i = 0; i < ${#dummy}; i++ )); do
		palabra[$i]=${dummy:i:1}
	done
}

#Arreglo de la palabra escondida
function inicializa_hidden(){
	for (( i = 0; i < ${#palabra[@]}; i++ )); do
		hidden[$i]='_'
	done
}

#Muestra la cabecera del juego
function cabecera(){
	echo -n `clear`
	echo -e "\t\t\t\t\E[0;35m╔═════════════════╗"
	echo -e "\t\t\t\t║\E[1;33m    Ahorcado:    \E[0;35m║"
	echo -e "\t\t\t\t║\E[1;33m  el videojuego  \E[0;35m║"
	echo -e "\t\t\t\t\E[0;35m╚═════════════════╝\E[0m\n"
	echo -e "\E[1;33m»\E[1;34m Usa el comando \"ayuda\" para más información.\E[0m\n"
}

#Dibujo para mostrar el avance
function dibujo(){
	echo -e "\E[0;33m	┌─────┐ "
	if [[ $vidas -eq 6 ]]; then
		echo -e "	│       "
		echo -e "	│       "
		echo -e "	│       "
	elif [[ $vidas -eq 5 ]]; then
		echo -e "	│     \E[1;31mo "
		echo -e "\E[0;33m	│       "
		echo -e "	│       "
	elif [[ $vidas -eq 4 ]]; then
		echo -e "	│     \E[1;31mo "
		echo -e "\E[0;33m	│     \E[1;31m| "
		echo -e "\E[0;33m	│       "
	elif [[ $vidas -eq 3 ]]; then
		echo -e "	│     \E[1;31mo "
		echo -e "\E[0;33m	│    \E[1;31m/| "
		echo -e "\E[0;33m	│       "
	elif [[ $vidas -eq 2 ]]; then
		echo -e "	│     \E[1;31mo "
		echo -e "\E[0;33m	│    \E[1;31m/|\\"
		echo -e "\E[0;33m	│       "
	elif [[ $vidas -eq 1 ]]; then
		echo -e "	│     \E[1;31mo "
		echo -e "\E[0;33m	│    \E[1;31m/|\\"
		echo -e "\E[0;33m	│    \E[1;31m/  "
	elif [[ $vidas -eq 0 ]]; then
		echo -e "	│     \E[1;31mo "
		echo -e "\E[0;33m	│    \E[1;31m/|\\"
		echo -e "\E[0;33m	│    \E[1;31m/ \\"
	fi
	echo -e "\E[0;33m	│       "
	echo -e "\E[0;33m	└──────"
}

#Muestra los comandos existentes
function ayuda(){
	echo -e "\n\t$(tput bold)COMANDOS$(tput sgr0)"
	echo -e "\tjugar			Inicia un nuevo juego"
	echo -e "\tadivina <letra>\t\tSi <letra> está en la palabra, la revelará."
	echo -e "				En caso contrario, perderás una vida."
	echo -e "\tayuda 			Muestra los comandos del juego."
	echo -e "\tsalir 			Sale del juego.\n"
}

#Hace una confirmación antes de salir del juego
function salir(){
	echo -e -n "\E[1;33m»\E[1;36m¿Está seguro que desea salir? (S/N):\E[0m "
	read salir
	if [[ $salir = "S" || $salir = "s" ]]; then
		echo `clear`
		exit
	elif [[ $salir = "N" || $salir = "n" ]]; then
		return
	else
		echo -e "Opción inválida."
	fi
}

#Funcion principal (para jugar)
function jugar(){
	
	#Inicialización del entorno

	#Inicializa arreglos para
	declare -a letras_usadas
	declare -a dummy
	letras_usadas[0]=' '
	inicializa_palabra
	inicializa_hidden

	#Inicializa variables
	letras_restantes=${#palabra[@]}
	vidas=6
	
	#Banderas para condicionales
	juego_activo=1
	letra_usada=0
	adivina=-1
	entrada=-1

	while [[ $juego_activo -eq 1 ]]; do

		#Interfaz del usuario

		#Cabecera
		cabecera
		
		#Si no se ha ingresado una letra.
		if [[ $entrada -eq 0 ]]; then
			echo -e "\E[1;33m»\E[1;34m No has ingresado una letra en el comando.\n"

		#Si la letra ingresada ya fue usada...
		elif [[ $letra_usada -eq 1 ]]; then
			echo -e "\E[1;33m»\E[1;34m Ya usaste esta letra.\n"
		
		#Si la letra ingresada fue adivinada.
		elif [[ $adivina -eq 1 ]]; then 
			echo -e "\E[1;33m»\E[1;32m Has adivinado la letra $letra!\n"
			#echo "${letras_usadas[*]}"
		
		#Si se ha fallado al adivinar una letra.
		elif [[ $adivina -eq 0 ]]; then
			echo -e "\E[1;33m»\E[1;31m Has cometido un grave error.\n"
			let vidas=vidas-1

		#Default
		else echo -e '\n'
		fi

		#Cuerpo (donde se desarrolla la acción)
		dibujo
		#echo "${palabra[*]}"
		echo -e "\t\t\t\E[1;33m${hidden[*]}\n\E[0m"	
		#echo "${letras_usadas[*]}"
		echo -e "\t\E[1;32m┌─────────────────────────────────────────────────────────────┐"
		echo -e "\E[1;32m        │  \E[1;36mLetras totales: \E[1;37m${#palabra[@]} \t\E[1;36mLetras restantes: \E[1;37m$letras_restantes \t \E[1;36mVidas: \E[1;37m$vidas     \E[1;32m│"
		echo -e "\t\E[1;32m└─────────────────────────────────────────────────────────────┘\n"

		#Si se acabaron las vidas, termina el juego y recoge los juguetes.
		if [[ $vidas -eq 0 ]]; then
			echo -e "\E[1;33m»\E[1;31m Fin del juego. «"
			echo -e -n "\E[1;33m»\E[1;34m Presiona Enter para continuar..."
			read
			unset dummy
			unset palabra
			unset letras_usadas
			unset hidden
			break
		fi

		#Si se ha adivinado la palabra, termina el juego y recoge los juguetes.
		if [[ $letras_restantes -eq 0 ]]; then
			echo -e "\E[1;33m»\E[1;32m Felicidades, has adivinado toda la palabra! «"
			echo -e -n "\E[1;33m»\E[1;34m Presiona Enter para continuar..."
			read
			unset dummy
			unset palabra
			unset letras_usadas
			unset hidden
			break
		fi

		#Prompt del usuario
		echo -e -n "\E[1;33m»\E[1;34m Ingrese comando:\E[0m "
		read comando letra

		#Comando para leer la letra.
		if [[ $comando = "adivina" && $letra ]]; then
			
			#Funciones a realizar requeridas para la cabecera del siguiente turno.
			
			#Checa si se ingreso una letra.		
			if [[ $letra =~ [[:alpha:]] ]]; then
				entrada=1
				adivina=0
				letra_usada=0
				
				#Checa por la letra ingresada ya fue usada antes.
				for scout in $letras_usadas; do
					if [ $scout = "$letra" ]; then
						letra_usada=1
						break
					fi
				done

				#Añade las letras usadas para futura referencia.
				letras_usadas+="$letra "

				#Si es letra nueva...
				if [[ $letra_usada -eq 0 ]]; then

					#Checa las letras que coinciden en la palabra y las "revela"
					for (( i = 0; i < ${#palabra[@]}; i++ )); do
						if [[ $letra = "${palabra[$i]}" ]]; then
							hidden[$i]=${palabra[$i]}
							let letras_restantes=letras_restantes-1
							adivina=1
						fi
					done
				fi
			fi
			#Si no se ingresa la letra.
		elif [[ $comando = "adivina" && !$letra ]]; then
				entrada=0
				
		#Comando para mostrar la ayuda (comandos) del juego
		elif [[ $comando = "ayuda" ]]; then
			ayuda
			echo -e -n "\E[1;33m»\E[1;34m Presione Enter para continuar..."
			read
			
		#Comando para salir del juego
		elif [[ $comando = "salir" ]]; then 
			salir

		#Comando erroneo	
		else 
			echo -e "\E[1;33m»\E[1;34m Comando desconocido."
			echo -e -n "\E[1;33m»\E[1;34m Presione Enter para continuar..."
			read
		fi
	done
}

while [[ $salir != "S" || $salir != "s" ]];
do 
	cabecera
	echo -e "\E[1;33m»\E[1;34m Usa el comando \"jugar\" para iniciar.\n"
	echo -e -n "\E[1;33m»\E[1;34m Ingrese comando:\E[0m "
	
	read comando extra

	if [[ $comando = "adivina" || ( $comando = "adivina" && $extra ) ]]; then
		echo -e "\E[1;33m»\E[1;34m Este comando sólo se puede usar al iniciar un juego."
		echo -e -n "\E[1;33m»\E[1;34m Presione Enter para continuar..."
		read
	elif [[ $extra ]]; then
		echo -e "\E[1;33m»\E[1;34m El comando ingresado no tiene argumentos."
		echo -e -n "\E[1;33m»\E[1;34m Presione Enter para continuar..."
		read

	#Comando para adivinar la letra
	elif [[ $comando = "jugar" ]]; then
		jugar
		
	#Comando para mostrar la ayuda (comandos) del juego
	elif [[ $comando = "ayuda" ]]; then
		ayuda
		echo -e -n "\E[1;33m»\E[1;34m Presione Enter para continuar..."
		read

	#Comando para salir del juego
	elif [[ $comando = "salir" ]]; then 
		salir
	
	#Comando erroneo	
	else 
		echo -e "\E[1;33m»\E[1;34m Comando desconocido."
		echo -e -n "\E[1;33m»\E[1;34m Presione Enter para continuar..."
		read
	fi
done