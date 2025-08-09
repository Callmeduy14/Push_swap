/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:20:47 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 19:20:48 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	is_op(const char *op, const char *key)
{
	return (ft_strncmp(op, key, 4) == 0);
}

static int	apply_single(const char *op, t_stack *a, t_stack *b)
{
	if (is_op(op, "sa"))
		ch_swap(a);
	else if (is_op(op, "sb"))
		ch_swap(b);
	else if (is_op(op, "pa"))
		ch_push(a, b);
	else if (is_op(op, "pb"))
		ch_push(b, a);
	else if (is_op(op, "ra"))
		ch_rot(a);
	else if (is_op(op, "rb"))
		ch_rot(b);
	else if (is_op(op, "rra"))
		ch_rrot(a);
	else if (is_op(op, "rrb"))
		ch_rrot(b);
	else
		return (0);
	return (1);
}

void	ch_apply_op(const char *op, t_stack *a, t_stack *b)
{
	if (apply_single(op, a, b))
		return ;
	if (is_op(op, "ss"))
	{
		ch_swap(a);
		ch_swap(b);
	}
	else if (is_op(op, "rr"))
	{
		ch_rot(a);
		ch_rot(b);
	}
	else if (is_op(op, "rrr"))
	{
		ch_rrot(a);
		ch_rrot(b);
	}
	else
		die_error();
}
