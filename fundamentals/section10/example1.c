#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt;
    bool flag_n = false;
    bool flag_f = false;

    while ((opt = getopt(argc, argv, "nf")) != -1) {
        switch (opt) {
            case 'n':
                flag_n = true;
                break;
            case 'f':
                flag_f = true;
                break;
            default:
                fprintf(stderr, "Usage: %s [-n] [-f]\n", argv[0]);
                return 1;
        }
    }

    if (flag_n) {
        printf("Flag -n is set.\n");
    }
    if (flag_f) {
        printf("Flag -f is set.\n");
    }

    return 0;
}