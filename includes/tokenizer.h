#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "../includes/token.h"

int is_sign(const char ch);
int is_whitespace(const char ch);
int is_number(const char* const str, const size_t index, const int flag);

char* slice(const char* const str);
char* make_token(const char* const str, const size_t len);

t_token* tokenize(const char* const str);

#endif