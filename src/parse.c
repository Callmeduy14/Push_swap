/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:51:47 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 18:51:48 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	has_dup_or_out_of_range(t_stack *a)
{
	t_node	*i;
	t_node	*j;

	i = a->top;
	while (i)
	{
		if (i->val > INT_MAX || i->val < INT_MIN)
			return (1);
		j = i->next;
		while (j)
		{
			if (j->val == i->val)
				return (1);
			j = j->next;
		}
		i = i->next;
	}
	return (0);
}

static int	push_value(t_stack *a, const char *s)
{
	int		ok;
	long	v;
	t_node	*n;

	v = ps_atol(s, &ok);
	if (!ok || v > INT_MAX || v < INT_MIN)
		return (0);
	n = node_new((int)v);
	if (!n)
		return (0);
	stack_push_bot(a, n);
	return (1);
}

static int	parse_tokenized(char *arg, t_stack *a)
{
	int		k;
	int		i;
	int		j;

	i = 0;
	while (arg[i])
	{
		while (arg[i] && ps_isspace(arg[i]))
			i++;
		j = i;
		while (arg[i] && !ps_isspace(arg[i]))
			i++;
		if (i > j)
		{
			k = arg[i];
			arg[i] = '\0';
			if (!push_value(a, &arg[j]))
				return (0);
			arg[i] = (char)k;
		}
	}
	return (1);
}

int	parse_args(int ac, char **av, t_stack *a)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!av[i][0] || av[i][0] == ' ')
			return (0);
		if (!parse_tokenized(av[i], a))
			return (0);
		i++;
	}
	if (has_dup_or_out_of_range(a))
		return (0);
	return (1);
}

int	is_sorted(t_stack *s)
{
	t_node	*n;

	n = s->top;
	while (n && n->next)
	{
		if (n->val > n->next->val)
			return (0);
		n = n->next;
	}
	return (1);
}
