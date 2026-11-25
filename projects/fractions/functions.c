#include "functions.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

long long int hcf(long long int first_num, long long int second_num) {
    long long int larger_num = (first_num > second_num) ? first_num : second_num;
    long long int smaller_num = (second_num < first_num) ? second_num : first_num;

    while (1) {
        if (smaller_num == 0)
            return larger_num;
        larger_num %= smaller_num;

        if (larger_num == 0)
            return smaller_num;
        smaller_num %= larger_num;
    }

    return larger_num;

    /* this function makes use of the euclidean algorithm which states that for two numbers a and b, a > b
       a (mod b) = c;
       c (mod b) = d;
       d(mod c) = e;
       .......

       untill you reach zero, say if we had reached zero at e, then the hcf would be d.*/
}

long long int lcm(long long int first_num, long long int second_num) {
    long long int lcm = (first_num * second_num) / (hcf(first_num, second_num));
    return lcm;

    /* a * b = lcm(a, b) * hcf(a, b), hence we can derive that
    lcm(a, b) = a * b / hcf(a, b) */
}

void print_fraction(Fraction fraction) {
    /* To print the fraction as a number when denominator is 1.
    example 3 / 1, now gets printed as 3. */

    if (fraction.denominator == 1) {
        printf("%lld\n", fraction.numerator);
    }
    else {
        printf("%lld\n", fraction.numerator);
        printf("-\n");
        printf("%lld\n", fraction.denominator);
    }

    /* To print fractions in the format
    2
    -
    3

    */
}

Fraction lowest_form(Fraction fraction) {
    int to_divide_by = hcf(fraction.numerator, fraction.denominator); // gets the hcf

    // Divides numerator and denominator by hcf to get the lowest form
    fraction.numerator /= to_divide_by;
    fraction.denominator /= to_divide_by;

    if (fraction.denominator < 0)
        standardise_fraction(&fraction);

    return fraction;
}

void print_menu(void) {
    printf("What would you like to do?\n");
    printf("1. Add two fractions\n");
    printf("2. Subtract two fractions\n");
    printf("3. Multiply two fractions\n");
    printf("4. Divide two fractions\n");
    printf("5. See lowest form of a fraction\n");
    printf("6. Exit\n");
}

long long int get_int(const char *prompt) {
    char number[10000];

    while (1) {
        printf("%s", prompt);
        fgets(number, sizeof(number), stdin);
        bool is_positive = isdigit(number[0]) || (number[0] == '+' && isdigit(number[1]));
        bool is_negative = (number[0] == '-' && isdigit(number[1]));

        if (is_positive || is_negative)
            return atoll(number);
        else {
            printf("Please enter a valid number!\n");
            continue;
        }
    }
}

Fraction add_fraction(Fraction first_fraction, Fraction second_fraction) {
    Fraction result = {0, 0};

    /* If both denominators are same, then just adds the numerators and keeps denominator same.
     2 / 3 + 4 / 3 = 6 / 3
     */

    if (first_fraction.denominator == second_fraction.denominator) {
        result.numerator = first_fraction.numerator + second_fraction.numerator;
        result.denominator = first_fraction.denominator;
        return result;
    }

    // Gets the common denominator(e.g for 2/3 and 4/6, the lcm or common denominator is 6)
    long long int common_denominator = lcm(first_fraction.denominator, second_fraction.denominator);

    long long int to_mul_numer_and_denom_of_first_fraction = common_denominator / first_fraction.denominator; // Figures out how much to multiply to make both fractions have common_denominator

    // Multiplies the fraction to keep it same but with the same denominator(2 / 3 = 2 * 2 / 3 * 2 = 4 / 6)
    first_fraction.numerator *= to_mul_numer_and_denom_of_first_fraction;
    first_fraction.denominator *= to_mul_numer_and_denom_of_first_fraction;

    // (4 / 6 remains same)
    long long int to_mul_numer_and_denom_of_second_fraction = common_denominator / second_fraction.denominator;
    second_fraction.numerator *= to_mul_numer_and_denom_of_second_fraction;
    second_fraction.denominator *= to_mul_numer_and_denom_of_second_fraction;

    // (4 + 4 / 6 = 8 / 6)
    result.numerator = first_fraction.numerator + second_fraction.numerator;
    result.denominator = common_denominator;
    return result;
}

Fraction subtract_fraction(Fraction first_fraction, Fraction second_fraction) {
    Fraction result = {0, 0};
    if (first_fraction.denominator == second_fraction.denominator) {
        result.numerator = first_fraction.numerator - second_fraction.numerator;
        result.denominator = first_fraction.denominator;
        return result;
    }
    long long int common_denominator = lcm(first_fraction.denominator, second_fraction.denominator);
    long long int to_mul_numer_and_denom_of_first_fraction = common_denominator / first_fraction.denominator;
    first_fraction.numerator *= to_mul_numer_and_denom_of_first_fraction;
    first_fraction.denominator *= to_mul_numer_and_denom_of_first_fraction;

    long long int to_mul_numer_and_denom_of_second_fraction = common_denominator / second_fraction.denominator;
    second_fraction.numerator *= to_mul_numer_and_denom_of_second_fraction;
    second_fraction.denominator *= to_mul_numer_and_denom_of_second_fraction;

    result.numerator = first_fraction.numerator - second_fraction.numerator;
    result.denominator = common_denominator;
    return result;
}

Fraction multiply_fraction(Fraction first_fraction, Fraction second_fraction) {
    Fraction result;

    if (first_fraction.numerator == 0 || second_fraction.numerator == 0) {
        result.numerator = 0;
        result.denominator = 1;

        return result;
    }

    first_fraction = lowest_form(first_fraction);
    second_fraction = lowest_form(second_fraction);

    result.numerator = first_fraction.numerator * second_fraction.numerator;
    result.denominator = first_fraction.denominator * second_fraction.denominator;

    return result;
}

Fraction divide_fraction(Fraction first_fraction, Fraction second_fraction) {
    first_fraction = lowest_form(first_fraction);
    second_fraction = lowest_form(second_fraction);

    Fraction result = {first_fraction.numerator * second_fraction.denominator, first_fraction.denominator * second_fraction.numerator};
    return result;
}

void standardise_fraction(Fraction *fraction) {
    fraction->numerator *= -1;
    fraction->denominator *= -1;
}