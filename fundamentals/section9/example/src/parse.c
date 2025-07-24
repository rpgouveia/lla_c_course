#include <stdio.h>
#include <unistd.h>
#include "parse.h"
#include "common.h"

int parse_file_header(int fd, int *numEmployeesOut) {
    if (fd == -1) {
        printf("Bad file descriptor provided\n");
        return STATUS_ERROR;
    }
    struct database_header header = {0};
    if (read(fd, &header, sizeof(header)) != sizeof(header)) {
        printf("Error reading file header\n");
        return STATUS_ERROR;
    }

    *numEmployeesOut = header.count;
    return STATUS_SUCCESS;
}