#!/bin/bash
# conta_tipos.sh
# Uso: ./conta_tipos.sh /caminho/para/diretorio

if [ $# -ne 1 ]; then
  echo "Uso: $0 <diretorio>"
  exit 1
fi

DIR="$1"

if [ ! -d "$DIR" ]; then
  echo "Erro: '$DIR' não é um diretório válido."
  exit 1
fi

# Contagens
TXT=$(find "$DIR" -type f -iname '*.txt' 2>/dev/null | wc -l)
SH=$(find "$DIR" -type f -iname '*.sh' 2>/dev/null | wc -l)
LOG=$(find "$DIR" -type f -iname '*.log' 2>/dev/null | wc -l)
TOTAL=$(find "$DIR" -type f 2>/dev/null | wc -l)

# Calcular outros (prevenindo negativos)
OUTROS=$(( TOTAL - TXT - SH - LOG ))
if [ $OUTROS -lt 0 ]; then
  OUTROS=0
fi

echo "TXT: $TXT"
echo "SH: $SH"
echo "LOG: $LOG"
echo "Outros: $OUTROS"
