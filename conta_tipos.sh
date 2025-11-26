#!/bin/bash

echo "Digite um diretório:"
read DIR

TXT=$DIR find -type f -iname "*.txt" 2> /dev/null | wc -l
SH=$DIR find -type f -iname "*.sh" 2> /dev/null | wc -l
LOG=$DIR find -type f -iname "*.log" 2> /dev/null | wc -l

TOTAL=$DIR find -type f | wc -l

OUTROS=$(( TOTAL - TXT - SH - LOG ))

echo "TXT: $TXT"
echo "SH: $SH"
echo "LOG: $LOG"
echo "Outros: $OUTROS"

