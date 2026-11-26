#include "utils.h"
#include <ctype.h>
#include <stdbool.h>

void do_thing(double *result, int first_num, int second_num, char operator) {
    // Just your average calculator. Uses pointers so I don't have to reassign result
    switch (operator) {
        case '+':
            *result = first_num + second_num;
            break;
        case '-':
            *result = first_num - second_num;
            break;
        case '*':
            *result = first_num * second_num;
            break;
        case '/':
            *result = first_num / (double)second_num;
            break;
        case '%':
            *result = first_num % second_num;
    }
}

bool isoperator(char operator) {
    // Checks if a character is an operator
    switch (operator) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
            return true;
        default:
            return false;
    }
}

double eval(const char *expression) {
    int numbers[500] = {0};      // An array of 500 numbers to store your stupidly long math questions
    int operators[499] = {'\0'}; // An array of 500 - 1 operators to store all your operators

    // sets num count and operator count to 0, to avoid undefined behaviour
    int num_count, operator_count; // num count and operator count keep track on how many numbers and operators there are
    num_count = operator_count = 0;

    // sets first num and second num to 0, to avoid undefined behaviour
    int first_num, second_num;
    first_num = second_num = 0;

    double result = 0; // sets result to 0, to avoid undefined behaviour
    char operator;     // set to '\0', toooooooo........ avoid undefined behaviour

    // for loop to put numbers in numbers array, and operators in operators array
    for (int i = 0; expression[i] != '\0'; i++) {
        char current_char = expression[i];
        if (isdigit(current_char))
            numbers[num_count++] = current_char - '0';
        else if (isoperator(current_char)) {
            operators[operator_count++] = current_char;
        }
    }

    // From here on, I will be taking an example of 3+4*5*6+7 to make this simple
    first_num = numbers[0];  // set to 3, putting this in for loop would make me do extra work
    second_num = numbers[1]; // set to 4
    operator = operators[0]; // set to +

    // does 3 + 4 and gets 7, so result becomes 7.
    do_thing(&result, first_num, second_num, operator);

    // for loop to continously solve the expression
    for (int i = 2; i < num_count; i++) {
        int next_num = numbers[i];   // 5 then 6 then 7
        operator = operators[i - 1]; // * then * then +

        do_thing(&result, result, next_num, operator);
    }

    return result;
}
