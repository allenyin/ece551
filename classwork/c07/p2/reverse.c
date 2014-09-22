#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
    int len = strlen(str);
    char * end = str+len-1;
    char temp;

    while (end > str) {
        // save the *str in temp
        temp = *str;
        // replace *str with *end
        *str = *end;
        // put str to the end
        *end = temp;
        // increment pointers
        end--;
        str++;
    }
}

int main(int argc, char ** argv) {
    if (argc == 1) {
        // nothing is entered for us to reverse
        return EXIT_SUCCESS;
    }
    else {
        char buffer[500] = 
    

    return EXIT_SUCCESS;
}
