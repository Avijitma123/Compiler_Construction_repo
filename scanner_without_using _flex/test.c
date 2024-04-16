#include <stdio.h>
#include <string.h>

#define NUM_STATES 10
#define NUM_CHARS 2

// Define the corrected transition table
int transition[NUM_STATES][NUM_CHARS] = {
    {1, 2},   // State 0: Initial state
    {-1, 2},  // State 1: Accepting state for '0'
    {3, 4},   // State 2: Accepting state for '1'
    {-1, 4},  // State 3: Accepting state for '10'
    {5, -1},  // State 4: Accepting state for '010'
    {6, -1},  // State 5: Accepting state for '011'
    {7, -1},  // State 6: Accepting state for '110'
    {-1, 8},  // State 7: Accepting state for '1001'
    {-1, 9},  // State 8: Accepting state for '10110'
    {5, 9}    // State 9: Accepting state for '01010'
};



int isAccepted(char *input) {
    int state = 0;
    int len = strlen(input);

    for (int i = 0; i < len; i++) {
        char currentChar = input[i];
        int charIndex = currentChar - '0'; // Convert char to index (0 or 1)

        if (charIndex < 0 || charIndex > 1) {
            return 0; // Invalid input character
        }

        state = transition[state][charIndex];

        if (state == -1) {
            return 0; // Invalid transition, not accepted
        }
    }

    // Check if the final state is an accepting state
    return (state != -1);
}

int main() {
    char input[100];

    while (1) {
        printf("Enter a string (or type 'exit' to quit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        if (strcmp(input, "exit") == 0) {
            break;
        }

        if (isAccepted(input)) {
            printf("Accepted\n");
        } else {
            printf("Not Accepted\n");
        }
    }

    return 0;
}

