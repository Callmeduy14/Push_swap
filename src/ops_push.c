#include "push_swap.h"

static void	push(t_stack *to, t_stack *from)
{
	t_node	*n;

	n = stack_pop_top(from);
	if (!n)
		return ;
	stack_push_top(to, n);
}

void	op_pa(t_stack *a, t_stack *b)
{
	push(a, b);
	ps_puts("pa\n");
}

void	op_pb(t_stack *a, t_stack *b)
{
	push(b, a);
	ps_puts("pb\n");
}