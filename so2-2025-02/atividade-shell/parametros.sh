# Contador inicial
i=1

# Percorre todos os parâmetros passados
for param in "$@"; do
  echo "Parâmetro $i: $param"
  i=$((i+1))
done
