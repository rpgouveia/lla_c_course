#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

    /* The string "hehe" is represented in hex as 68 65 68 65 */

    // this is a string
    char *str = "hehe";

    // create the same string
    // as a character array 
    char otherstr[] = {0x68, 0x65, 0x68, 0x65, 0x00}; // with null terminator

    if (!strcmp(str, otherstr)) {
        printf("Yay!\n");
    } else {
        printf("Nay!\n");
    }

    return 0;
}