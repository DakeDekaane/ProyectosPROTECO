#!/bin/bash

#Funcion principal, explora cada directorio y su contenido recursivamente.
function arbol() {
	for file in "$1"/*; do
		for ((i=0; $i < $nivel; i++)); do
			echo -n "   "
		done
		if [[ -d "$file" ]]; then
			let nivel=nivel+1
			nombre=`echo -e "$file" | grep -E -o "[][a-zA-Z0-9_─–\.\+\(\)\ \'\!\-]*$"`
			echo -e " └─ \E[1;32m$nombre\E[0m"
			arbol "$file"
			let nivel=nivel-1
		elif [[ -f "$file" ]]; then
			nombre=`echo -e "$file" | grep -E -o "[][a-zA-Z0-9_─–\.\+\(\)\ \'\!\-]*$"`
			echo -e " └─ \E[1;33m$nombre\E[0m"
		fi
	done
}

nivel=0
arbol `pwd`