#ifndef PARSE_H
#define PARSE_H

struct database_header {
    unsigned short version;
    unsigned short count;
};

int parse_file_header(int fd, int *numEmployeesOut);

#endif