#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>   
#include <fcntl.h>
#include "file.h"

int open_file_rw(char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        return fd;
    }
    return fd;
}
