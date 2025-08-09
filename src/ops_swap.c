/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:51:28 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 18:51:29 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	print_op(const char *s)
{
	ps_puts(s);
	ps_puts("\n");
}

static void	do_swap(t_stack *s)
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

void	op_sa(t_stack *a)
{
	do_swap(a);
	print_op("sa");
}

void	op_sb(t_stack *b)
{
	do_swap(b);
	print_op("sb");
}

void	op_ss(t_stack *a, t_stack *b)
{
	do_swap(a);
	do_swap(b);
	print_op("ss");
}
