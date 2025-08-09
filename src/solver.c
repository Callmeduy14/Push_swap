/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:52:26 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 20:08:17 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	push_non_lis_to_b(t_stack *a, t_stack *b)
{
	t_node	*n;
	int		keep;
	int		total;

	keep = 0;
	n = a->top;
	while (n)
	{
		if (n->lis_keep)
			keep++;
		n = n->next;
	}
	total = a->size;
	while (total--)
	{
		if (a->top->lis_keep)
			op_ra(a);
		else
			op_pb(a, b);
	}
}

static void	final_rotate_min_top(t_stack *a)
{
	int	pos;
	int	half;

	index_compress(a);
	pos = stack_min_idx_pos(a);
	half = a->size / 2;
	if (pos <= half)
	{
		while (pos-- > 0)
			op_ra(a);
	}
	else
	{
		while (pos++ < a->size)
			op_rra(a);
	}
}

void	solve(t_stack *a, t_stack *b)
{
	int	guard;

	push_non_lis_to_b(a, b);
	while (b->size)
	{
		update_positions(a, b);
		calc_costs(a, b);
		exec_cheapest(a, b);
	}
	final_rotate_min_top(a);
	guard = 0;
	while (!is_sorted(a) && guard < a->size)
	{
		op_ra(a);
		guard++;
	}
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
