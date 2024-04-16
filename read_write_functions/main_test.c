#include <stdio.h>

// Function prototypes for the functions in your .o file
int readInt(int *nP);
int printInt(int n);

int main() {
    int num;
    int readResult, printResult;

    // Test readInt function
    printf("Enter an integer: ");
    fflush(stdout);
    readResult = readInt(&num);

    if (readResult == 0) {
        printf("You entered: ");
        fflush(stdout);
        // Test printInt function
        printResult = printInt(num);

        if (printResult == 0) {
            printf("\n");
        } else {
            printf("\nError printing integer.\n");
        }
    } else {
        printf("\nError reading integer.\n");
    }

    return 0;
}

