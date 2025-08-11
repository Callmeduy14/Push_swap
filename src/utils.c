/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:53:31 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/11 09:31:34 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	ps_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

static long	atol_fail(int *ok)
{
	*ok = 0;
	return (0L);
}

static const char	*atol_chekmp(const char *s, long *sign)
{
	*sign = 1;
	while (*s && ps_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			*sign = -1;
		s++;
	}
	return (s);
}

long	ps_atol(const char *s, int *ok)
{
	long	sign;
	long	res;

	*ok = 1;
	res = 0;
	s = atol_chekmp(s, &sign);
	if (!ft_isdigit(*s))
		return (atol_fail(ok));
	while (ft_isdigit(*s))
	{
		res = res * 10 + (*s++ - '0');
		if ((sign == 1 && res > (long)INT_MAX)
			|| (sign == -1 && - res < (long)INT_MIN))
			return (atol_fail(ok));
	}
	while (*s && ps_isspace(*s))
		s++;
	if (*s)
		return (atol_fail(ok));
	return (res * sign);
}

int	ps_puts(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return ((int)write (1, s, len));
}
