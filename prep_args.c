#include "push_swap.h"

char	*joinargs(int argc, char **argv)
{
	int i;
	char *str;
	char *tmp;
	char *tmp2;

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

static int validchars(char *str)
{
	int signcount;
	int i;
	// check if there are non-numeric chars that are also not a + or - and for double signs
	// also check that after numbers start, there are no signs after that!!!!!!
	i = 0;
	signcount = 0;
	while (str[i] && issign(str[i]) != 0) // first count the signs
	{
		if (issign(str[i]) != 0)
			signcount++;
		i++;
	}
	if (signcount > 1) // if more than one sign
		return (0);
	while (ft_isdigit(str[i]) == 1) // check only for digits after that
		i++;
	if (ft_isdigit(str[i]) == 0 && str[i]) // if non-digit found
		return (0);
	return (1);
}

static long	*buildchecker(char **arr, long *longarr, char *str)
{
	int i;

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

static int dupefound(long	*longarr, int wordcount)
{
	int i;
	int j;

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
	long *longarr;
	char	**arr;
	char *str;
	int i;

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
