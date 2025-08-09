/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:52:41 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 18:52:42 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	max_of_three(t_stack *a)
{
	int		m;
	t_node	*n;

	n = a->top;
	m = n->val;
	n = n->next;
	if (n && n->val > m)
		m = n->val;
	n = n->next;
	if (n && n->val > m)
		m = n->val;
	return (m);
}

void	sort_three(t_stack *a)
{
	int	m;

	if (is_sorted(a))
		return ;
	m = max_of_three(a);
	if (a->top->val == m)
		op_ra(a);
	else if (a->top->next->val == m)
		op_rra(a);
	if (a->top->val > a->top->next->val)
		op_sa(a);
}

void	sort_five(t_stack *a, t_stack *b)
{
	int	minpos;

	while (a->size > 3)
	{
		index_compress(a);
		minpos = stack_min_idx_pos(a);
		if (minpos <= a->size / 2)
			while (minpos-- > 0)
				op_ra(a);
		else
			while (minpos++ < a->size)
				op_rra(a);
		op_pb(a, b);
	}
	sort_three(a);
	while (b->size)
		op_pa(a, b);
}
