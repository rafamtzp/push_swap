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