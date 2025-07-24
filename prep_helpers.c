#include "push_swap.h"

void	handle_error(long *longarr)
{
	if (longarr)
		free(longarr);
	write(2, "Error\n", 6); // TODO: write to stderr!!!
	longarr = NULL;
	exit(EXIT_FAILURE);
}

int issign(char c)
{
	if (c == '+')
		return (1);
	else if (c == '-')
		return (-1);
	return (0);
}

long	ps_atol(const char *nptr)
{
	long	num;
	int	sign;

	sign = issign(*nptr);
	if (sign != 0)
		nptr++;
	else
		sign = 1;
	while (*nptr == '0')
		nptr++;
	if (*nptr == '\0')
		return (0);
	num = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num += (*nptr - '0');
		nptr++;
		if (*nptr >= '0' && *nptr <= '9')
			num = num * 10;
	}
	return (sign * num);
}

int wordcount(char *str)
{
	int count;
	int counted;

	count = 0;
	counted = 0;
	while (*str)
	{
		if (*str != ' ' && counted == 0)
		{
			count++;
			counted = 1;
		}
		else if (*str == ' ' && counted == 1)
			counted = 0;
		str++;
	}
	return (count);
}

int countdigits(char *str)
{
	int count;

	count = 0;
	while (*str == '+' || *str == '-' || *str == '0')
		str++;
	if (*str >= '1' && *str <= '9')
	{
		count++;
		str++;
	}
	if (count == 0)
		return (1);
	while (*str >= '0' && *str <= '9' && count == 1)
	{
		count++;
		str++;
	}
	return (count);
}