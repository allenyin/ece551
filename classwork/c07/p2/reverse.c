#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 500

void printline(char buffer[], int size) {
    for (int i=0; i<size; i++) {
        printf("%c", buffer[i]);
    }
    printf("\n");
}

void reverse(char buffer[], int size) {
    if (size <= 1) {
        return;
    }
    char temp;
    temp = buffer[0];
    buffer[0] = buffer[size-1];
    buffer[size-1] = temp;
    reverse(buffer+1, size-2);
}

void reverse_helper(char buffer[]) {
    int len = strlen(buffer);
    if (buffer[len-1] == '\n') {
        reverse(buffer, len-1);
        printline(buffer, len-1);
    }
    else {
        reverse(buffer, len);
        printline(buffer, len);
    }
    return;
}

int main(void) {
    /* Program behavior:
     * After starting the program via "./reverse", the user keeps entering
     * input. The program stops taking inputs when EOF or "/n" is detected.
     * Then the reverse of the user input is outputted, and the program exits.
     */
     char buffer[BUFFER_SIZE];
     while ( (fgets(buffer, BUFFER_SIZE, stdin)!= NULL)) {
         
         reverse_helper(buffer);
     }
    return EXIT_SUCCESS;
}
