#include "push_swap.h"

int	issorted(t_stack **a) // works!
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
void	sort_two(t_stack **a)
{
	if (issorted(a) == 1 || ps_lstsize(*a) < 2) 
		return ;
	swap_a(a);
}

t_stack	*findmin(t_stack **s, t_stack *prevmin) // this function now looks for min that isn't previous min
{
	t_stack	*candidate;
	t_stack	*ptr;

	ptr = *s;
	candidate = NULL;
	while (ptr != NULL)
	{
		if ((prevmin == NULL || ptr->value > prevmin->value) && (candidate == NULL || ptr->value < candidate->value))
			candidate = ptr;
		ptr = ptr->next;
	}
	if (candidate == NULL)
		return (*s);
	return (candidate);
}

t_stack *findmax(t_stack **s, t_stack *anode)
{
	t_stack *candidate;
	t_stack *ptr;

	ptr = *s;
	candidate = NULL;
	while (ptr != NULL)
	{
		if ((anode == NULL || ptr->value < anode->value) && (candidate == NULL || ptr->value > candidate->value))
			candidate = ptr;
		ptr = ptr->next;
	}
	if (candidate == NULL)
		return (findmax(s, NULL));
	return (candidate);
}


void setpositions(t_stack **s)
{
	t_stack *ptr;
	unsigned int i;

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

void setbelowmedian(t_stack **a)
{
	t_stack	*ptr;
	float median;

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

void settargets(t_stack ** a, t_stack **b)
{
	t_stack *ptr;

	ptr = *a;
	if (*a == NULL || *b == NULL)
		return ;
	while (ptr != NULL)
	{
		ptr->target = findmax(b, ptr);
		ptr = ptr->next;
	}
}

void settargets_b(t_stack **a, t_stack **b)
{
	t_stack *ptr;

	ptr = *b;
	if (*a == NULL || *b == NULL)
		return ;
	while (ptr != NULL)
	{
		ptr->target = findmin(a, ptr);
		ptr = ptr->next;
	}
}
void	sort_three(t_stack **a)
{
	t_stack *min;

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

void	sort_four(t_stack **a, t_stack **b)  // not sure if optimized....
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

void	setrotvalues(t_stack **a, t_stack **b)
{
	t_stack *ptr;

	ptr = *a;
	while (ptr != NULL)
	{
		setpositions(a);
		setpositions(b);
		ptr->Pa = ptr->position;
		ptr->Pb = ptr->target->position;
		ptr->Na = ps_lstsize(*a) - ptr->position;
		ptr->Nb = ps_lstsize(*b) - ptr->target->position;
		ptr = ptr->next;
	}
}

int	findrotoutcome(int pp, int nn, int pn, int np)
{
	int arr[4];
	int min;
	int i;
	int outcome;

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
int	greq(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

void	set_costs_and_outcomes(t_stack **a)
{
	t_stack *ptr;

	ptr = *a;
	while (ptr != NULL)
	{
		ptr->rot_outcome = findrotoutcome(greq(ptr->Pa, ptr->Pb), greq(ptr->Na, ptr->Nb), ptr->Pa + ptr->Nb, ptr->Na + ptr->Pb);
		if (ptr->rot_outcome == 0)
			ptr->rot_cost = greq(ptr->Pa, ptr->Pb);
		else if (ptr->rot_outcome == 1)
			ptr->rot_cost = greq(ptr->Na, ptr->Nb);
		else if (ptr->rot_outcome == 2)
			ptr->rot_cost = ptr->Pa + ptr->Nb;
		else if (ptr->rot_outcome == 3)
			ptr->rot_cost = ptr->Na + ptr->Pb;
		ptr = ptr->next;
	}
}

t_stack *cheapestnode(t_stack **a)
{
	t_stack *ptr;
	t_stack *cheapest;

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

int lesseq(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

void	rotate(t_stack **a, t_stack **b, int num, int dir)
{
	int i;

	i = 0;
	while (a != NULL && b != NULL && i++ < num && dir == 1)
		rotate_ab(a, b);
	i = 0;
	while (a != NULL && b != NULL && i++ < num && dir == -1)
		reverse_rotate_ab(a, b);
	i = 0;
	while (a == NULL && b != NULL && i++ < num && dir == 1)
		rotate_b(b);
	i = 0;
	while (a == NULL && b != NULL && i++ < num && dir == -1)
		reverse_rotate_b(b);
	i = 0;
	while (a != NULL && b == NULL && i++ < num && dir == 1)
		rotate_a(a);
	i = 0;
	while (a != NULL && b == NULL && i++ < num && dir == -1)
		reverse_rotate_a(a);
}

void	executerotations1(t_stack **a, t_stack **b, t_stack *cheapest)
{
	if (cheapest->rot_outcome == 0)
	{
		rotate(a, b, lesseq(cheapest->Pa, cheapest->Pb), 1);
		if (cheapest->Pa >= cheapest->Pb)
			rotate(a, NULL, cheapest->Pa - cheapest->Pb, 1);
		else
			rotate(NULL, b, cheapest->Pb - cheapest->Pa, 1);
	}
	else if (cheapest->rot_outcome == 1)
	{
		rotate(a, b, lesseq(cheapest->Na, cheapest->Nb), -1);
		if (cheapest->Na >= cheapest->Nb)
			rotate(a, NULL, cheapest->Na - cheapest->Nb, -1);
		else
			rotate(NULL, b, cheapest->Nb - cheapest->Na, -1);
	}
}

void	executerotations2(t_stack **a, t_stack **b, t_stack *cheapest)
{
	if (cheapest->rot_outcome == 2)
	{
		rotate(a, NULL, cheapest->Pa, 1);
		rotate(NULL, b, cheapest->Nb, -1);
	}
	else if (cheapest->rot_outcome == 3)
	{
		rotate(a, NULL, cheapest->Na, -1);
		rotate(NULL, b, cheapest->Pb, 1);
	}
}
void donothing(void)
{
	return ;
}
void	push_all_a(t_stack **a, t_stack **b)
{
	t_stack	*min;
	while (*b != NULL)
	{
		setbelowmedian(a);
		settargets_b(a, b);
		while (*a != (*b)->target)
		{
			settargets_b(a, b);
			if ((*b)->target->below_median == 1)
				reverse_rotate_a(a);
			else
				rotate_a(a);
		}
		push_a(a, b);
	}
	donothing();
	setbelowmedian(a);
	min = findmin(a, NULL);
	while (min->below_median == 0 && *a != min) // or issorted == 0 instead?
		rotate_a(a);
	while (min->below_median == 1 && *a != min)
		reverse_rotate_a(a);
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

void	sort_several(t_stack **a, t_stack **b)
{
	push_b(a, b); // push first two entries
	push_b(a, b);

	while (ps_lstsize(*a) > 3)
	{
		settargets(a, b);
		setrotvalues(a, b);
		set_costs_and_outcomes(a);
		if (cheapestnode(a)->rot_outcome == 0 || cheapestnode(a)->rot_outcome == 1)
			executerotations1(a, b, cheapestnode(a));
		else if (cheapestnode(a)->rot_outcome == 2 || cheapestnode(a)->rot_outcome == 3)
			executerotations2(a, b, cheapestnode(a));
		push_b(a, b);
	}
	sort_three(a);
	push_all_a(a, b);
	// ft_printf("After:\n");
	// ft_printf("a:\n");
	// t_stack *ptra = *a;
	// for (int i = 0; i < ps_lstsize(*a); i++)
	// {
	// 	ft_printf("Index: %i\n", ptra->index);
	// 	ptra = ptra->next;
	// }
	// t_stack *ptrb = *b;
	// ft_printf("b:\n");
	// for (int j = 0; j < ps_lstsize(*b); j++)
	// {
	// 	ft_printf("%i\n", ptrb->index);
	// 	ptrb = ptrb->next;
	// }
	ps_lstclear(a);  // TODO: Memory leaks.
					// free memory malloc'd in ft_split, strjoin (for argprep), error cases, etc. 
	ps_lstclear(b);
	exit(EXIT_SUCCESS);
}

void	sort(t_stack **a, t_stack **b)
{
	// is sorted case (includes case size = 1)
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