#!/bin/bash
# adivinha.sh

echo "Jogo da Adivinhação (1 a 50)"
echo "Digite 'q' a qualquer momento para sair."

while true; do
  # gera número aleatório
  SECRET=$(( RANDOM % 50 + 1 ))
  TRIES=0

  echo
  echo "Novo jogo iniciado!"

  while true; do
    read -rp "Seu palpite: " RESPOSTA

    # sair
    if [[ "$RESPOSTA" =~ ^[Qq]$ ]]; then
      echo "Você desistiu. O número era: $SECRET"
      exit 0
    fi

    # valida se é número
    if ! [[ "$RESPOSTA" =~ ^[0-9]+$ ]]; then
      echo "Digite um número válido entre 1 e 50."
      continue
    fi

    PALPITE=$RESPOSTA

    if [ "$PALPITE" -lt 1 ] || [ "$PALPITE" -gt 50 ]; then
      echo "Digite um número entre 1 e 50."
      continue
    fi

    TRIES=$((TRIES+1))

    if [ "$PALPITE" -lt "$SECRET" ]; then
      echo "Muito baixo"
    elif [ "$PALPITE" -gt "$SECRET" ]; then
      echo "Muito alto"
    else
      echo "Parabéns! Você acertou em $TRIES tentativas."

      read -rp "Jogar novamente? (s/n): " OPCAO

      if [[ "$OPCAO" =~ ^[Ss]$ ]]; then
        break   # sai desse loop e inicia outro jogo
      else
        echo "Obrigado por jogar!"
        exit 0
      fi
    fi
  done
done
