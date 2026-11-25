#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {
    long long int numerator;
    long long int denominator;
} Fraction;

typedef enum { ADD = 1, SUBTRACT = 2, MULTIPLY = 3, DIVIDE = 4, SEE_LOWEST = 5, EXIT = 6 } Choice;

long long int hcf(long long int first_num, long long int second_num);
long long int lcm(long long int first_num, long long int second_num);
void print_fraction(Fraction fraction);
Fraction lowest_form(Fraction fraction);
void print_menu(void);
long long int get_int(const char *prompt);
Fraction add_fraction(Fraction first_fraction, Fraction second_fraction);
Fraction subtract_fraction(Fraction first_fraction, Fraction second_fraction);
Fraction multiply_fraction(Fraction first_fraction, Fraction second_fraction);
Fraction divide_fraction(Fraction first_fraction, Fraction second_fraction);
void standardise_fraction(Fraction *fraction);

#endif