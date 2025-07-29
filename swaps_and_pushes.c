/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swaps_and_pushes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:00:11 by ramarti2          #+#    #+#             */
/*   Updated: 2025/07/29 14:53:17 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_a(t_stack **a)
{
	t_stack	*ptr;

	if (ps_lstsize(*a) < 2)
		return ;
	ptr = *a;
	ptr = ptr->next;
	(*a)->next = ptr->next;
	ptr->next = *a;
	*a = ptr;
	ft_printf("sa\n");
}

void	swap_b(t_stack **b)
{
	t_stack	*ptr;

	if (ps_lstsize(*b) < 2)
		return ;
	ptr = *b;
	ptr = ptr->next;
	(*b)->next = ptr->next;
	ptr->next = *b;
	*b = ptr;
	ft_printf("sb\n");
}

void	swap_ab(t_stack **a, t_stack **b)
{
	if (ps_lstsize(*b) < 2 || ps_lstsize(*a) < 2)
		return ;
	swap_a(a);
	swap_b(b);
	ft_printf("ss\n");
}

void	push_a(t_stack **a, t_stack **b)
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

void	push_b(t_stack **a, t_stack **b)
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
