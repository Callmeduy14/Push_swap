/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:54:21 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 19:54:22 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	total_cost(t_node *n)
{
	int	a;
	int	b;

	a = n->cost_a;
	if (a < 0)
		a = -a;
	b = n->cost_b;
	if (b < 0)
		b = -b;
	return (a + b);
}

static void	pick_best(t_stack *b, int *ca, int *cb)
{
	t_node	*n;
	int		best;

	best = INT_MAX;
	*ca = 0;
	*cb = 0;
	n = b->top;
	while (n)
	{
		if (total_cost(n) < best)
		{
			best = total_cost(n);
			*ca = n->cost_a;
			*cb = n->cost_b;
		}
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
	int	ca;
	int	cb;

	pick_best(b, &ca, &cb);
	exec_rotate_both(a, b, &ca, &cb);
	exec_single_rotates(a, b, ca, cb);
	op_pa(a, b);
}
