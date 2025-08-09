/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:53:49 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 20:12:03 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	stack_init(t_stack *s, char name)
{
	s->top = NULL;
	s->bot = NULL;
	s->size = 0;
	s->name = name;
}

void	stack_push_top(t_stack *s, t_node *n)
{
	t_node	*next;

	next = s->top;
	n->prev = NULL;
	n->next = next;
	if (next)
		next->prev = n;
	else
		s->bot = n;
	s->top = n;
	s->size++;
}

void	stack_push_bot(t_stack *s, t_node *n)
{
	t_node	*prev;

	prev = s->bot;
	n->next = NULL;
	n->prev = prev;
	if (prev)
		prev->next = n;
	else
		s->top = n;
	s->bot = n;
	s->size++;
}

t_node	*stack_pop_top(t_stack *s)
{
	t_node	*n;

	n = s->top;
	if (!n)
		return (NULL);
	s->top = n->next;
	if (s->top)
		s->top->prev = NULL;
	else
		s->bot = NULL;
	s->size--;
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

int	stack_min_idx_pos(t_stack *a)
{
	int		min;
	int		pos;
	int		k;
	t_node	*n;

	if (!a || !a->top)
		return (0);
	min = a->top->idx;
	pos = 0;
	k = 0;
	n = a->top;
	while (n)
	{
		if (n->idx < min)
		{
			min = n->idx;
			pos = k;
		}
		n = n->next;
		k++;
	}
	return (pos);
}
