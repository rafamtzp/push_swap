/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:56:05 by ramarti2          #+#    #+#             */
/*   Updated: 2025/07/29 15:09:55 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_empty_indices(t_stack **s)
{
	t_stack	*ptr;

	if (*s == NULL || s == NULL)
		return ;
	ptr = *s;
	while (ptr != NULL)
	{
		ptr->index = -1;
		ptr = ptr->next;
	}
	return ;
}

static int	indices_set(t_stack **s)
{
	t_stack	*ptr;

	ptr = *s;
	if (ptr == NULL)
		return (1);
	while (ptr != NULL)
	{
		if (ptr->index == -1)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

static void	setindices(t_stack **s)
{
	t_stack	*ptr;
	t_stack	*min;
	int		i;

	ptr = *s;
	if (ptr == NULL)
		return ;
	set_empty_indices(s);
	min = findmin(s, NULL);
	i = 0;
	while (indices_set(s) != 1)
	{
		if (ptr == min)
		{
			ptr->index = i++;
			min = findmin(s, min);
			ptr = *s;
		}
		else if (ptr == NULL)
			ptr = *s;
		else
			ptr = ptr->next;
	}
	return ;
}

static void	free_and_setindices(char *str, long *longarr, t_stack **a)
{
	free(str);
	free(longarr);
	setindices(a);
}

void	stackargs(t_stack **a, long *longarr, int argc, char **argv)
{
	int		size;
	int		i;
	t_stack	*t_stack;
	char	*str;

	if (!longarr)
	{
		handle_error(longarr, NULL, NULL, 0);
		return ;
	}
	str = joinargs(argc, argv);
	size = wordcount(str);
	i = 0;
	while (i < size)
	{
		t_stack = ps_lstnew((int)longarr[i++]);
		if (!t_stack)
		{
			ps_lstclear(a);
			handle_error(longarr, str, NULL, 0);
			return ;
		}
		ps_lstadd_back(a, t_stack);
	}
	free_and_setindices(str, longarr, a);
}
