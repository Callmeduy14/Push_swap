#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

/* ================== data structures ================== */
typedef struct s_node
{
	int			val;
	int			idx; /* coordinate compressed index */
	int			lis_keep; /* 1 if part of chosen LIS */
	int			pos; /* current position from top (0-based) */
	int			target_pos; /* target position in A */
	int			cost_a; /* rotations needed on A */
	int			cost_b; /* rotations needed on B */
	struct s_node	*prev;
	struct s_node	*next;
}t_node;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bot;
	int		size;
	char	name; /* 'a' or 'b' */
}t_stack;

/* ============== parsing / errors ============== */
int			parse_args(int ac, char **av, t_stack *a);
int			is_sorted(t_stack *s);
void		die_error(void);

/* ============== stack utils =================== */
t_node		*node_new(int val);
void		stack_init(t_stack *s, char name);
void		stack_push_top(t_stack *s, t_node *n);
void		stack_push_bot(t_stack *s, t_node *n);
t_node		*stack_pop_top(t_stack *s);
void		stack_clear(t_stack *s);
int			stack_min_idx_pos(t_stack *a);

/* ============== operations (print + do) ======= */
void		op_sa(t_stack *a);
void		op_sb(t_stack *b);
void		op_ss(t_stack *a, t_stack *b);
void		op_pa(t_stack *a, t_stack *b);
void		op_pb(t_stack *a, t_stack *b);
void		op_ra(t_stack *a);
void		op_rb(t_stack *b);
void		op_rr(t_stack *a, t_stack *b);
void		op_rra(t_stack *a);
void		op_rrb(t_stack *b);
void		op_rrr(t_stack *a, t_stack *b);

/* ============== LIS + solver ================== */
void		index_compress(t_stack *a);
void		mark_lis_keep(t_stack *a);
void		solve(t_stack *a, t_stack *b);

/* ============== cost / target ================= */
void		update_positions(t_stack *a, t_stack *b);
int			find_target_pos(t_stack *a, int idx);
void		calc_costs(t_stack *a, t_stack *b);
void		exec_cheapest(t_stack *a, t_stack *b);

/* ============== tiny sorts ==================== */
void		sort_three(t_stack *a);
void		sort_five(t_stack *a, t_stack *b);

/* ============== utils ========================= */
long		ps_atol(const char *s, int *ok);
int			ps_isspace(char c);
int			ps_isdigit(char c);
int			ps_puts(const char *s);

#endif