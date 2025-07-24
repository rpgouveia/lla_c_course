#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

void print_usage(char *argv[]) {
    printf("Usage: %s [-n] [-f <filepath>]\n", argv[0]);
    printf("Options:\n");
    printf("  -n          Create a new file\n");
    printf("  -f <path>   Specify the file path\n");
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    bool newfile = false;
    int option;
    
    // Parse command line options
    while ((option = getopt(argc, argv, "nf:")) != -1) {
        switch (option) {
            case 'n':
                newfile = true;
                break;
            case 'f':
                filepath = optarg;
                break;
            case '?':
                printf("Unknown option: -%c\n", option);
                break; 
            default:
                return -1;
        }
    }

    printf("New file: %d\n", newfile);

    if (filepath == NULL) {
        printf("Filepath is required.\n");
        print_usage(argv);
        return 0;
    }
    printf("Filepath: %s\n", filepath);

    return 0;
}