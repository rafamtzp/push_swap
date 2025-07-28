#include "push_swap.h"

void set_empty_indices(t_stack **s)
{
	t_stack *ptr;

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

int indices_set(t_stack **s)
{
	t_stack *ptr;

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

void setindices(t_stack **s)
{
	t_stack *ptr;
	t_stack *min;
	int i;

	ptr = *s;
	if (ptr == NULL)  // from here, assumed indices have been set to -1 outside
		return ;
	set_empty_indices(s);
	min = findmin(s, NULL);
	i = 0;
	while (indices_set(s) != 1) // move ptr through list looking for mins until all indices are set
	{
		if (ptr == min) // if min found
		{
			ptr->index = i++; // set index to current index value to be given
			min = findmin(s, min); // find the next min
			ptr = *s; // set pointer back to beginning
		}
		else if (ptr == NULL)
			ptr = *s;
		else
			ptr = ptr->next; // if not found, go to next node
	}
	return ;
}

void	stackargs(t_stack** a, long *longarr, int argc, char **argv)
{
	int size;
	int i;
	t_stack	*t_stack;
	char	*str;

	if (!longarr)
	{
		handle_error(longarr);
		return ;
	}
	str = joinargs(argc, argv);
	size = wordcount(str);
	i = 0;
	while (i < size)
	{
		t_stack = ps_lstnew((int)longarr[i++]);
		ps_lstadd_back(a, t_stack);
	}
	setindices(a);
}
// IDEA: calculate moves JUST to see which one is cheapest, but INSTEAD
// do your rotations in a loop until one of the targets is at the top and THEN do the other one
// rather than doing each a pre-calculated, specific number of times.

void	push_swap(t_stack	**a, t_stack **b, int argc, char **argv)
{
	stackargs(a, argprep(argc, argv), argc, argv); // takes empty stack a and creates a list with arg values
	// test
	sort(a, b);
	
	// ptra = *a;
	// t_stack *ptrb = *b;
	// ft_printf("After:\n");
	// ft_printf("a:\n");
	// for (int i = 0; i < ps_lstsize(*a); i++)
	// {
	// 	ft_printf("value: %i\n", ptra->value);
	// 	ptra = ptra->next;
	// }
	// ft_printf("b:\n");
	// for (int j = 0; j < ps_lstsize(*b); j++)
	// {
	// 	ft_printf("%i\n", ptrb->value);
	// 	ptrb = ptrb->next;
	// }
}

int main(int argc, char **argv)
{
	t_stack	*na;
	t_stack	*nb;

	na = NULL;
	nb = NULL;
	push_swap(&na, &nb, argc, argv);
}