#include <stdio.h>
// mark halim
// 5827 4708
// Global variable to keep track of the round number
int roundNum = 0;

// Required function
void round_result(int *board, int n) {
    int *pStart = board;
    int *pEnd = board + n - 1;
    int john_sum = 0;
    int marjorie_sum = 0;
    int marjorieTurn;

    // Determine who starts this round
    if (roundNum % 2 == 0)
        marjorieTurn = 1;  // Marjorie starts
    else
        marjorieTurn = 0;  // John starts

    while (pStart <= pEnd) {
        int *pPick;

        // Both players pick the largest available number
        if (*pStart >= *pEnd)
            pPick = pStart;
        else
            pPick = pEnd;

        // Add the picked number to the current player's sum
        if (marjorieTurn)
            marjorie_sum += *pPick;
        else
            john_sum += *pPick;

        // Remove the picked number from the board
        if (pPick == pStart)
            ++pStart;
        else
            --pEnd;

        // Switch turns
        marjorieTurn = !marjorieTurn;
    }

    // Print the result
    if (marjorie_sum > john_sum)
        printf("Marjorie\n");
    else if (john_sum > marjorie_sum)
        printf("John\n");
    else
        printf("Draw\n");
}

int main() {
    int num_of_rounds;  // T
    scanf("%d", &num_of_rounds);  // Read the number of rounds

    // Validate the number of rounds
    if (num_of_rounds < 1 || num_of_rounds > 100)
        return 1;

    // Process each round
    while (num_of_rounds--) {
        int n;
        scanf("%d", &n);

        // Validate the number of numbers on the board
        if (n < 1 || n > 1000)
            return 1;

        int board[1000];  // Maximum size as per constraints
        int *p = board;
        int *pEnd = board + n;

        // Read the numbers into the board
        while (p < pEnd) {
            scanf("%d", p);
            ++p;
        }

        // Call the required function
        round_result(board, n);

        // Increment the round number without using counter variables
        ++roundNum;
    }
    return 0;
}
