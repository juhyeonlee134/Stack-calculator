#include "../includes/calculator.h"
#include "../includes/postfix.h"
#include <math.h>

double calculate(const t_token** const head)
{
	double ret = 0;
	t_token* stack = NULL;
	t_token* curr = (*head)->next;

	stack = init();
	if (!stack)
	{
		clear(head);
		exit(1);
	}
	while (curr != *head)
	{
		if (is_all_number(curr->token))
		{
			move_to_stack(&curr, &stack);
		}
		else
		{
			t_token* node2 = pop(&stack);
			t_token* node1 = pop(&stack);
			t_token* node = operate(node1->token, node2->token, curr->token[0]);
			push(&stack, node);
			curr = curr->next;
		}
	}
	if (stack->prev->prev != stack)
	{
		fprintf(stderr, "Syntax error\n");
		clear(head);
		clear(&stack);
		exit(1);
	}
	ret = to_number(stack->prev->token);
	clear(&stack);
	return ret;
}

t_token* operate(const char* const s1, const char* const s2, const char op)
{
	double n1 = to_number(s1);
	double n2 = to_number(s2);
	double ret = 0;
	t_token* token = NULL;

	switch (op)
	{
	case '+':
		ret = n1 + n2;
		break;
	case '-':
		ret = n1 - n2;
		break;
	case '*':
		ret = n1 * n2;
		break;
	case '/':
		if (n2 == 0)
		{
			fprintf(stderr, "Operation not permitted: division by zero\n");
			return NULL;
		}
		ret = n1 / n2;
		break;
	}
	token = (t_token*)malloc(sizeof(t_token));
	if (!token)
	{
		fprintf(stderr, "Fatal error\n");
		return NULL;
	}
	token->token = to_str(ret);
	if (!token->token)
	{
		free(token);
		return NULL;
	}
	return token;
}

char* to_str(const double num)
{
	char* ret = NULL;

	ret = (char*)malloc(sizeof(char) * 21);
	if (!ret)
	{
		fprintf(stderr, "Fatal error\n");
		return NULL;
	}
	sprintf_s(ret, 21, "%lf", num);
	return ret;
}

double to_number(const char* const str)
{
	int sign = 0;
	double ret = 0;
	size_t index = 0;
	long long real = 0;
	long long integer = 0;

	if (str[0] == '-')
	{
		sign = 1;
		index++;
	}
	integer = atoll(str + index);
	while (str[index])
	{
		if (str[index] == '.' || str[index] == ',')
		{
			break;
		}
		index++;
	}
	if (index == strlen(str))
	{
		ret = (double)integer;
	}
	else
	{
		index++;
		real = atoll(str + index);
		ret = (double)real / pow(10, (double)strlen(str + index));
		ret += integer;
	}
	ret *= (sign ? -1 : 1);
	return ret;
}