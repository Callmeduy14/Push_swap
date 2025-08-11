/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:20:51 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/11 09:38:15 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	swap_top_two(t_stack *s)
{
	t_node	*a;
	t_node	*b;

	if (s->size < 2)
		return ;
	a = s->top;
	b = a->next;
	a->next = b->next;
	if (b->next)
		b->next->prev = a;
	else
		s->bot = a;
	b->prev = NULL;
	b->next = a;
	a->prev = b;
	s->top = b;
}

void	ch_swap(t_stack *s)
{
	swap_top_two(s);
}
