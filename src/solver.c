#include "push_swap.h"

static void	push_non_lis_to_b(t_stack *a, t_stack *b)
{
	int		keep;
	int		pushed;
	t_node	*n;

	keep = 0;
	n = a->top;
	while (n)
	{
		if (n->lis_keep)
			keep++;
		n = n->next;
	}
	pushed = 0;
	while (a->size > keep && pushed < a->size)
	{
		if (!a->top->lis_keep)
		{
			op_pb(a, b);
			pushed++;
		}
		else
		op_ra(a);
	}
}

static void	final_rotate_min_top(t_stack *a)
{
	int		pos;
	int		k;

	pos = stack_min_idx_pos(a);
	k = a->size / 2;
	if (pos <= k)
		while (pos-- > 0)
			op_ra(a);
	else
		while (pos++ < a->size)
			op_rra(a);
}

void	solve(t_stack *a, t_stack *b)
{
	push_non_lis_to_b(a, b);
	while (b->size)
	{
		update_positions(a, b);
		calc_costs(a, b);
		exec_cheapest(a, b);
	}
	final_rotate_min_top(a);
}
