#include "../includes/postfix.h"

int is_all_number(const char* const str)
{
	if (str[1] == '\0' && !isdigit(str[0]))
	{
		return 0;
	}
	return 1;
}

void exchange(t_token** const list, t_token** const stack)
{
	t_token* to_list = pop(stack);
	t_token* to_stack = cut(list);

	push(list, to_list);
	push(stack, to_stack);
}

void move_to_list(t_token** const list, t_token** const stack)
{
	t_token* node = pop(stack);

	push(list, node);
}

void move_to_stack(t_token** const list, t_token** const stack)
{
	t_token* node = cut(list);

	push(stack, node);
}

void to_postfix(t_token** const head)
{
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
			curr = curr->next;
		}
		else if (curr->token[0] == '+' || curr->token[0] == '-')
		{
			if (stack->prev == stack)
			{
				move_to_stack(&curr, &stack);
			}
			else
			{
				exchange(&curr, &stack);
			}
		}
		else if (curr->token[0] == '*' || curr->token[0] == '/')
		{
			move_to_stack(&curr, &stack);
		}
		else if (curr->token[0] == '(')
		{
			move_to_stack(&curr, &stack);
		}
		else if (curr->token[0] == ')')
		{
			if (stack->prev == stack)
			{
				fprintf(stderr, "Syntax error\n");
				clear(head);
				clear(&stack);
				exit(1);
			}
			cut(&curr);
			while (1)
			{
				if (stack->prev == stack)
				{
					break;
				}
				else if (stack->prev->token[0] == '(')
				{
					break;
				}
				move_to_list(&curr, &stack);
			}
			pop(&stack);
		}
	}
	while (stack->prev != stack)
	{
		move_to_list(&curr, &stack);
	}
	free(stack);
}