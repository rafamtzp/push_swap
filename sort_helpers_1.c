/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:08:44 by ramarti2          #+#    #+#             */
/*   Updated: 2025/07/29 16:41:58 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	issorted(t_stack **a)
{
	t_stack	*ptr;

	ptr = *a;
	if (ps_lstsize(*a) <= 1)
		return (1);
	while (ptr->next->value > ptr->value && ptr->next->next != NULL)
		ptr = ptr->next;
	if (ptr->next->value <= ptr->value)
		return (0);
	return (1);
}

t_stack	*findmin(t_stack **s, t_stack *prevmin)
{
	t_stack	*candidate;
	t_stack	*ptr;

	ptr = *s;
	candidate = NULL;
	while (ptr != NULL)
	{
		if ((prevmin == NULL || ptr->value > prevmin->value)
			&& (candidate == NULL || ptr->value < candidate->value))
			candidate = ptr;
		ptr = ptr->next;
	}
	if (candidate == NULL)
		return (findmin(s, NULL));
	return (candidate);
}

t_stack	*findmax(t_stack **s, t_stack *anode)
{
	t_stack	*candidate;
	t_stack	*ptr;

	ptr = *s;
	candidate = NULL;
	while (ptr != NULL)
	{
		if ((anode == NULL || ptr->value < anode->value) && (candidate == NULL
				|| ptr->value > candidate->value))
			candidate = ptr;
		ptr = ptr->next;
	}
	if (candidate == NULL)
		return (findmax(s, NULL));
	return (candidate);
}

int	lesseq(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

int	greq(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}
