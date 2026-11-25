#include "functions.h"
#include <stdio.h>

int main(void) {
    int choice = 0;
    long long int first_numerator, first_denominator;
    long long int second_numerator, second_denominator;
    Fraction result;

    while (1) {
        print_menu();
        choice = get_int("Please enter your choice: ");

        // These two if blocks are here, since the switch case has two fractions common, while these don't
        if (choice == SEE_LOWEST) {
            long long int numerator = get_int("Please enter the numerator of the fraction: ");
            long long int denominator = get_int("Please enter the denominator of the fraction: ");

            Fraction fraction = {numerator, denominator};
            result = lowest_form(fraction);

            printf("The result is: \n");
            print_fraction(result);
        }

        if (choice == EXIT)
            break;

        // First fraction and second fraction are common across all four choices, so decided to have them here
        first_numerator = get_int("Please enter the numerator of the first fraction: ");
        first_denominator = get_int("Please enter the denominator of the first fraction: ");

        // Informs user about a 0 denominator, since that leads to funky stuff
        if (first_denominator == 0) {
            printf("Bruv, you can't have zero as the denominator\n");
            continue;
        }

        second_numerator = get_int("Please enter the numerator of the second fraction: ");
        second_denominator = get_int("Please enter the denominator of the second fraction: ");

        if (second_denominator == 0) {
            printf("Bruv, you can't have zero as the denominator\n");
            continue;
        }

        // Initialises the two fractions
        Fraction first_fraction = {first_numerator, first_denominator};
        Fraction second_fraction = {second_numerator, second_denominator};

        switch (choice) {
            case ADD:
                result = add_fraction(first_fraction, second_fraction); // Adds the fractions and stores them in result
                printf("The result is: \n");
                print_fraction(result); // Prints the result
                printf("\nOR\n");
                print_fraction(lowest_form(result)); // Prints the result in lowest form

                break;
            case SUBTRACT:
                result = subtract_fraction(first_fraction, second_fraction);
                printf("The result is: \n");
                print_fraction(result);
                printf("\nOR\n");
                print_fraction(lowest_form(result));

                break;
            case MULTIPLY:
                result = multiply_fraction(first_fraction, second_fraction);
                printf("The result is: \n");
                print_fraction(result);
                printf("\nOR\n");
                print_fraction(lowest_form(result));

                break;
            case DIVIDE:
                // Informs user about 0 numerator(In division numerator becomes denominator, so once again funky stuff)
                if (second_fraction.numerator == 0) {
                    printf("Setting zero as numerator and dividing, is NOT COOL!\n");
                    continue;
                }
                result = divide_fraction(first_fraction, second_fraction);
                printf("The result is: \n");
                print_fraction(result);
                printf("\nOR\n");
                print_fraction(lowest_form(result));

                break;
            default:
                printf("Unknown choice!\n");
        }
    }
    return 0;
}