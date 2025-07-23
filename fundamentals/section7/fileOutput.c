#include <stdio.h>
#include <fcntl.h> // For open()
#include <unistd.h> // For write() and close()
#include <string.h> // For strlen()

int main(int argc, char *argv[]) {
    // Check if the filename is provided as a command line argument
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    // Open the file descriptor for reading and writing, create it if it doesn't exist
    // and set the file permissions to rw-r--r--
    int fd = open(argv[1], O_RDWR | O_CREAT, 0644);

    // Check if the file was opened successfully
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    char *buffer = "Hello, World!\n";
    write(fd, buffer, strlen(buffer)); // Write the string to the file
    close(fd); // Close the file descriptor
    return 0;
}