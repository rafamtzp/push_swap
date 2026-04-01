/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:56:20 by ramarti2          #+#    #+#             */
/*   Updated: 2026/04/01 13:27:28 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_stack
{
	int				value;
	int				index;
	int				position;
	int				rot_cost;
	int				ra;
	int				rb;
	int				rra;
	int				rrb;
	int				rot_outcome;
	int				below_median;
	int				cheapest;
	struct s_stack	*target;
	struct s_stack	*next;
}					t_stack;

// ---------------------- Preparing and stacking up user input ----------------------
// Argument preparation (prep_args.c)
long				*argprep(int argc, char **argv); // cuts up arguments, checks their validity, and converts them into an array of longs
char				*joinargs(int argc, char **argv); // if user provides list as several arguments, this bunches them together

// Argument preparation helpers (prep_helpers.c)
void				handle_error(long *longarr, char *str, char **arr,
						int wordcount);
long				ps_atol(const char *nptr);
int					wordcount(char *str);
int					countdigits(char *str);
int					issign(char c);

// Takes in array of longs and stacks them up into stack A, setting up the indices (stack_args.c)
void				stackargs(t_stack **a, long *longarr, int argc,
						char **argv);

// Push swap linked list helpers (list_helpers.c)
t_stack				*ps_lstnew(int value);
int					ps_lstsize(t_stack *lst);
void				ps_lstadd_back(t_stack **lst, t_stack *new);
void				ps_lstclear(t_stack **lst);

// ------------------ Stack Movements -----------------------------------
// Swaps and pushes
void				swap_a(t_stack **a);
void				swap_b(t_stack **b);
void				swap_ab(t_stack **a, t_stack **b);
void				push_a(t_stack **a, t_stack **b);
void				push_b(t_stack **a, t_stack **b);
// Rotations
void				rotate_a(t_stack **a);
void				rotate_b(t_stack **b);
void				rotate_ab(t_stack **a, t_stack **b);
// Reverse rotations
void				reverse_rotate_a(t_stack **a);
void				reverse_rotate_b(t_stack **b);
void				reverse_rotate_ab(t_stack **a, t_stack **b);

// ---------------- Sorting the stacks ---------------------------
void				sort(t_stack **a, t_stack **b);

// Sort helpers 1
t_stack				*findmin(t_stack **s, t_stack *prevmin);
t_stack				*findmax(t_stack **s, t_stack *anode);
int					lesseq(int a, int b);
int					greq(int a, int b);
int					issorted(t_stack **a);

// Sort helpers 2
void				setpositions(t_stack **s);
void				setbelowmedian(t_stack **a);
void				settargets(t_stack **a, t_stack **b);
void				settargets_b(t_stack **a, t_stack **b);
t_stack				*cheapestnode(t_stack **a);

// Sort helpers 3
void				setrotvalues(t_stack **a, t_stack **b);
void				set_costs_and_outcomes(t_stack **a);

// Sort helpers 4
void				executerotations1(t_stack **a, t_stack **b,
						t_stack *cheapest);
void				executerotations2(t_stack **a, t_stack **b,
						t_stack *cheapest); // these are used to execute rotations after costs are calculated
void				push_all_a(t_stack **a, t_stack **b); // after sorting everything, this carefully pushes everything back to a

#endif
