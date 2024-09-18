#include "../includes/tokenizer.h"

int is_number(const char* const str, const size_t index, const int flag)
{
	if (isdigit(str[index]))
	{
		return 1;
	}
	else if (str[index] == '.' || str[index] == ',')
	{
		if (index == 0)
		{
			return isdigit(str[index + 1]);
		}
		else
		{
			return isdigit(str[index - 1]) && isdigit(str[index + 1]);
		}
	}
	else if (str[index] == '+' || str[index] == '-')
	{
		if (flag == 0 && isdigit(str[index + 1]))
		{
			return 1;
		}
	}
	return 0;
}

int is_whitespace(const char ch)
{
	return (ch == ' ' || (ch >= 9 && ch <= 13));
}

int is_sign(const char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
	{
		return 1;
	}
	else if (ch == '(' || ch == ')')
	{
		return 1;
	}
	return 0;
}

char* slice(const char* const str)
{
	static size_t start = 0;
	static int prev_is_num = 0;
	size_t end = start;
	char* token = NULL;

	if (str[start] == '\0')
	{
		return (char*)(-1);
	}
	while (str[end])
	{
		if (is_number(str, end, prev_is_num))
		{
			end++;
			prev_is_num = 1;
		}
		else if (is_whitespace(str[end]))
		{
			if (end - start == 0)
			{
				end++;
				start++;
			}
			else
			{
				break;
			}
		}
		else if (is_sign(str[end]))
		{
			if (end - start == 0)
			{
				end++;
				prev_is_num = 0;
			}
			break;
		}
		else
		{
			fprintf(stderr, "Invalid elements [%zd]: %c\n", end, str[end]);
			return NULL;
		}
	}
	token = make_token(str + start, end - start);
	start = end;
	return token;
}

char* make_token(const char* const str, const size_t len)
{
	char* token = (char*)malloc(sizeof(char) * (len + 1));

	if (!token)
	{
		fprintf(stderr, "Fatal error\n");
		return NULL;
	}
	strncpy_s(token, len + 1, str, len);
	token[len] = '\0';
	return token;
}

t_token* tokenize(const char* const str)
{
	char* token = NULL;
	t_token* head = init();
	t_token* node = NULL;

	if (!head)
	{
		exit(1);
	}
	while (1)
	{
		token = slice(str);
		if (!token)
		{
			clear(&head);
			exit(1);
		}
		else if (token == (char*)(-1))
		{
			break;
		}
		node = (t_token*)malloc(sizeof(t_token));
		if (!node)
		{
			fprintf(stderr, "Fatal error\n");
			clear(&head);
			exit(1);
		}
		node->token = token;
		push(&head, node);
	}
	return head;
}