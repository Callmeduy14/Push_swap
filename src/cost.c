#include "push_swap.h"

void	update_positions(t_stack *a, t_stack *b)
{
	int		k;
	t_node	*n;

	k = 0;
	n = a->top;
	while (n)
	{
		n->pos = k++;
		n = n->next;
	}
	k = 0;
	n = b->top;
	while (n)
	{
		n->pos = k++;
		n = n->next;
	}
}

int	find_target_pos(t_stack *a, int idx)
{
	int		pos;
	int		best_idx;
	t_node	*n;

	pos = 0;
	best_idx = INT_MAX;
	n = a->top;
	while (n)
	{
		if (n->idx > idx && n->idx < best_idx)
		{
			best_idx = n->idx;
			pos = n->pos;
		}
		n = n->next;
	}
	if (best_idx != INT_MAX)
		return (pos);
	/* if no greater, place after current max -> just after position of min */
	return (stack_min_idx_pos(a));
}

void	calc_costs(t_stack *a, t_stack *b)
{
	t_node	*n;
	int		half_a;
	int		half_b;

	half_a = a->size / 2;
	half_b = b->size / 2;
	n = b->top;
	while (n)
	{
		n->target_pos = find_target_pos(a, n->idx);
		if (n->pos <= half_b)
			n->cost_b = n->pos;
		else
			n->cost_b = (n->pos - b->size);
		if (n->target_pos <= half_a)
			n->cost_a = n->target_pos;
		else
			n->cost_a = (n->target_pos - a->size);
		n = n->next;
	}
}

static void	exec_rotate_both(t_stack *a, t_stack *b, int *ca, int *cb)
{
	while (*ca > 0 && *cb > 0)
	{
		op_rr(a, b);
		(*ca)--;
		(*cb)--;
	}
	while (*ca < 0 && *cb < 0)
	{
		op_rrr(a, b);
		(*ca)++;
		(*cb)++;
	}
}

static void	exec_single_rotates(t_stack *a, t_stack *b, int ca, int cb)
{
	while (ca > 0)
	{
		op_ra(a);
		ca--;
	}
	while (ca < 0)
	{
		op_rra(a);
		ca++;
	}
	while (cb > 0)
	{
		op_rb(b);
		cb--;
	}
	while (cb < 0)
	{
		op_rrb(b);
		cb++;
	}
}

void	exec_cheapest(t_stack *a, t_stack *b)
{
	t_node	*n;
	int		best;
	int		ca;
	int		cb;
	int		tmp;

	n = b->top;
	best = INT_MAX;
	ca = 0;
	cb = 0;
	while (n)
	{
		tmp = n->cost_a;
		if (tmp < 0)
			tmp = -tmp;
		if (n->cost_b < 0)
			tmp += -n->cost_b;
		else
			tmp += n->cost_b;
		if (tmp < best)
		{
			best = tmp;
			ca = n->cost_a;
			cb = n->cost_b;
		}
		n = n->next;
	}
	exec_rotate_both(a, b, &ca, &cb);
	exec_single_rotates(a, b, ca, cb);
	op_pa(a, b);
}
