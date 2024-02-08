#include "philosophers.h"

void	thread_process(t_data *info)
{
	int	i;

	i = 0;
	init_personal_data(info);
	info->start = get_time();
	while (i < info->num_philo)
	{
		info->philos[i].last_meal_time = info->start;
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		pthread_create(&info->philos[i].thread, NULL, &routine, &info->philos[i]);
		i++;
	}
	if (monitor_simulation(info) > 0)
	{
		pthread_mutex_lock(&info->write);
		printf("%zu %d philo has died\n", time - info->start, info->dead_id);
		pthread_mutex_unlock(&info->write);
	}
	// pthread_create(&ap->monitor, NULL, &monitor, ap);
	// if (ap->max_meals > 0)
	// 	pthread_create(&ap->waiter, NULL, &waiter, ap);
	// if (terminate(ap) == 1)
	// {
	// 	join_threads(ap);
	// 	free_memory(ap);
	// }
	return ;
}

void	*routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	while (1)
	{
		get_a_table(philo);
		eat(philo);
		drop_forks(philo);
		ft_sleep(philo);
		print_event(philo, "is thinking");
		print_event(philo, "is thinking");
	}
	return (NULL);
}

void	get_a_table(t_philo *philo)
{
	while (1)
	{
		// pthread_mutex_lock(&philo->info->csi);
		// if (philo->info->dead_id > 0)
		// {
		// 	pthread_mutex_unlock(&philo->info->csi);
		// 	return ;
		// }
		// pthread_mutex_unlock(&philo->info->csi);
		if (philo->id % 2 > 0)
		{
			pick_right(philo);
			pick_left(philo);
			check(philo);
			break ;
		}
		else
		{
			pick_left(philo);
			pick_right(philo);
			check(philo);
			break ;
		}
	}
	return ;
}

void	pick_left(t_philo *philo)
{
	pthread_mutex_lock(philo->l_lock);
	*(philo->l_fork) = 1;
	print_event(philo, "has taken a fork");
}

void	pick_right(t_philo *philo)
{
	pthread_mutex_lock(philo->r_lock);
	*(philo->r_fork) = 1;
	print_event(philo, "has taken a fork");
}

void	check(t_philo *philo)
{
	pthread_mutex_lock(philo->taken_lock_ptr);
	if (*(philo->r_fork) == 0 && *(philo->l_fork) == 1)
	{
		philo->taken_ptr = false;
		drop_left(philo);
		pthread_mutex_unlock(philo->taken_lock_ptr);
		return ;
	}
	else if (*(philo->l_fork) == 0 && *(philo->r_fork) == 1)
	{
		philo->taken_ptr = false;
		drop_right(philo);
		pthread_mutex_unlock(philo->taken_lock_ptr);
		return ;
	}
	else if (*(philo->l_fork) == 0 && *(philo->r_fork) == 0)
	{
		philo->taken_ptr = false;
		pthread_mutex_unlock(philo->taken_lock_ptr);
		return ;
	}
	*(philo->taken_ptr) = true;
	pthread_mutex_unlock(philo->taken_lock_ptr);
	return ;
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 > 0)
	{
		drop_left(philo);
		drop_right(philo);
	}
	else if (philo->id % 2 == 0)
	{
		drop_right(philo);
		drop_left(philo);
	}
}

void	drop_left(t_philo *philo)
{
	philo->l_fork = 0;
	pthread_mutex_unlock(philo->l_lock);
}

void   drop_right(t_philo *philo)
{
	philo->r_fork = 0;
	pthread_mutex_unlock(philo->r_lock);
}

