#include "push_swap.h"

int	ps_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ps_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

long	ps_atol(const char *s, int *ok)
{
	long	sign;
	long	res;

	*ok = 1;
	while (*s && ps_isspace(*s))
		s++;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!ps_isdigit(*s))
		return (*ok = 0, 0);
	res = 0;
	while (*s && ps_isdigit(*s))
	{
		res = res * 10 + (*s - '0');
		if ((sign == 1 && res > (long)INT_MAX) ||
			(sign == -1 && -res < (long)INT_MIN))
			return (*ok = 0, 0);
		s++;
	}
	while (*s)
	{
		if (!ps_isspace(*s))
			return (*ok = 0, 0);
		s++;
	}
	return (res * sign);
}

int	ps_puts(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return ((int)write(1, s, len));
}