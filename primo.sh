#!/bin/bash
echo "Digite um número inteiro"
read RESPOSTA 
while test $RESPOSTA 
do
    if [ "$RESPOSTA" -lt 2 ]; then
        echo "$RESPOSTA não é um número primo."
        return 1
    fi

    for ((i=2; i*i <= RESPOSTA; i++)); do
        if [ $((RESPOSTA % i)) -eq 0 ]; then
            # Se encontrar um divisor, não é primo
            echo "$RESPOSTA não é um número primo (divisível por $i)."
            return 1
        fi
    done

    # Se o loop terminar sem encontrar divisores, é primo
    echo "$RESPOSTA é um número primo."
    return 0
}

# Verifica se um argumento foi fornecido na linha de comando
if [ $# -eq 0 ]; then
    echo "Uso: $0 <numero>"
    exit 1
fi
done


