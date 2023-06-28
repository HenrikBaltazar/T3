#!/bin/bash

# Gerar uma sequência de números de 1 a 10000
seq 1 $1 > numeros.txt

# Embaralhar a sequência de números aleatoriamente
shuf -i 1-$1 -o numeros.txt --random-source=/dev/urandom

# Ler o arquivo e concatenar os números em uma única linha separados por espaços
tr '\n' ' ' < numeros.txt > $1_random.txt

# Remover o último espaço em branco da linha
sed -i 's/ $//' $1_random.txt

# Remover o arquivo temporário
rm numeros.txt