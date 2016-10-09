#!/bin/bash

memoria_total=`free -m | while read c1 c2 c3 c4 c5 c6 c7; do echo $c2; done | sed -n '2 p'`
memoria_libre=`free -m | while read c1 c2 c3 c4 c5 c6 c7; do echo $c3; done | sed -n '2 p'`
memoria_swap=`free -m | while read c1 c2 c3 c4 c5 c6 c7; do echo $c2; done | sed -n '3 p'`
sist_operativo=`uname -o`
distribucion=`lsb_release -d | while read c1 c2 ; do echo $c2; done`
kernel=`uname -r`
arquitectura=`arch`
modelo_procesador=`cat /proc/cpuinfo | grep -e "model\ name*"`
velocidad_procesador=`cat /proc/cpuinfo | grep -e "cpu\ MHz*"`
cache_procesador=`cat /proc/cpuinfo | grep -e "cache\ size*"`

echo -e "\E[1;32mMemoria total:\E[0m $memoria_total MB"
echo -e "\E[1;32mMemoria libre:\E[0m $memoria_libre MB"
echo -e "\E[1;32mMemoria swap:\E[0m $memoria_swap MB"
echo -e "\E[1;32mSistema operativo:\E[0m $sist_operativo"
echo -e "\E[1;32mDistribución:\E[0m $distribucion"
echo -e "\E[1;32mVersión del kernel:\E[0m $kernel"
echo -e "\E[1;32mArquitectura del procesador:\E[0m $arquitectura"
echo -e "\E[1;32mModelo de procesador:\E[0m \n$modelo_procesador"
echo -e "\E[1;32mVelocidad de procesador:\E[0m \n$velocidad_procesador"
echo -e "\E[1;32mMemoria caché:\E[0m \n$cache_procesador"