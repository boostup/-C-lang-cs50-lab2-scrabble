#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHA_ARRAY_SIZE 26
int uppercase_index[ALPHA_ARRAY_SIZE];
int lowercase_index[ALPHA_ARRAY_SIZE];

bool only_digits(string s);
int find_pos_in_arr(int val, int array[]);
void cipher(int key, string source);
void fillAlphaArray(string lettercase);

int main(int argc, string argv[])
{

    // argument validation
    if (argc != 2)
    {
        printf("Error: please provide a single command-line argument to execute this program (a single non-negative integer).\n");
        return 1;
    }

    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // We're ready to rock since all input validation was sucessful
    // Filling up arrays for upper and lower case indices
    fillAlphaArray("upper");
    fillAlphaArray("lower");

    // converts key to int
    int key = atoi(argv[1]);

    // capturing the text to be ciphered
    string plain_text = get_string("plaintext:  ");

    // ciphering & printing result
    printf("ciphertext: ");
    cipher(key, plain_text);

    // being nice to console prompt cursor position...
    printf("\n");

    // main returns with no errors
    return 0;
}

/**
 * This function checks that all characters contained in the string `s` are indeed all digits from 0-9
 * It returns true in this case.
 * It returns false immediately after finding a character which isn't a digit.
 */
bool only_digits(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// ASCII ranges for letters only
// Upper : 65 (A) - 90 (Z)
// Lower : 97 (a) - 122 (z)
// These arrays are filled with integer values which correspond to the ASCII values  pertaining to each letter of the alphabet
// This functions just automates the process of writing manually this sequence of ASCII values
// ie: uppercase index = {65,66,...,90}
// ie: lowercase index = {97,98,...,122}
void fillAlphaArray(string lettercase)
{
    for (int i = 0; i < ALPHA_ARRAY_SIZE; i++)
    {
        if (strcmp(lettercase, "upper"))
        {
            uppercase_index[i] = i + 'A';
        }
        if (strcmp(lettercase, "lower"))
        {
            lowercase_index[i] = i + 'a';
        }
    }
}

/**
 * Given a value and an array, this function returns it's position in the array.
 * Returns -1 if not found.
 */
int find_pos_in_arr(int val, int array[])
{
    for (int i = 0; i < ALPHA_ARRAY_SIZE; i++)
    {
        if (val == array[i])
        {
            return i;
        }
    }

    return -1;
}

void cipher(int key, string source)
{

    // loop through each character of plain text, and cipher it,
    for (int i = 0, source_size = strlen(source); i < source_size; i++)
    {
        char c = source[i];
        int cipher_c;
        // but only if it's a letter though
        if (isalpha(c))
        {
            // when char is uppercase
            if (isupper(c))
            {
                // printf("upper: %c\n", c);
                int pos = find_pos_in_arr(c, uppercase_index);
                int c_plus_key_mod = (pos + key) % 26;
                cipher_c = uppercase_index[c_plus_key_mod];
            }
            // when char is lowercase
            else
            {
                // printf("lower: %c\n", c);
                int pos = find_pos_in_arr(c, lowercase_index);
                int c_plus_key_mod = (pos + key) % 26;
                cipher_c = lowercase_index[c_plus_key_mod];
                // printf("%c, %i (%i + %i) => %%26 = %i (%c)\n", c, c + key, c, key, c_plus_key_mod, lowercase_index[c_plus_key_mod]);
            }
        }
        // and let's leave all non-letter characters `as is`
        else
        {
            cipher_c = c;
        }
        printf("%c", cipher_c);
    }
}