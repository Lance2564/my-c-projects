#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void do_thing(double *result, double first_num, double second_num, char operator) {
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
            *result = (int)first_num % (int)second_num;
            break;
    }
}

bool isoperator(char oper) {
    /* Checks if a character is an operator, decided to use switch case rather than
    return operator == '+' || operator == '-' and so on, for readability reasons */

    switch (oper) {
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

bool issign(char sign) {
    // checks if a character is a sign. Shorter and more readable than a bazillion if (sign == '+' || sign == '-')
    return (sign == '+') || (sign == '-');
}

bool isdecimal(char character) {
    // returns true if a character is a period. Shorter than if (character == '.') and more readable.
    return (character == '.');
}

double eval(const char *expression) {
    char numbers[500][500] = {"\0"}; // An array of 500 numbers(capacity of 500 digits) to store your stupidly long math questions
    int operators[499] = {'\0'};     // An array of 500 - 1 operators to store all your operators

    // sets num count and operator count to 0, to avoid undefined behaviour
    int num_count, operator_count; // num count and operator count keep track on how many numbers and operators there are
    num_count = operator_count = 0;

    // sets first num and second num to 0, to avoid undefined behaviour
    double first_num, second_num;
    first_num = second_num = 0;

    double result = 0; // sets result to 0, to avoid undefined behaviour
    char operator;     // set to '\0', toooooooo........ avoid undefined behaviour

    int digits_in_current_number = 0;

    // for loop to put numbers in numbers array, and operators in operators array

    while (*expression != '\0') {
        char current_char = *expression; // current_char for better readability and speed

        // since we're allowing negative numbers, this helps check if it's 5 * -4 or 5 - 4.
        bool is_num_sign = (valid_num(current_char)) && (operator_count == num_count);

        // If it's the sign of a number, and the number is valid, i.e it's either a digit, a sign, or a decimal do the following while loop
        if (is_num_sign && valid_num(current_char)) {
            // the digits in the number being worked on, helps keep track
            digits_in_current_number = 0;

            /* this while loop, loops through expression[i] for as long as expression[i] is a valid number
            and stores it in an appropriate index, allowing support for multi-digit number */

            while (valid_num(*expression))
                numbers[num_count][digits_in_current_number++] = *expression++; // 1234

            num_count++;

            // restarts the loop once the number has been assigned
            continue;
        }

        // if it is an operator, store it in the operator array
        if (isoperator(current_char)) {
            operators[operator_count++] = current_char;
            expression++;
        }
        else
            expression++;
    }

    // From here on, I will be taking an example of 34 * 56 + 7 * 8 to make this simple
    first_num = strtod(numbers[0], NULL);  // set to 34
    second_num = strtod(numbers[1], NULL); // set to 56
    operator = operators[0];               // set to *

    // does 34 * 56 and gets 1904, and sets result to 1904
    do_thing(&result, first_num, second_num, operator);

    // for loop to continously solve the expression
    for (int i = 2; i < num_count; i++) {
        double next_num = strtod(numbers[i], NULL); // 7 then 8
        operator = operators[i - 1];                // + then *

        // calculates the value and stores it in result
        do_thing(&result, result, next_num, operator);
    }

    return result; // finally returns the ending value
}

bool valid_num(char character) {
    /*  checks if a character is a digit, a sign or a . this is to help in identifying
    whether a character can be a part of a number */

    return is_digit(character) || issign(character) || isdecimal(character);
}

bool is_digit(char character) {
    // own is_digit to be a teeny tiny bit faster(pretty sure it's impossible to notice though)
    int int_value_of_char = character - '0';

    return int_value_of_char <= 9 && int_value_of_char >= 0;
}