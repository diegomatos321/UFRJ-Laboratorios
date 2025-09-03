#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <nome_arquivo>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    // Open a file for reading and writing
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        fprintf(stderr, "Error opening file");
        return 1;
    }

    // Reposition the file pointer 0 bytes from the end of the file
    long new_offset = lseek(fd, 0, SEEK_END);
    printf("File size: %ld B\n", new_offset);

    close(fd);

    return 0;
}