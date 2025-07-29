/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:14:22 by ramarti2          #+#    #+#             */
/*   Updated: 2025/07/29 14:49:41 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	setpositions(t_stack **s)
{
	t_stack			*ptr;
	unsigned int	i;

	ptr = *s;
	if (ptr == NULL)
		return ;
	i = 0;
	while (ptr != NULL)
	{
		ptr->position = i;
		i++;
		ptr = ptr->next;
	}
	return ;
}

void	setbelowmedian(t_stack **a)
{
	t_stack	*ptr;
	float	median;

	setpositions(a);
	ptr = *a;
	if (*a == NULL)
		return ;
	median = (ps_lstsize(*a) - 1) / 2.0;
	while (ptr != NULL)
	{
		if (ptr->position <= median)
			ptr->below_median = 0;
		else
			ptr->below_median = 1;
		ptr = ptr->next;
	}
	return ;
}

void	settargets(t_stack **a, t_stack **b)
{
	t_stack	*ptr;

	ptr = *a;
	if (*a == NULL || *b == NULL)
		return ;
	while (ptr != NULL)
	{
		ptr->target = findmax(b, ptr);
		ptr = ptr->next;
	}
}

void	settargets_b(t_stack **a, t_stack **b)
{
	t_stack	*ptr;

	ptr = *b;
	if (*a == NULL || *b == NULL)
		return ;
	while (ptr != NULL)
	{
		ptr->target = findmin(a, ptr);
		ptr = ptr->next;
	}
}

t_stack	*cheapestnode(t_stack **a)
{
	t_stack	*ptr;
	t_stack	*cheapest;

	ptr = *a;
	cheapest = *a;
	while (ptr != NULL)
	{
		if (ptr->rot_cost < cheapest->rot_cost)
			cheapest = ptr;
		ptr = ptr->next;
	}
	return (cheapest);
}
