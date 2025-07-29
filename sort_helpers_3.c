/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:17:30 by ramarti2          #+#    #+#             */
/*   Updated: 2025/07/29 14:49:46 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	setrotvalues(t_stack **a, t_stack **b)
{
	t_stack	*ptr;

	ptr = *a;
	while (ptr != NULL)
	{
		setpositions(a);
		setpositions(b);
		ptr->ra = ptr->position;
		ptr->rb = ptr->target->position;
		ptr->rra = ps_lstsize(*a) - ptr->position;
		ptr->rrb = ps_lstsize(*b) - ptr->target->position;
		ptr = ptr->next;
	}
}

static int	findrotoutcome(int pp, int nn, int pn, int np)
{
	int	arr[4];
	int	min;
	int	i;
	int	outcome;

	arr[0] = pp;
	arr[1] = nn;
	arr[2] = pn;
	arr[3] = np;
	min = arr[0];
	outcome = 0;
	i = 0;
	while (i < 4)
	{
		if (arr[i] < min)
		{
			min = arr[i];
			outcome = i;
		}
		i++;
	}
	return (outcome);
}

void	set_costs_and_outcomes(t_stack **a)
{
	t_stack	*ptr;

	ptr = *a;
	while (ptr != NULL)
	{
		ptr->rot_outcome = findrotoutcome(greq(ptr->ra, ptr->rb), greq(ptr->rra,
					ptr->rrb), ptr->ra + ptr->rrb, ptr->rra + ptr->rb);
		if (ptr->rot_outcome == 0)
			ptr->rot_cost = greq(ptr->ra, ptr->rb);
		else if (ptr->rot_outcome == 1)
			ptr->rot_cost = greq(ptr->rra, ptr->rrb);
		else if (ptr->rot_outcome == 2)
			ptr->rot_cost = ptr->ra + ptr->rrb;
		else if (ptr->rot_outcome == 3)
			ptr->rot_cost = ptr->rra + ptr->rb;
		ptr = ptr->next;
	}
}
