#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

void do_thing(double *result, double first_num, double second_num, char operator);
bool isoperator(char oper);
bool issign(char sign);
double eval(const char *expression);
bool valid_num(char character);
bool is_digit(char character);

#endif