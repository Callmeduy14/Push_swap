/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:38:19 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/11 09:38:29 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	rotate_one(t_stack *s)
{
	t_node	*n;

	if (s->size < 2)
		return ;
	n = stack_pop_top(s);
	stack_push_bot(s, n);
}

static void	reverse_rotate_one(t_stack *s)
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

void	ch_rot(t_stack *s)
{
	rotate_one(s);
}

void	ch_rrot(t_stack *s)
{
	reverse_rotate_one(s);
}

void	ch_push(t_stack *to, t_stack *from)
{
	t_node	*n;

	n = stack_pop_top(from);
	if (!n)
		return ;
	stack_push_top(to, n);
}
