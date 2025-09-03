#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <nome_arquivo>\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    // Open a file for reading and writing
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        fprintf(stderr, "Error opening file");
        return 1;
    }

    char buffer[101];
    // Read up to 100 bytes into the buffer (leaving space for null terminator if needed)
    int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1)
    {
        fprintf(stderr, "Error reading file");
        close(fd);
        exit(1);
    }

    long new_offset = lseek(fd, 200, SEEK_SET);

    // Read up to 100 bytes into the buffer (leaving space for null terminator if needed)
    bytes_read = read(fd, buffer, 50);
    if (bytes_read == -1)
    {
        fprintf(stderr, "Error reading file");
        close(fd);
        exit(1);
    }

    // Null-terminate the buffer if treating as a string
    buffer[50] = '\0';

    printf("%s", buffer);

    // Close the file descriptor
    close(fd);

    return 0;
}