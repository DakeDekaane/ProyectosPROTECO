#!/bin/bash

function busca() {
	for file in "$2"/*;do
		if [[ -d "$file" ]];then
			busca "$1" "$file"
		elif [[ -f "$file" ]]; then
			archivo=`echo -e "$file" | grep -E -o "[][a-zA-Z0-9_─–\.\+\(\)\ \'\!\-]*$"`
			if [[ $archivo = $1 ]]; then
				echo -e "\E[1;32mArchivo encontrado:\E[0m $file"
				archivo_encontrado=1
			fi
		fi
	done
}

archivo_encontrado=0
if [[ $# -lt 2 ]]; then
	echo -e "\E[1;31mFaltan argumentos.\E[1;37m Sintáxis: busca [archivo] [directorio].\E[0m"
else
	busca $1 $2
	if [[ archivo_encontrado -eq 0 ]]; then
		echo -e 	"\E[1;31mNo se encontró el archivo."
	fi
fi
