/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:54:11 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 19:54:12 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	*to_array(t_stack *a)
{
	int		*k;
	int		i;
	t_node	*n;

	k = (int *)malloc(sizeof(int) * a->size);
	if (!k)
		return (NULL);
	i = 0;
	n = a->top;
	while (n)
	{
		k[i++] = n->val;
		n = n->next;
	}
	return (k);
}

static int	cmp_int(const void *aa, const void *bb)
{
	int	a;
	int	b;

	a = *(const int *)aa;
	b = *(const int *)bb;
	if (a < b)
		return (-1);
	if (a > b)
		return (1);
	return (0);
}

static int	bsearch_idx(int *arr, int n, int key)
{
	int	l;
	int	r;
	int	m;

	l = 0;
	r = n - 1;
	while (l <= r)
	{
		m = (l + r) / 2;
		if (arr[m] == key)
			return (m);
		if (arr[m] < key)
			l = m + 1;
		else
			r = m - 1;
	}
	return (-1);
}

int	index_compress(t_stack *a)
{
	int		*arr;
	int		*sorted;
	int		i;
	t_node	*n;

	arr = to_array(a);
	if (!arr)
		return (0);
	sorted = (int *)malloc(sizeof(int) * a->size);
	if (!sorted)
		return (free(arr), 0);
	i = -1;
	while (++i < a->size)
		sorted[i] = arr[i];
	qsort(sorted, a->size, sizeof(int), cmp_int);
	n = a->top;
	while (n)
	{
		n->idx = bsearch_idx(sorted, a->size, n->val);
		n = n->next;
	}
	free(arr);
	free(sorted);
	return (1);
}
