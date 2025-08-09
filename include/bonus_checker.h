/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_checker.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:36:13 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/09 20:04:17 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_CHECKER_H
# define BONUS_CHECKER_H

# include "../include/push_swap.h"

int		ch_read_line(char *buf, int max);

struct	s_stack;

int		ch_read_line(char *buf, int max);
void	ch_swap(struct s_stack *s);
void	ch_rot(struct s_stack *s);
void	ch_rrot(struct s_stack *s);
void	ch_push(struct s_stack *to, struct s_stack *from);
void	ch_apply_op(const char *op, struct s_stack *a, struct s_stack *b);

#endif
