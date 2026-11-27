#include "utils.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    double result = 0;

    // If an expression is passed via command line arguments (e.g ./calculator "3+4*5")
    if (argc > 1) {
        result = eval(argv[1]);
        printf("Result: %lf\n", result);
        return 0;
    }

    // If no cmdline argument then a normal prompt
    char expression[256]; // the expression(string so that they can write a multitude of operators at a time e.g 3+4/5)
    printf("Simple C Calculator (type 'exit' to quit)\n");
    printf("FAIR WARNING: DOESN'T FOLLOW BODMAS OR PEMDAS OR WHATEVER YOU FOLLOW!!!\n\n\n");

    while (1) {
        // Gets the expression and stores it at well, expression
        printf("Enter expression: ");
        // Breaks the loop if the input is NULL
        if (fgets(expression, sizeof(expression), stdin) == NULL) {
            break;
        }

        // Removes newline character if present
        expression[strcspn(expression, "\n")] = '\0';

        // Checks for exit command
        if (strcmp(expression, "exit") == 0 || strcmp(expression, "quit") == 0) {
            break;
        }

        // Re-iterates through the loop if the length of the expression is 0(meaning no expression)
        if (strlen(expression) == 0) {
            printf("Not cool man, enter a calculation, don't just press enter!!(or whatever it is you did)\n");
            continue;
        }

        // Evaluates the result and prints it.
        result = eval(expression);
        printf("Result: %lf\n", result);
    }

    return 0;
}