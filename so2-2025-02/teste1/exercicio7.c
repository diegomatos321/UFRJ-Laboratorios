/* 
    No Windows (MSVC) não existe ftruncate(), mas podemos usar _chsize()
*/

#include <stdio.h>
#include <fcntl.h>  // O_RDWR, O_BINARY
#include <string.h> // strlen

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <arquivo.txt>\n", argv[0]);
        return 1;
    }

    // Abre arquivo para leitura/escrita em modo binário
    int fd = open(argv[1], O_RDWR | O_BINARY);
    if (fd < 0)
    {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    // Pula até o byte 20
    long pos = _lseek(fd, 20, SEEK_SET);
    if (pos == -1L)
    {
        perror("Erro em lseek");
        close(fd);
        return 1;
    }

    // Escreve "FIM\n"
    const char *msg = "FIM\n";
    if (write(fd, msg, (unsigned)strlen(msg)) < 0)
    {
        perror("Erro em write");
        close(fd);
        return 1;
    }

    // Pega posição atual após write
    pos = _lseek(fd, 0, SEEK_CUR);
    if (pos == -1L)
    {
        perror("Erro em lseek (SEEK_CUR)");
        close(fd);
        return 1;
    }

    // Trunca arquivo no ponto atual
    if (_chsize(fd, pos) != 0)
    {
        perror("Erro em _chsize");
        close(fd);
        return 1;
    }

    printf("Arquivo \"%s\" truncado para %ld bytes.\n", argv[1], pos);

    close(fd);
    return 0;
}
