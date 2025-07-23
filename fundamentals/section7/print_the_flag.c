/*
On the system, there is a file called /tmp/flag.
Using C programming and POSIX file operations, read the contents of that file 
to a buffer and print the contents of the flag to the screen.

You may use two types of file operations, either the syscall set open and read, 
or fopen and fread. All that matters is that you output the contents of the file.

Write a function called print_the_flag that reads the file and prints it to the 
screen. Don't forget a newline (\n)!

Extra!
For testing purposes, you can create the file with the following command:
echo "Este eh o conteudo da flag para teste do seu programa C." > /tmp/flag

To verify the contents of the file, you can use:
xxd /tmp/flag
*/

#include <fcntl.h> // For open
#include <stdio.h> // For printf, perror
#include <stdlib.h> // For malloc, free
#include <sys/stat.h> // For struct stat
#include <unistd.h> // For close, read

#define FILE_PATH "/tmp/flag"

void print_the_flag() {
    int file_descriptor;
    struct stat file_stat;
    char *buffer;
    ssize_t bytes_read;

    // 1. Open the file for reading
    file_descriptor = open(FILE_PATH, O_RDONLY);
    // Check if the file was opened successfully
    if (file_descriptor == -1) {
        perror("Error opening file");
        return;
    }

    // 2. Get the file size
    // Check the file size using fstat
    if (fstat(file_descriptor, &file_stat) == -1) {
        perror("Error getting file size");
        close(file_descriptor);
        return;
    }
    // Get the file size from the stat structure
    long file_size = file_stat.st_size;

    // 3. Allocate memory for the buffer
    buffer = (char *)malloc(file_size + 1); // +1 for null terminator
    // Check if memory allocation was successful
    if (buffer == NULL) {
        perror("Error allocating memory");
        close(file_descriptor);
        return;
    }

    // 4. Read the file contents into the buffer
    bytes_read = read(file_descriptor, buffer, file_size);

    // Check if the read operation was successful
    if (bytes_read == -1) {
        perror("Error reading file");
        free(buffer);
        close(file_descriptor);
        return;
    }

    if (bytes_read != file_size) {
        fprintf(stderr, "Error: Read %zd bytes, expected %ld bytes\n", bytes_read, file_size);
        free(buffer);
        close(file_descriptor);
        return;
    }

    // 5. Null-terminate the buffer
    buffer[bytes_read] = '\0';

    // 6. Print the contents of the buffer
    printf("%s\n", buffer);

    // 7. Clean up
    free(buffer);
    close(file_descriptor);
}

int main() {
    print_the_flag();
    return 0;
}