/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:54:18 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 19:54:19 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	rot_cost(int pos, int half, int size)
{
	if (pos <= half)
		return (pos);
	return (pos - size);
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
		n->cost_b = rot_cost(n->pos, half_b, b->size);
		n->cost_a = rot_cost(n->target_pos, half_a, a->size);
		n = n->next;
	}
}

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
