#!/bin/bash

num=$1
# Loop para contar até zero
while [ $num -ge 0 ]; do
  echo -n "$num "  # -n impede a quebra de linha
  num=$((num-1))
done

echo
