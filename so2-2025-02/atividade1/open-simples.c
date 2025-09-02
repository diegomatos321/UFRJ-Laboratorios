#include <io.h> // For _open, _close
#include <fcntl.h> // For file access modes like _O_RDONLY, _O_WRONLY, _O_CREAT
#include <stdio.h> // For perror

int main()
{
    char c;
    int in, out; /* serão usados como descritores de arquivos */
    in = open("file.in", O_RDONLY);
    out = open("file.out", O_WRONLY | O_CREAT);
    while (read(in, &c, 1) == 1)
        write(out, &c, 1);
}