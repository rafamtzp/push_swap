#include "push_swap.h"

void	rotate_a(t_stack **a) // WORKS :D
{
	t_stack	*ptra;

	if (*a == NULL || ps_lstsize(*a) == 1)
		return ;
	ptra = *a;
	while (ptra->next != NULL)
		ptra = ptra->next;
	ptra->next = *a;
	*a = (*a)->next;
	ptra = ptra->next;
	ptra->next = NULL;
	ft_printf("ra\n");
}

void	rotate_b(t_stack **b) // WORKS :D
{
	t_stack *ptrb;

	if (*b == NULL || ps_lstsize(*b) == 1)
		return ;
	ptrb = *b;
	while (ptrb->next != NULL)
		ptrb = ptrb->next;
	ptrb->next = *b;
	*b = (*b)->next;
	ptrb = ptrb->next;
	ptrb->next = NULL;
	ft_printf("rb\n");
}

void	rotate_ab(t_stack **a, t_stack **b) // works :D
{
	if (*b == NULL || ps_lstsize(*b) == 1 || *a == NULL || ps_lstsize(*a) == 1)
		return ;
	rotate_a(a);
	rotate_b(b);
	ft_printf("rr\n");
}