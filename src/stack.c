#include "push_swap.h"

static void	link_node_between(t_stack *s, t_node *n, t_node *prev, t_node *next)
{
	n->prev = prev;
	n->next = next;
	if (prev)
		prev->next = n;
	else
		s->top = n;
	if (next)
		next->prev = n;
	else
		s->bot = n;
	s->size++;
}

t_node	*node_new(int val)
{
	t_node	*n;

	n = (t_node *)malloc(sizeof(t_node));
	if (!n)
		return (NULL);
	n->val = val;
	n->idx = -1;
	n->lis_keep = 0;
	n->pos = 0;
	n->target_pos = 0;
	n->cost_a = 0;
	n->cost_b = 0;
	n->prev = NULL;
	n->next = NULL;
	return (n);
}

void	stack_init(t_stack *s, char name)
{
	s->top = NULL;
	s->bot = NULL;
	s->size = 0;
	s->name = name;
}

void	stack_push_top(t_stack *s, t_node *n)
{
	link_node_between(s, n, NULL, s->top);
}

void	stack_push_bot(t_stack *s, t_node *n)
{
	link_node_between(s, n, s->bot, NULL);
}

t_node	*stack_pop_top(t_stack *s)
{
	t_node	*n;

	n = s->top;
	if (!n)
		return (NULL);
	s->top = n->next;
	if (s->top)
		s->top->prev = NULL;
	else
		s->bot = NULL;
	s->size--;
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

void	stack_clear(t_stack *s)
{
	t_node	*n;
	t_node	*nx;

	n = s->top;
	while (n)
	{
		nx = n->next;
		free(n);
		n = nx;
	}
	s->top = NULL;
	s->bot = NULL;
	s->size = 0;
}

int	stack_min_idx_pos(t_stack *a)
{
	int		min;
	int		pos;
	int		k;
	t_node	*n;

	if (!a->top)
		return (0);
	min = a->top->idx;
	pos = 0;
	k = 0;
	n = a->top;
	while (n)
	{
		if (n->idx < min)
		{
			min = n->idx;
			pos = k;
		}
		n = n->next;
		k++;
	}
	return (pos);
}