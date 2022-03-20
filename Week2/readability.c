#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int toascii(int c);

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int get_grade_level(int letters, int words, int sentences);

int main(void)
{
    string sample = get_string("Text to be analysed, please: \n");
    int letter_count = count_letters(sample);
    int word_count = count_words(sample);
    int sentence_count = count_sentences(sample);
    int grade_level = get_grade_level(letter_count, word_count, sentence_count);

    // printf("%i letters\n", letter_count);
    // printf("%i words\n", word_count);
    // printf("%i sentences\n", sentence_count);

    printf("%sGrade %i%s\n",
           grade_level < 1 ? "Before " : "",
           grade_level < 1 ? 1 : grade_level >= 16 ? 16
                                                   : grade_level,
           grade_level >= 16 ? "+" : "");
}

int count_letters(string text)
{
    int count = 0;

    // loop through chars in text string
    for (int i = 0; i < strlen(text); i++)
    {
        // printf("%c", text[i]);
        // increase count when char is a letter
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    // printf("\n");

    return count;
}

int count_words(string text)
{
    int count = 0;

    // loop through chars in text string
    for (int i = 0; i < strlen(text); i++)
    {
        // increase count when char is a space
        if (isspace(text[i]))
        {
            count++;
        }
    }

    // Amount of words is the number of spaces found + 1
    return count + 1;
}

int count_sentences(string text)
{
    int count = 0;

    // loop through chars in text string
    for (int i = 0; i < strlen(text); i++)
    {
        // printf("%c\t", text[i]);

        // get char's ascii code for easier detection of the type of chars we'r looking for here, namely:
        // 33 => !   46 => .    63 => ?
        int ascii_code = toascii(text[i]);

        // increase count when char is punctuation
        if (ascii_code == 33 || ascii_code == 46 || ascii_code == 63)
        {
            count++;
            // printf("%i\t", ascii_code);
        }
    }

    // Amount of sentences is the number of end-of-sentence punctuation marks found
    return count;
}

int get_grade_level(int letters, int words, int sentences)
{

    float L = (float)letters * 100 / words;
    // printf("L: %f\n", L);

    float S = (float)sentences * 100 / words;
    // printf("S: %f\n", S);

    // printf("raw: %f\n", 0.0588 * L - 0.296 * S - 15.8);

    return round(0.0588 * L - 0.296 * S - 15.8);
}