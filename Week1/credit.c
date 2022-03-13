#include "cs50.h"
#include "stdio.h"
#include "string.h"
#include <math.h>

bool checkSum(long cardNum);
int getDigitsCount(long cardNum);
void printCardIssuerName(long cardNum);

int main(void)
{
    long cardNum = get_long("Please enter a card number:\n");

    if (checkSum(cardNum))
        printCardIssuerName(cardNum);

    else
        printf("INVALID\n");

    return 0;
}

// take every other digits, start at the second-to-last digit
// multiply by 2 every one of the selected digits
// than add all products together
// take that sum and add it to all the digits that were not selected
// if the last digit of that sum is zero, than the card number satisfies the checksum
bool checkSum(long cardNum)
{
    // printf("%lu\n", cardNum);
    int i = 0;
    long quotient = cardNum;
    int reminder;
    int result = 0;
    int sumOddDigits = 0;
    do
    {
        i++;
        reminder = quotient % 10;
        quotient = quotient / 10;

        // printf("%i | %s | reminder: %i | quotient: %lu\n",
        //        i,
        //        (i % 2 == 0) ? "even" : "odd",
        //        reminder,
        //        quotient);

        if (i % 2 == 0)
        {
            int product = reminder * 2;
            if (product > 9)
                product = (product % 10) + floor(product / 10);
            result += product;
        }
        else
            sumOddDigits += reminder;

        // printf("%s | reminder: %i - result: %i - sumOdd: %i\n", (i % 2 == 0) ? "even" : "odd", reminder, result, sumOddDigits);

    } while (quotient != 0);

    result += sumOddDigits;
    // printf("%i\n", result);

    if (result % 10 == 0)
        return true;
    return false;
}

int getDigitsCount(long cardNum)
{
    int count = 0;
    long temp = cardNum;
    while (temp)
    {
        temp /= 10;
        count++;
    }
    return count;
}

// American Express uses 15-digit numbers | possible prefixes {34, 37}
// MasterCard uses 16-digit numbers | possible prefixes {51, 52, 53, 54, 55}
// Visa uses 13- and 16-digit numbers | possible prefixes {4}
void printCardIssuerName(long cardNum)
{
    int digitsCount = getDigitsCount(cardNum);
    int firstTwoDigits = cardNum / (pow(10, digitsCount - 2));
    int firstDigit = floor(firstTwoDigits / 10);

    // printf("# digits: %i | 1st Digit: %i\n", digitsCount, firstDigit);

    string issuer = "INVALID";

    // if length is 15 and prefix is 34 or 37 => print AMEX
    if (digitsCount == 15)
    {
        if (firstTwoDigits == 34 || firstTwoDigits == 37)
            issuer = "AMEX";
    }
    // if length is 16,
    else if (digitsCount == 16)
    {
        // then if prefix is 51, 52, 53, 54 or 55 => print MASTERCARD
        if (firstTwoDigits == 51 || firstTwoDigits == 52
            //
            || firstTwoDigits == 53 || firstTwoDigits == 54
            //
            || firstTwoDigits == 55)
            issuer = "MASTERCARD";

        // if is 4 => print VISA
        if (firstDigit == 4)
            issuer = "VISA";
    }
    //  if length is 13 and prefix is 4 => print VISA
    else if (digitsCount == 13 && firstDigit == 4)
        issuer = "VISA";

    printf("%s\n", issuer);
}