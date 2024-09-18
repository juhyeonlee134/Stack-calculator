#include "../includes/tokenizer.h"
#include "../includes/postfix.h"
#include "../includes/calculator.h"

#define INPUT_SIZE 1024

int main(void)
{
	int integer = 0;
	double result = 0;
	t_token* list = NULL;
	char input[INPUT_SIZE];

	gets_s(input, INPUT_SIZE);
	list = tokenize(input);
	to_postfix(&list);
	result = calculate(&list);
	integer = (int)result;
	if (result - integer == 0)
	{
		printf("%d\n", integer);
	}
	else
	{
		printf("%lf\n", result);
	}
	clear(&list);
	return 0;
}