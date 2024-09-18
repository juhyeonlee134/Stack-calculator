#include "../includes/token.h"

void clear(t_token** const head)
{
	t_token* curr = (*head)->next;
	t_token* next = curr->next;

	while (curr != *head)
	{
		free(curr->token);
		free(curr);
		curr = next;
		next = next->next;
	}
	free(*head);
}

void push(t_token** const head, t_token* const node)
{
	node->prev = (*head)->prev;
	node->next = *head;
	(*head)->prev->next = node;
	(*head)->prev = node;
}

t_token* init(void)
{
	t_token* head = (t_token*)malloc(sizeof(t_token));

	if (!head)
	{
		fprintf(stderr, "Fatal error\n");
		return NULL;
	}
	head->token = NULL;
	head->prev = head;
	head->next = head;
	return head;
}

t_token* pop(t_token** const head)
{
	t_token* node = (*head)->prev;

	node->prev->next = node->next;
	node->next->prev = node->prev;
	return node;
}

t_token* cut(t_token** const head)
{
	t_token* node = *head;

	*head = (*head)->next;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	return node;
}