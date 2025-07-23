#include <stdio.h>
#include <fcntl.h> // For open()
#include <unistd.h> // For write() and close()
#include <string.h> // For strlen()
#include <sys/stat.h> // For struct stat

/*
    Setup Test File Header:
    echo -ne "\x01\x00\x41\x00\x08\x00\x00\x00" > ./my-db.db

    Check Test File Header:
    hexdump -C ./my-db.db 
    or
    xxd ./my-db.db 
*/

// This program reads a database header from a file and prints its contents
struct database_header {
    unsigned short version;
    unsigned short employees;
    unsigned int file_size;
};


int main(int argc, char *argv[]) {
    // Initialize the header with default values
    struct database_header header = {0};
    struct stat db_header_stat = {0};

    // Check for valid command line arguments
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 0;
    }
    
    // Open the file for reading and writing, create it if it doesn't exist
    int fd = open(argv[1], O_RDWR | O_CREAT, 0644);

    // Check if the file was opened successfully
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    // Read the header from the file
    ssize_t bytesRead = read(fd, &header, sizeof(header));
    if (bytesRead != sizeof(header)) {
        perror("Error reading file header");
        close(fd);
        return -1;
    }

    // Print the header information
    printf("DB Header Information\n");
    printf("DB Version: %u\n", header.version);
    printf("DB Number of Employees: %u\n", header.employees);
    printf("DB File Size: %u\n", header.file_size);

    // Check metadata of the file using stat
    // Get the file status using fstat
    int fstat_result = fstat(fd, &db_header_stat);
    if (fstat_result == -1) {
        perror("Error getting file status");
        close(fd);
        return -1;
    }
    printf("DB File Size (fstat): %lu bytes\n", (unsigned long)db_header_stat.st_size);

    /*
        Modify the header for testing purposes
        echo -ne "\x01\x00\x41\x00\x08\x09\x00\x00" > ./modified-db.db
    */

    // Validate the file size from the header against the actual file size
    if (db_header_stat.st_size != header.file_size) {
        fprintf(stderr, "File size mismatch: expected %lu bytes, received %u bytes\n", (unsigned long)db_header_stat.st_size, header.file_size);
        close(fd);
        return -2;
    }

    // Close the file descriptor
    close(fd);
    return 0;
}