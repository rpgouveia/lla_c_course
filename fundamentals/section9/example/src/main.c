#include <stdio.h>
#include "file.h"
#include "parse.h"

int main(int argc, char *argv[]) {
    int fd, numEmployees;
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    fd = open_file_rw(argv[1]);
    if (fd == -1) {
        printf("Error opening file %s\n", argv[1]);
        return -1;
    }
    if (parse_file_header(fd, &numEmployees)) {
        printf("Error parsing file header\n");
        return -1;
    }

    printf("Number of employees: %d\n", numEmployees);

    return 0;
}
