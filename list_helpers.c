/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:00:23 by ramarti2          #+#    #+#             */
/*   Updated: 2025/08/28 18:19:19 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*ps_lstnew(int value)
{
	t_stack	*n;

	n = malloc(sizeof(t_stack));
	if (n == 0)
		return (0);
	n->value = value;
	n->next = 0;
	return (n);
}

void	ps_lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*ptr;

	if (lst == 0 || new == 0)
		return ;
	ptr = *lst;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	while (ptr->next != 0)
		ptr = ptr->next;
	ptr->next = new;
}

int	ps_lstsize(t_stack *lst)
{
	int	size;

	if (lst == 0)
		return (0);
	size = 1;
	while (lst->next != 0)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

void	ps_lstclear(t_stack **lst)
{
	t_stack	*ptr1;
	t_stack	*ptr2;

	if (lst == 0 || *lst == 0)
		return ;
	ptr1 = *lst;
	while (ptr1->next != 0)
	{
		ptr2 = ptr1->next;
		free(ptr1);
		ptr1 = ptr2;
	}
	free(ptr1);
	*lst = 0;
	lst = 0;
}
