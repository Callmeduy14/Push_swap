/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:35:58 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/11 09:17:23 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_line(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	if (i > 0)
		write(1, s, i);
	write(1, "\n", 1);
}

int	ch_read_line(char *buf, int max)
{
	int		i;
	char	c;
	int		r;

	i = 0;
	while (i < max - 1)
	{
		r = (int)read(0, &c, 1);
		if (r <= 0)
			break ;
		if (c == '\n')
			break ;
		buf[i++] = c;
	}
	buf[i] = '\0';
	return (i);
}

int	main(int ac, char **av)
{
	t_stack	a;
	t_stack	b;
	char	op[8];

	stack_init(&a, 'a');
	stack_init(&b, 'b');
	if (ac == 1)
		return (0);
	if (!parse_args(ac, av, &a))
	{
		stack_clear(&a);
		stack_clear(&b);
		die_error();
	}
	while (ch_read_line(op, (int) sizeof(op)) > 0)
		ch_apply_op(op, &a, &b);
	if (is_sorted(&a) && b.size == 0)
		put_line("OK");
	else
		put_line("KO");
	stack_clear(&a);
	stack_clear(&b);
	return (0);
}
