#!/bin/bash
# menu.sh

while true; do
  clear
  echo "MENU"
  echo "1 - Mostrar data e hora"
  echo "2 - Mostrar usuário atual"
  echo "3 - Listar arquivos"
  echo "0 - Sair"
  echo
  read -rp "Digite o número da opção desejada: " RESPOSTA

  case "$RESPOSTA" in
    1)
      echo
      date
      ;;
    2)
      echo
      whoami
      ;;
    3)
      echo
      ls -la
      ;;
    0)
      echo "Saindo..."
      exit 0
      ;;
    *)
      echo "Opção inválida. Tente novamente."
      ;;
  esac

  echo
  read -rp "Pressione Enter para voltar ao menu..." _
done
