#!/bin/bash
#Sistema - Script que mostra informações sobre o sistema
#Autora: Ingridy Candido

echo "Vou buscar os dados do sistema. Posso continuar? [sn]"
read RESPOSTA
test "$RESPOSTA" = "n" && exit
echo "Data e Horário:"
date
echo 
echo "Uso do disco:"
df
echo
echo "Usuários conectados:"
w  | awk 'NR>2 {print $1}'| wc -l
