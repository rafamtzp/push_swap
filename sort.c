/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:58:36 by ramarti2          #+#    #+#             */
/*   Updated: 2025/07/29 15:09:10 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_two(t_stack **a)
{
	if (issorted(a) == 1 || ps_lstsize(*a) < 2)
		return ;
	swap_a(a);
}

static void	sort_three(t_stack **a)
{
	t_stack	*min;

	if (ps_lstsize(*a) < 3 || issorted(a) == 1)
		return ;
	setbelowmedian(a);
	min = findmin(a, NULL);
	if (*a == min)
	{
		swap_a(a);
		rotate_a(a);
	}
	else if (min->below_median == 0 && (*a)->value > (*a)->next->next->value)
		rotate_a(a);
	else if (min->below_median == 0 && (*a)->value < (*a)->next->next->value)
		swap_a(a);
	else if (min->below_median == 1 && (*a)->value < (*a)->next->value)
		reverse_rotate_a(a);
	else if (min->below_median == 1 && (*a)->value > (*a)->next->value)
	{
		swap_a(a);
		reverse_rotate_a(a);
	}
	return ;
}

static void	sort_four(t_stack **a, t_stack **b)
{
	if (issorted(a) == 1)
		return ;
	push_b(a, b);
	sort_three(a);
	(*b)->target = findmin(a, *b);
	while (*a != (*b)->target)
		rotate_a(a);
	push_a(a, b);
	while (issorted(a) == 0)
		reverse_rotate_a(a);
}

static void	sort_several(t_stack **a, t_stack **b)
{
	push_b(a, b);
	push_b(a, b);
	while (ps_lstsize(*a) > 3)
	{
		settargets(a, b);
		setrotvalues(a, b);
		set_costs_and_outcomes(a);
		if (cheapestnode(a)->rot_outcome == 0
			|| cheapestnode(a)->rot_outcome == 1)
			executerotations1(a, b, cheapestnode(a));
		else if (cheapestnode(a)->rot_outcome == 2
			|| cheapestnode(a)->rot_outcome == 3)
			executerotations2(a, b, cheapestnode(a));
		push_b(a, b);
	}
	sort_three(a);
	push_all_a(a, b);
}

void	sort(t_stack **a, t_stack **b)
{
	if (issorted(a) == 1)
		return ;
	if (ps_lstsize(*a) == 2)
		sort_two(a);
	else if (ps_lstsize(*a) == 3)
		sort_three(a);
	else if (ps_lstsize(*a) == 4)
		sort_four(a, b);
	else if (ps_lstsize(*a) >= 5)
		sort_several(a, b);
	return ;
}
