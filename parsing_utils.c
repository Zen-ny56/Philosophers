#include "philosophers.h"

int	ft_isdigit(int a)
{
	if (a >= 48 && a <= 57)
		return (1);
	else
		return (0);
}

void	parse(char **av)
{
	int	i;

	i = 2;
	check_digit(av);
	if (atoi(av[1]) > 200 || atoi(av[1]) < 1)
	{
		write(2, "Number is not valid\n", 21);
		exit(1);
	}
	while (av[i] != NULL)
	{
		if (i == 5)
			break ;
		if (atoi(av[i]) < 60)
		{
			write(2, "Time is not enough\n", 20);
			exit(1);
		}
		i++;
	}
	if (av[i] != NULL && atoi(av[i]) < 1)
	{
		write(2, "Last argument ain't valid\n", 27);
		exit(1);
	}
}

void	check_digit(char **av)
{
	int	i;
	int	k;

	i = 2;
	while (av[i] != NULL)
	{
		k = 0;
		while (av[i][k] != '\0')
		{
			if (ft_isdigit(av[i][k]) == 0)
				exit(1);
			k++;
		}
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - '0';
		if (result * sign > 2147483647)
			exit(1);
		else if (result * sign < -2147483648)
			exit(1);
		i++;
	}
	return (result * sign);
}
