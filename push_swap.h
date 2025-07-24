#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"

// list struct
typedef	struct s_stack
{
	int value;
	int index;
	int position;
	int rot_cost;
	int Pa;
	int Pb;
	int Na;
	int Nb;
	int rot_outcome;
	int below_median;
	int cheapest;
	struct s_stack *target;
	struct s_stack *next;
}	t_stack;

// prepare args
long	*argprep(int argc, char **argv);
char	*joinargs(int argc, char **argv);

// prep args helpers
void	handle_error(long *longarr);
int	issign(char c);
long	ps_atol(const char *nptr);
int	wordcount(char *str);
int	countdigits(char *str);

// list helpers
t_stack	*ps_lstnew(int value);
void	ps_lstadd_back(t_stack **lst, t_stack *new);
int	ps_lstsize(t_stack *lst);

// moves
void	swap_a(t_stack	**a);
void	swap_b(t_stack	**b);
void	swap_ab(t_stack **a, t_stack **b);
void	push_a(t_stack **a, t_stack **b);
void	push_b(t_stack **a, t_stack **b);
void	rotate_a(t_stack **a);
void	rotate_b(t_stack **b);
void	rotate_ab(t_stack **a, t_stack **b);
void	reverse_rotate_a(t_stack **a);
void	reverse_rotate_b(t_stack **b);
void	reverse_rotate_ab(t_stack **a, t_stack **b);

// sorting functions
int	issorted(t_stack **a);
void	sort_four(t_stack **a, t_stack **b);
void	sort(t_stack **a, t_stack **b);
t_stack	*findmin(t_stack **s, t_stack *prevmin);
t_stack *findmax(t_stack **s, t_stack *anode);
void settargets(t_stack ** a, t_stack **b);

#endif