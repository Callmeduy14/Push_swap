/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_target.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:54:27 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 19:54:31 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	next_pos(int pos, int size)
{
	if (pos + 1 == size)
		return (0);
	return (pos + 1);
}

static int	best_pred_pos(t_stack *a, int idx_b, int *found)
{
	t_node	*n;
	int		pred_idx;
	int		pred_pos;

	n = a->top;
	pred_idx = INT_MIN;
	pred_pos = 0;
	*found = 0;
	while (n)
	{
		if (n->idx < idx_b && n->idx > pred_idx)
		{
			pred_idx = n->idx;
			pred_pos = n->pos;
			*found = 1;
		}
		n = n->next;
	}
	return (next_pos(pred_pos, a->size));
}

static int	max_idx_next_pos(t_stack *a)
{
	t_node	*n;
	int		max_idx;
	int		max_pos;

	n = a->top;
	max_idx = INT_MIN;
	max_pos = 0;
	while (n)
	{
		if (n->idx > max_idx)
		{
			max_idx = n->idx;
			max_pos = n->pos;
		}
		n = n->next;
	}
	return (next_pos(max_pos, a->size));
}

int	find_target_pos(t_stack *a, int idx_b)
{
	int	pos;
	int	found;

	pos = best_pred_pos(a, idx_b, &found);
	if (found)
		return (pos);
	return (max_idx_next_pos(a));
}
