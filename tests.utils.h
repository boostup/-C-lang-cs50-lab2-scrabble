#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

int testNumber = 0;

void printStartMessage()
{
    printf("\n");
    printf("/**************************\n");
    printf("/\tTests Results\n");
    printf("/**************************\n");
}

void printTestResult(string testName, bool didPass)
{
    testNumber++;
    printf("\nTest #%i\n\t%s: %s\n", testNumber, testName, didPass
                                                               //
                                                               ? ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n"
                                                               //
                                                               : ANSI_COLOR_RED "failed" ANSI_COLOR_RESET "\n");
}