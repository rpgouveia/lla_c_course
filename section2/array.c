#include <stdio.h>

int main(int argc, char **argv) {

    // create an array of 10 integers 
    int myarray[10] = {7,4,1};

    // set the 4th element to 2
    myarray[3] = 2;

    // print the 4th element
    printf("%d\n", myarray[3]);

    return 0;

}