#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int toascii(int c);
int compute_score(string word);

int compute_score(string word)
{
    // TODO: Compute and return score for string
    // Ignore non-letter chars
    // Handle bother upper and lowercase

    // ASCII ranges for letters only
    // Upper : 65 (A) - 90 (Z)
    // Lower : 97 (a) - 122 (z)
    int score = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        int points = 0;
        if (isupper(word[i]))
            points = POINTS[toascii(word[i]) - 65];
        if (islower(word[i]))
            points = POINTS[toascii(word[i]) - 97];

        // leaving the following line commented for future debugging purposes
        // printf("%c (ASCII: %i) / points: %i\n", word[i], toascii(word[i]), points);
        score += points;
    }

    // printf("%s\n", word);
    return score;
}
