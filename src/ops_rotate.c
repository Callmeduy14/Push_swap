#include "push_swap.h"

static void	rotate(t_stack *s)
{
	t_node	*n;

	if (s->size < 2)
		return ;
	n = stack_pop_top(s);
	stack_push_bot(s, n);
}

void	op_ra(t_stack *a)
{
	rotate(a);
	ps_puts("ra\n");
}

void	op_rb(t_stack *b)
{
	rotate(b);
	ps_puts("rb\n");
}

void	op_rr(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
	ps_puts("rr\n");
}