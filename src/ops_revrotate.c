/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_revrotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:51:10 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 18:51:11 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	rev_rotate(t_stack *s)
{
	t_node	*n;

	if (s->size < 2)
		return ;
	n = s->bot;
	if (n->prev)
		n->prev->next = NULL;
	s->bot = n->prev;
	if (!s->bot)
		s->top = NULL;
	s->size--;
	n->prev = NULL;
	n->next = NULL;
	stack_push_top(s, n);
}

void	op_rra(t_stack *a)
{
	rev_rotate(a);
	ps_puts("rra\n");
}

void	op_rrb(t_stack *b)
{
	rev_rotate(b);
	ps_puts("rrb\n");
}

void	op_rrr(t_stack *a, t_stack *b)
{
	rev_rotate(a);
	rev_rotate(b);
	ps_puts("rrr\n");
}
