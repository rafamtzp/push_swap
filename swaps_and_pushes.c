#include "push_swap.h"

void	swap_a(t_stack	**a)  // WORKS :D
{
	t_stack	*ptr;

	if (ps_lstsize(*a) < 2)
		return ;
	ptr = *a; // points to first t_stack of list
	ptr = ptr->next; // goes to second t_stack
	(*a)->next = ptr->next;  // relink first to third
	ptr->next = *a; // relink second to first
	*a = ptr; // make second t_stack the first one.
	ft_printf("sa\n");
}

void	swap_b(t_stack	**b) // WORKS :D
{
		t_stack	*ptr;

	if (ps_lstsize(*b) < 2)
		return ;
	ptr = *b; // points to first t_stack of list
	ptr = ptr->next; // goes to second t_stack
	(*b)->next = ptr->next;  // relink first to third
	ptr->next = *b; // relink second to first
	*b = ptr; // make second t_stack the first one.
	ft_printf("sb\n");
}

void	swap_ab(t_stack **a, t_stack **b) // WORKS :D
{
	if (ps_lstsize(*b) < 2 || ps_lstsize(*a) < 2)
		return ;
	swap_a(a);
	swap_b(b);
	ft_printf("ss\n");
}

void	push_a(t_stack **a, t_stack **b) // WORKS :D
{
	t_stack	*ptra;
	
	if (*b == NULL)
		return ;
	ptra = *a;
	*a = *b;
	*b = (*b)->next;
	(*a)->next = ptra;
	ft_printf("pa\n");
}

void	push_b(t_stack **a, t_stack **b) // WORKS :D
{
	t_stack	*ptrb;

	if (*a == NULL)
		return ;
	ptrb = *b;
	*b = *a;
	*a = (*a)->next;
	(*b)->next = ptrb;
	ft_printf("pb\n");
}