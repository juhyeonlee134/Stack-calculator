#ifndef POSTFIX_H
#define POSTFIX_H

#include "token.h"

int is_all_number(const char* const str);

void exchange(t_token** const list, t_token** const stack);
void move_to_list(t_token** const list, t_token** const stack);
void move_to_stack(t_token** const list, t_token** const stack);
void to_postfix(t_token** const head);

#endif