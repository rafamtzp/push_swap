/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:46:00 by ramarti2          #+#    #+#             */
/*   Updated: 2025/07/30 15:12:11 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*joinargs(int argc, char **argv)
{
	int		i;
	char	*str;
	char	*tmp;
	char	*tmp2;

	i = 2;
	str = ft_strjoin(argv[1], " ");
	while (i < argc)
	{
		tmp = str;
		tmp2 = ft_strjoin(tmp, argv[i++]);
		str = ft_strjoin(tmp2, " ");
		free(tmp);
		free(tmp2);
	}
	return (str);
}

static int	validchars(char *str)
{
	int	i;
	int	digitfound;

	i = 0;
	if (issign(str[i]) != 0)
		i++;
	digitfound = 0;
	while (ft_isdigit(str[i]) == 1)
	{
		digitfound = 1;
		i++;
	}
	if ((ft_isdigit(str[i]) == 0 && str[i]) || digitfound == 0)
		return (0);
	return (1);
}

static long	*buildchecker(char **arr, long *longarr, char *str)
{
	int	i;

	i = 0;
	while (i < wordcount(str))
	{
		if (validchars(arr[i]) == 0)
			return (NULL);
		if (countdigits(arr[i]) > 10)
			return (NULL);
		longarr[i] = ps_atol(arr[i]);
		if (longarr[i] > 2147483647 || longarr[i] < -2147483648)
			return (NULL);
		i++;
	}
	return (longarr);
}

static int	dupefound(long *longarr, int wordcount)
{
	int	i;
	int	j;

	i = 0;
	while (i < wordcount)
	{
		j = i;
		while (j < wordcount)
		{
			if (longarr[i] == longarr[j] && i != j)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

long	*argprep(int argc, char **argv)
{
	long	*longarr;
	char	**arr;
	char	*str;
	int		i;

	if (argc == 1)
		return (NULL);
	str = joinargs(argc, argv);
	arr = ft_split(str, ' ');
	longarr = ft_calloc(sizeof(long), wordcount(str));
	if (!longarr || buildchecker(arr, longarr, str) == NULL
		|| dupefound(longarr, wordcount(str)) == 1)
	{
		handle_error(longarr, str, arr, wordcount(str));
		return (NULL);
	}
	i = wordcount(str);
	free(str);
	while (i >= 0)
		free(arr[i--]);
	free(arr);
	return (longarr);
}
