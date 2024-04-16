#include <stdio.h>

// Function prototypes
int readInt(int *nP);
int printInt(int n);

// Function to read a single character from standard input
char readChar() {
    char c = 0;
    __asm__ __volatile__ (
        "movq $0, %%rax # 0 for read \n\t"
        "movq $0, %%rdi # 0 for stdin \n\t"
        "movq $1, %%rdx # 1 byte \n\t"
        "syscall \n\t"
        :
        :"S" (&c)
    );
    return c;
}

// Function to write a single character to standard output
void writeChar(char c) {
    __asm__ __volatile__ (
        "movq $1, %%rax # 1 for write \n\t"
        "movq $1, %%rdi # 1 for stdout \n\t"
        "movq $1, %%rdx # 1 byte \n\t"
        "syscall \n\t"
        :
        :"S" (&c)
    );
}

// Function to read an integer from standard input
int readInt(int *nP) {
    *nP = 0;
    char c;

    // Read characters until newline
    while ((c = readChar()) != '\n') {
        // Check for non-digit character
        if (c < '0' || c > '9') {
            return 1; // Error: Non-digit character encountered
            
        }

        // Convert the digit to its corresponding integer value
        *nP = (*nP * 10) + (c - '0');
    }
    
    return 0; // Successful read
}

// Function to print an integer to standard output
int printInt(int n) {
    int isNegative = 0;

    if (n < 0) {
        isNegative = 1;
        n = -n;
    }

    // Print optional negative sign
    if (isNegative) {
        writeChar('-');
    }

    // Recursive helper function to print digits
    int result = 0;
    if (n / 10 != 0) {
        result = printInt(n / 10);
    }

    // Check for a successful recursive print
    if (result != 0) {
        return result;
    }

    // Print the last digit
    writeChar('0' + n % 10);

    return 0; // Successful print
}

