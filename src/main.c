#include "push_swap.h"

static void	end_ok(t_stack *a, t_stack *b)
{
	stack_clear(a);
	stack_clear(b);
}

int	main(int ac, char **av)
{
	t_stack	a;
	t_stack	b;

	stack_init(&a, 'a');
	stack_init(&b, 'b');
	if (ac == 1)
		return (0);
	if (!parse_args(ac, av, &a))
		die_error();
	if (is_sorted(&a))
		return (end_ok(&a, &b), 0);
	if (a.size <= 3)
	{
		sort_three(&a);
		return (end_ok(&a, &b), 0);
	}
	if (a.size <= 5)
	{
		sort_five(&a, &b);
		return (end_ok(&a, &b), 0);
	}
	index_compress(&a);
	mark_lis_keep(&a);
	solve(&a, &b);
	end_ok(&a, &b);
	return (0);
}
