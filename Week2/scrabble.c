#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include "scrabble.h"

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
        printf("Player 1 Wins! Score: %i - %i\n", score1, score2);

    else if (score2 > score1)
        printf("Player 2 Wins! Score: %i - %i\n", score1, score2);

    else
        printf("It's a tie!\n");
}