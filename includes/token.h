#ifndef TOKEN_H
#define TOKEN_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_token
{
	char* token;
	struct s_token* prev;
	struct s_token* next;
}t_token;

void clear(t_token** const head);
void push(t_token** const head, t_token* const node);

t_token* init(void);
t_token* pop(t_token** const head);
t_token* cut(t_token** const head);
t_token* remove_front(t_token** const head);

#endif