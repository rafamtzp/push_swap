/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:20:08 by ramarti2          #+#    #+#             */
/*   Updated: 2025/07/29 16:43:27 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_stack **a, t_stack **b, int num, int dir)
{
	int	i;

	i = 0;
	while (a != NULL && b != NULL && i++ < num && dir == 1)
		rotate_ab(a, b);
	i = 0;
	while (a != NULL && b != NULL && i++ < num && dir == -1)
		reverse_rotate_ab(a, b);
	i = 0;
	while (a == NULL && b != NULL && i++ < num && dir == 1)
		rotate_b(b);
	i = 0;
	while (a == NULL && b != NULL && i++ < num && dir == -1)
		reverse_rotate_b(b);
	i = 0;
	while (a != NULL && b == NULL && i++ < num && dir == 1)
		rotate_a(a);
	i = 0;
	while (a != NULL && b == NULL && i++ < num && dir == -1)
		reverse_rotate_a(a);
}

void	executerotations1(t_stack **a, t_stack **b, t_stack *cheapest)
{
	if (cheapest->rot_outcome == 0)
	{
		rotate(a, b, lesseq(cheapest->ra, cheapest->rb), 1);
		if (cheapest->ra >= cheapest->rb)
			rotate(a, NULL, cheapest->ra - cheapest->rb, 1);
		else
			rotate(NULL, b, cheapest->rb - cheapest->ra, 1);
	}
	else if (cheapest->rot_outcome == 1)
	{
		rotate(a, b, lesseq(cheapest->rra, cheapest->rrb), -1);
		if (cheapest->rra >= cheapest->rrb)
			rotate(a, NULL, cheapest->rra - cheapest->rrb, -1);
		else
			rotate(NULL, b, cheapest->rrb - cheapest->rra, -1);
	}
}

void	executerotations2(t_stack **a, t_stack **b, t_stack *cheapest)
{
	if (cheapest->rot_outcome == 2)
	{
		rotate(a, NULL, cheapest->ra, 1);
		rotate(NULL, b, cheapest->rrb, -1);
	}
	else if (cheapest->rot_outcome == 3)
	{
		rotate(a, NULL, cheapest->rra, -1);
		rotate(NULL, b, cheapest->rb, 1);
	}
}

void	push_all_a(t_stack **a, t_stack **b)
{
	t_stack	*min;

	while (*b != NULL)
	{
		setbelowmedian(a);
		settargets_b(a, b);
		while (*a != (*b)->target)
		{
			settargets_b(a, b);
			if ((*b)->target->below_median == 1)
				reverse_rotate_a(a);
			else
				rotate_a(a);
		}
		push_a(a, b);
	}
	setbelowmedian(a);
	min = findmin(a, NULL);
	while (min->below_median == 0 && *a != min)
		rotate_a(a);
	while (min->below_median == 1 && *a != min)
		reverse_rotate_a(a);
}
