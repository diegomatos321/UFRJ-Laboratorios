gcc src/main.c -o build/main -Wall -lpthread -lm

valores_N=(1000 1000000 10000000)

# echo "Gerando relatório..."

for N in ${valores_N[@]}; do
    # echo "Para N = $N."

    for nThread in 1 2 4 8; do
        # echo "Para $nThread threads."

        for i in {1..5}; do
            ./main "$N" "$nThread"
        done

        # echo
    done

    # echo 
done
