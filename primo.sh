#!/bin/bash
# primo.sh

echo "Verificador de números primos. Digite 'q' para sair."

while true; do
  read -rp "Digite um número inteiro: " RESPOSTA

  # sair
  if [[ "$RESPOSTA" =~ ^[Qq]$ || "$RESPOSTA" =~ ^(sair|exit)$ ]]; then
    echo "Encerrando."
    exit 0
  fi

  # valida inteiro (aceita negativos, mas considera primos apenas >= 2)
  if ! [[ "$RESPOSTA" =~ ^-?[0-9]+$ ]]; then
    echo "Entrada inválida. Digite um número inteiro ou 'q' para sair."
    continue
  fi

  N=$RESPOSTA

  if [ "$N" -lt 2 ]; then
    echo "$N não é um número primo."
    continue
  fi

  is_primo=1
  for (( i=2; i*i<=N; i++ )); do
    if (( N % i == 0 )); then
      echo "$N NÃO é primo (divisível por $i)."
      is_primo=0
      break
    fi
  done

  if [ $is_primo -eq 1 ]; then
    echo "$N é um número primo."
  fi
done
