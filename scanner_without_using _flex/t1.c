#include <stdio.h>
#include <stdlib.h>
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


// Define a struct to associate a string with its accepting state
typedef struct {
    char *string;       // String representing the token
    int accepting_state; // Corresponding accepting state
} TokenInfo;

// Array to store strings and corresponding accepting states
TokenInfo token_info[] = {
    {"0", 1},
    {"1", 2},
    {"10", 3},
    {"010", 4},
    {"011", 5},
    {"110", 6},
    {"1001", 7},
    {"10110", 8},
    {"01010", 9}
};

/**
 * Check if a substring is a valid token.
 * 
 * input The input string.
 * start The starting index of the substring.
 * end The ending index of the substring.
 * int Returns 1 if the substring is a valid token, otherwise returns 0.
 */
int isToken(char *input, int start, int end) {
    int state = 0;

    for (int i = start; i <= end; i++) {
        char currentChar = input[i];
        int charIndex = currentChar - '0'; // Convert char to index (0 or 1)

        if (charIndex < 0 || charIndex > 1) {
            return 0; // Invalid input character
        }

        state = transition[state][charIndex];

        if (state == -1) {
            return 0; // Invalid transition, not a token
        }
    }

    // Check if the final state is an accepting state
    for (int i = 0; i < sizeof(token_info) / sizeof(token_info[0]); i++) {
        if (token_info[i].accepting_state == state) {
            // If the current state is an accepting state,
            // check if the string matches the input substring
            int len = end - start + 1;
            if (strlen(token_info[i].string) == len &&
                strncmp(token_info[i].string, input + start, len) == 0) {
                return 1; // Valid token found
            }
        }
    }
    return 0; // Not a valid token
}

/**
 * Print the sequence of maximal length tokens.
 * 
 * input The input string.
 */
void printMaximalTokens(char *input) {
    int n = strlen(input);
    int dp[n + 1]; // Dynamic programming table to store the maximal length ending at index i
    int prev[n + 1]; // Array to store the previous index for each maximal length ending at index i
    memset(dp, 0, sizeof(dp)); // Initialize dp array with 0
    memset(prev, -1, sizeof(prev)); // Initialize prev array with -1

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        prev[i] = prev[i - 1];

        for (int j = 0; j < i; j++) {
            if (isToken(input, j, i - 1)) {
                int tokenLength = i - j;
                if (dp[i] < dp[j] + tokenLength) {
                    dp[i] = dp[j] + tokenLength;
                    prev[i] = j;
                }
            }
        }
    }

    // Print the sequence of maximal length tokens
    int index = n;
    while (index > 0) {
        int startIndex = prev[index];
        printf("<");
        for (int i = startIndex; i < index; i++) {
            printf("%c", input[i]);
        }
        printf(">");
        index = startIndex;
        if (prev[index] != -1) {
            printf(" ");
        }
    }
    printf("\n");
}

/**
 *  Main function.
 * 
 * argc Number of command-line arguments.
 * argv Array of command-line arguments.
 * int Returns 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        printf("Usage: %s input_filename\n", argv[0]);
        return 1;
    }

    char input[100];
    FILE *file = fopen(argv[1], "r");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read the input string from the file
    while (fgets(input, sizeof(input), file)) {
        // Remove newline character, if present
        input[strcspn(input, "\n")] = '\0';
        
        // Filter out characters other than '0' and '1'
        int len = strlen(input);
        int j = 0;
        for (int i = 0; i < len; i++) {
            if (input[i] == '0' || input[i] == '1') {
                input[j++] = input[i];
            }
        }
        input[j] = '\0';

        // Print the sequence of maximal length tokens
        printMaximalTokens(input);
    }

    // Close the file
    fclose(file);

    return 0;
}

