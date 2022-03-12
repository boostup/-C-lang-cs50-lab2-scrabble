#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include "tests.utils.h"
#include "scrabble.h"

bool testInvalidChars();
bool testIgnoreCase();
bool testForTie();
bool testForWinner();

int main(void)
{
    printStartMessage();

    bool test1 = testInvalidChars();
    printTestResult("Test Invalid Characters", test1);

    bool test2 = testIgnoreCase();
    printTestResult("Ensure same score for same letters of different case", test2);

    bool test3 = testForTie();
    printTestResult("Ensure ties are detected", test3);

    bool test4 = testForWinner();
    printTestResult("Ensure winner is detected", test4);

    return test1
           //
           && test2
           //
           && test3
           //
           && test4
        //
        ;
}

bool testInvalidChars()
{

    // Assertion :
    // Invalid characters don't count, so if only invalid chars are passed as a word to `compute_score`, then it should return a scroe of 0
    bool assert1 = compute_score("0123456789") == 0;
    bool assert2 = compute_score("/*-+/.,!@#$%%^&*(){}[]~ \n\t") == 0;

    return assert1
           //
           && assert2;
}

bool testIgnoreCase()
{
    bool assert1 = compute_score("abcxyz") == compute_score("ABCXYZ");
    return assert1;
}

bool testForTie()
{
    bool assert1 = compute_score("Computer") == compute_score("retupmoC");
    return assert1;
}

bool testForWinner()
{
    // Player 2 should be the winner
    bool assert1 = compute_score("Computer") < compute_score("reQtuJpmoC");

    // Player 1 should be the winner
    bool assert2 = compute_score("reQtuJpmoC") > compute_score("Computer");

    return assert1 && assert2;
}