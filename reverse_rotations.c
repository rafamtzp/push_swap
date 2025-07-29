/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:58:05 by ramarti2          #+#    #+#             */
/*   Updated: 2025/07/29 14:53:42 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate_a(t_stack **a)
{
	t_stack	*ptra;
	t_stack	*ptrb;

	if (*a == NULL || ps_lstsize(*a) == 1)
		return ;
	ptra = *a;
	while (ptra->next != NULL)
		ptra = ptra->next;
	ptra->next = *a;
	*a = ptra;
	ptrb = ptra->next;
	while (ptrb->next != ptra)
		ptrb = ptrb->next;
	ptrb->next = NULL;
	ft_printf("rra\n");
}

void	reverse_rotate_b(t_stack **b)
{
	t_stack	*ptrb;
	t_stack	*ptrc;

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
	ft_printf("rrb\n");
}

static void	ab_reverse_rotate_a(t_stack **a)
{
	t_stack	*ptra;
	t_stack	*ptrb;

	if (*a == NULL || ps_lstsize(*a) == 1)
		return ;
	ptra = *a;
	while (ptra->next != NULL)
		ptra = ptra->next;
	ptra->next = *a;
	*a = ptra;
	ptrb = ptra->next;
	while (ptrb->next != ptra)
		ptrb = ptrb->next;
	ptrb->next = NULL;
}

static void	ab_reverse_rotate_b(t_stack **b)
{
	t_stack	*ptrb;
	t_stack	*ptrc;

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
}

void	reverse_rotate_ab(t_stack **a, t_stack **b)
{
	if (*b == NULL || ps_lstsize(*b) == 1 || *a == NULL || ps_lstsize(*a) == 1)
		return ;
	ab_reverse_rotate_a(a);
	ab_reverse_rotate_b(b);
	ft_printf("rrr\n");
}
