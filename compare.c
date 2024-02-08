#include "philosophers.h"

int	ru_full(t_data *info)
{
	if (info->full_philos >= info->num_philo)
	{
		return (1);
	}
	return (0);
}
