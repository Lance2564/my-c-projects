#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

void do_thing(double *result, int first_num, int second_num, char operator);
bool isoperator(char operator);
double eval(const char *expression);

#endif