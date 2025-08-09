/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_mark.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:54:04 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 19:54:05 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	alloc_lis_arrays(int n, int **nxt, int **len, int **prev)
{
	*nxt = (int *)malloc(sizeof(int) * n);
	*len = (int *)malloc(sizeof(int) * n);
	*prev = (int *)malloc(sizeof(int) * n);
	if (!*nxt || !*len || !*prev)
		return (0);
	return (1);
}

static void	init_lis_arrays(t_stack *a, int *nxt, int *len, int *prev)
{
	t_node	*n;
	int		i;

	n = a->top;
	i = 0;
	while (n)
	{
		nxt[i] = n->idx;
		len[i] = 1;
		prev[i] = -1;
		n = n->next;
		i++;
	}
}

static void	compute_lis_dp(int n, int *nxt, int *len, int *prev)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < i)
		{
			if (nxt[j] < nxt[i] && len[j] + 1 > len[i])
			{
				len[i] = len[j] + 1;
				prev[i] = j;
			}
			j++;
		}
		i++;
	}
}

static int	find_best_i(int n, int *len)
{
	int	i;
	int	best;

	best = 0;
	i = 1;
	while (i < n)
	{
		if (len[i] > len[best])
			best = i;
		i++;
	}
	return (best);
}

void	mark_lis_keep(t_stack *a)
{
	int		*nxt;
	int		*len;
	int		*prev;
	int		i;

	if (!alloc_lis_arrays(a->size, &nxt, &len, &prev))
		die_error();
	init_lis_arrays(a, nxt, len, prev);
	compute_lis_dp(a->size, nxt, len, prev);
	i = find_best_i(a->size, len);
	lis_clear_marks(a);
	lis_mark_backtrack(a, prev, i);
	free(nxt);
	free(len);
	free(prev);
}
