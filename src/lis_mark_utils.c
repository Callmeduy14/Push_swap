/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_mark_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:54:07 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 19:54:08 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static t_node	*node_at(t_stack *a, int pos)
{
	t_node	*n;
	int		i;

	n = a->top;
	i = 0;
	while (n && i < pos)
	{
		n = n->next;
		i++;
	}
	return (n);
}

void	lis_clear_marks(t_stack *a)
{
	t_node	*n;

	n = a->top;
	while (n)
	{
		n->lis_keep = 0;
		n = n->next;
	}
}

void	lis_mark_backtrack(t_stack *a, int *prev, int i)
{
	t_node	*n;

	while (i != -1)
	{
		n = node_at(a, i);
		if (n)
			n->lis_keep = 1;
		i = prev[i];
	}
}
