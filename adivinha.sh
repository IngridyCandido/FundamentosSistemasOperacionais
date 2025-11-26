#!/bin/bash
$(( RANDOM % 50 + 1 ))
while 
do
	echo "Me dê um palpite de qual o número."
	read RESPOSTA 
	if test $RESPOSTA -lt 
	then echo "Muito baixo"
	else test $RESPOSTA -gt 
	then echo "Muito alto"
	 VEZ ++1 
done
	
