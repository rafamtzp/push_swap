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
	setpositions(a);
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

int resultsmin(int results[])
{
	int min;
	int i;
	int outcome;

	i = 0;
	outcome = 0;
	min = results[0];
	while (i < 4)
	{
		if (results[i] < min)
		{
			min = results[i];
			outcome = i;
		}
		i++;
	}
	return (outcome);
}

int setrotoutcome(int Pa, int Pb, int Na, int Nb)
{
	int results[4];

	if (Pa > Pb)
		results[0] = Pa;
	else
		results[0] = Pb;
	if (Na > Nb)
		results[1] = Na;
	else
		results[1] = Nb;
	results[2] = Pa + Nb;
	results[3] = Na + Pb;
	return (resultsmin(results));
}

int greq(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

void setrotcost(t_stack *ptr)
{
	if (ptr->rot_outcome == 0)
		ptr->rot_cost = greq(ptr->Pa, ptr->Pb);
	else if (ptr->rot_outcome == 1)
		ptr->rot_cost = greq(ptr->Na, ptr->Nb);
	else if (ptr->rot_outcome == 2)
		ptr->rot_cost = ptr->Pa + ptr->Nb;
	else if (ptr->rot_outcome == 3)
		ptr->rot_cost = ptr->Na + ptr->Pb;
}

void setcosts(t_stack **a, t_stack **b)
{
	t_stack *ptr;
	
	ptr = *a;
	while (ptr != NULL)
	{
		setpositions(a);
		setpositions(b);  // I think I forgot to set positions for both!
		ptr->Pa = ptr->position;
		ptr->Na = ps_lstsize(*a) - ptr->position;
		ptr->Pb = ptr->target->position;
		ptr->Nb = ps_lstsize(*b) - ptr->target->position;
		ptr->rot_outcome = setrotoutcome(ptr->Pa, ptr->Pb, ptr->Na, ptr->Nb);
		setrotcost(ptr);
		ptr = ptr->next;
	}
}

t_stack	*findmincost(t_stack **s)
{
	t_stack	*ptr;
	t_stack *min;
	
	ptr = *s;
	min = *s;
	while (ptr != NULL)
	{
		if (ptr->rot_cost < min->rot_cost)
			min = ptr;
		ptr = ptr->next;
	}
	return (min);
}

void rotate(t_stack **a, t_stack **b, int times, int dir)
{
	int i;
	
	i = 0;
	while (a != NULL && b != NULL && i++ < times && dir == 1)
		rotate_ab(a, b);
	while (a != NULL && b != NULL && i++ < times && dir == -1)
		reverse_rotate_ab(a, b);
	while (a != NULL && b == NULL && i++ < times && dir == 1)
		rotate_a(a);
	while (a != NULL && b == NULL && i++ < times && dir == -1)
		reverse_rotate_a(a);
	while (a == NULL && b != NULL && i++ < times && dir == 1)
		rotate_b(b);
	while (a == NULL && b != NULL && i++ < times && dir == -1)
		reverse_rotate_b(b);
}

int lesseq(int a, int b)
{
	if (a <= b)
	return (a);
	return (b);
}

void do_rotateboth(t_stack **a, t_stack **b, t_stack *mincost)
{
	if (mincost->rot_outcome == 0)
	{
		rotate(a, b, lesseq(mincost->Pa, mincost->Pb), 1);
		if (mincost->Pa > mincost->Pb)
			rotate(a, NULL, mincost->Pa - mincost->Pb, 1);
		else if (mincost->Pb > mincost->Pa)
			rotate(NULL, b, mincost->Pb, 1);
	}
	else if (mincost->rot_outcome == 1)
	{
		rotate(a, b, lesseq(mincost->Na, mincost->Nb), -1);
		if (mincost->Na > mincost->Nb)
			rotate(a, NULL, mincost->Na - mincost->Nb, -1);
		else if (mincost->Nb > mincost->Na)
			rotate(NULL, b, mincost->Nb, -1);
	}
}
	
void do_rotate(t_stack **a, t_stack **b, t_stack *mincost)
{
	if (mincost->rot_outcome == 2)
	{
		rotate(a, NULL, mincost->Pa, 1);
		rotate(NULL, b, mincost->Nb, -1);
	}
	else if (mincost->rot_outcome == 3)
	{
		rotate(a, NULL, mincost->Na, -1);
		rotate(NULL, b, mincost->Pb, 1);
	}
}

void push_all_a(t_stack **a, t_stack **b)
{
	t_stack	*min;
	setbelowmedian(a);
	while (*b != NULL)
	{
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
	setbelowmedian(a);
	min = findmin(a, NULL);
	while (min->below_median == 0 && *a != min) // or issorted == 0 instead?
		rotate_a(a);
	while (min->below_median == 1 && *a != min)
		reverse_rotate_a(a);
}

void	sort_several(t_stack **a, t_stack **b)
{
	t_stack *mincost;
	
	push_b(a, b); // push first two entries
	push_b(a, b);
	while (ps_lstsize(*a) > 3)
	{
		settargets(a, b); // we set the targets
		setcosts(a, b); // this will calculate Pa Pb Na Nb for all nodes in a, the rotation outcome, and the total cost
		
		mincost = findmincost(a); // find the minimum cost
		if (mincost->rot_outcome == 0 || mincost->rot_outcome == 1) // !!!! Fix THIS!!!  I'm not pushing to b correctly!!!
			do_rotateboth(a, b, mincost); // executes rotations stored in node with minimal cost
		else if (mincost->rot_outcome == 2 || mincost->rot_outcome == 3)
			do_rotate(a, b, mincost);
		push_b(a, b); // pushes from a to b after rotations
	}
	sort_three(a);
	setpositions(b);
	push_all_a(a, b); // calls settargets_b(b, a) and finds and executes rotations before every push
	//test
	t_stack *ptra = *a;
	ft_printf("After:\n");
	ft_printf("size: %i\n", ps_lstsize(*a));
	ft_printf("a:\n");
	while (ptra != NULL)
	{
		ft_printf("Value: %i; Index: %i\n", ptra->value, ptra->index);
		ptra = ptra->next;
	}
	t_stack *ptrb = *b;
	ft_printf("b:\n");
	for (int j = 0; j < ps_lstsize(*b); j++)
	{
		ft_printf("Value: %i; Index: %i\n", ptrb->value, ptrb->index);
		ptrb = ptrb->next;
	}
	exit(EXIT_SUCCESS);
	return ;
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