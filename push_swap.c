/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:06:42 by ramarti2          #+#    #+#             */
/*   Updated: 2025/07/29 14:59:52 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_stack **a, t_stack **b, int argc, char **argv)
{
	stackargs(a, argprep(argc, argv), argc, argv);
	sort(a, b);
	ps_lstclear(a);
	ps_lstclear(b);
}

int	main(int argc, char **argv)
{
	t_stack	*na;
	t_stack	*nb;

	na = NULL;
	nb = NULL;
	push_swap(&na, &nb, argc, argv);
}
