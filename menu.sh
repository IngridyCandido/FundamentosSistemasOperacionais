#!/bin/bash
while 
do 
	clear
	echo "MENU
	1 - DATA E HORA 
	2 - USUÁRIO ATUAL
	3 - LISTAR ARQUIVOS
	0 - SAIR"
	echo "Digite o número da opção desejada"
	read RESPOSTA
	if test "$RESPOSTA" = "1"
	then date 
	elif test "$RESPOSTA" = "2"
	then whoami
	elif test "$RESPOSTA" = "3"
	then ls
	else "$RESPOSTA" = "0"
	then && exit 
done
