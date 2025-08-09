#include "push_swap.h"

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

void	index_compress(t_stack *a)
{
	int		*arr;
	int		*sorted;
	int		i;
	t_node	*n;

	arr = to_array(a);
	if (!arr)
		die_error();
	sorted = (int *)malloc(sizeof(int) * a->size);
	if (!sorted)
		die_error();
	i = 0;
	while (i < a->size)
	{
		sorted[i] = arr[i];
		i++;
	}
	/* simple qsort clone to stay norm-friendly */
	qsort(sorted, a->size, sizeof(int), cmp_int);
	n = a->top;
	while (n)
	{
		i = 0;
		while (i < a->size)
		{
			if (sorted[i] == n->val)
			{
				n->idx = i;
				break ;
			}
			i++;
		}
		n = n->next;
	}
	free(arr);
	free(sorted);
}

void	mark_lis_keep(t_stack *a)
{
	int		*nxt;
	int		*len;
	int		*prev;
	t_node	*n;
	int		i;
	int		j;
	int		best_i;

	nxt = (int *)malloc(sizeof(int) * a->size);
	len = (int *)malloc(sizeof(int) * a->size);
	prev = (int *)malloc(sizeof(int) * a->size);
	if (!nxt || !len || !prev)
		die_error();
	i = 0;
	n = a->top;
	while (n)
	{
		len[i] = 1;
		prev[i] = -1;
		nxt[i] = n->idx;
		n = n->next;
		i++;
	}
	i = 0;
	while (i < a->size)
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
	best_i = 0;
	i = 1;
	while (i < a->size)
	{
		if (len[i] > len[best_i])
			best_i = i;
		i++;
	}
	i = best_i;
	j = 0;
	n = a->top;
	while (n)
	{
		n->lis_keep = 0;
		n = n->next;
	}
	while (i != -1)
	{
		n = a->top;
		j = 0;
		while (n && j < i)
		{
			n = n->next;
			j++;
		}
		if (n)
			n->lis_keep = 1;
		i = prev[i];
	}
	free(nxt);
	free(len);
	free(prev);
}