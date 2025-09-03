#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <arquivo_binario>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Erro ao abrir arquivo");
        return 1;
    }

    long size = lseek(fd, 0, SEEK_END); // pega tamanho total
    if (size == (long)-1)
    {
        fprintf(stderr, "Erro em lseek (SEEK_END)");
        close(fd);
        return 1;
    }

    long pos = 0;
    unsigned char byte;
    int n;
    long long count = 0;

    while (pos < size)
    {
        // move cursor para posição "pos"
        if (lseek(fd, pos, SEEK_SET) == (long)-1)
        {
            fprintf(stderr, "Erro em lseek (SEEK_SET)");
            close(fd);
            return 1;
        }

        // lê 1 byte
        n = read(fd, &byte, 1);
        if (n < 0)
        {
            fprintf(stderr, "Erro em read");
            close(fd);
            return 1;
        }
        else if (n == 0)
        {
            break; // EOF
        }

        if (byte == '\0')
        {
            count++;
        }

        pos++;
    }

    printf("Arquivo: %s\n", argv[1]);
    printf("Tamanho: %lld bytes\n", (long long)size);
    printf("Bytes nulos encontrados: %lld\n", count);

    close(fd);
    return 0;
}
