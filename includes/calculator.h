#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "token.h"

char* to_str(const double num);

double to_number(const char* const str);
double calculate(const t_token** const head);

t_token* operate(const char* const s1, const char* const s2, const char op);

#endif