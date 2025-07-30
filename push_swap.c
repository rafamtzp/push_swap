/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:06:42 by ramarti2          #+#    #+#             */
/*   Updated: 2025/07/30 15:11:30 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_stack **a, t_stack **b, int argc, char **argv)
{
	int	i;

	if (argc == 1)
		return ;
	i = 1;
	while (i < argc && argv[i][0] != '\0')
		i++;
	if (i < argc && argv[i][0] == '\0')
	{
		write(STDERR_FILENO, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
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
