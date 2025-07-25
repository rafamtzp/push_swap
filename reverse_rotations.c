#include "push_swap.h"

void	reverse_rotate_a(t_stack **a) // WORKS :D
{
	t_stack *ptra;
	t_stack *ptrb;

	if (*a == NULL || ps_lstsize(*a) == 1)
		return ;
	// go to last node
	ptra = *a; 
	while (ptra->next != NULL)
		ptra = ptra->next;
	ptra->next = *a; // point last node to first
	*a = ptra; // make last node the first one
	ptrb = ptra->next;
	while (ptrb->next != ptra)
		ptrb = ptrb->next;
	ptrb->next = NULL;
	//ft_printf("rra\n");
}

void	reverse_rotate_b(t_stack **b) // WORKS :D
{
	t_stack *ptrb;
	t_stack *ptrc;

	if (*b == NULL || ps_lstsize(*b) == 1)
		return ;
	ptrb = *b;
	while (ptrb->next != NULL)
		ptrb = ptrb->next;
	ptrb->next = *b;
	*b = ptrb;
	ptrc = ptrb->next;
	while (ptrc->next != ptrb)
		ptrc = ptrc->next;
	ptrc->next = NULL;
	//ft_printf("rrb\n");
}

void	reverse_rotate_ab(t_stack **a, t_stack **b) // WORKS :D
{
	if (*b == NULL || ps_lstsize(*b) == 1 || *a == NULL || ps_lstsize(*a) == 1)
		return ;
	reverse_rotate_a(a);
	reverse_rotate_b(b);
	//ft_printf("rrr\n");
}