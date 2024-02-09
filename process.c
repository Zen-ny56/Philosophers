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
		size_t			time;

		time = get_time();
		pthread_mutex_lock(&info->write);
		printf("%zu %d philo has died\n", time - info->start, monitor_simulation(info));
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
	while (!check_status(philo))
	{
		if (get_a_table(philo))
			break ;
		if (eat(philo))
			break ;
		if (drop_forks(philo))
			break ;
		if (ft_sleep(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (NULL);
}

int		get_a_table(t_philo *philo)
{

	if (check_status(philo))
		return (1);
	if (philo->id % 2 > 0)
	{
		pick_right(philo);
		pick_left(philo);
		drop_one(philo);
		usleep(20);
		return (0);
	}
	else
	{
		pick_left(philo);
		pick_right(philo);
		drop_one(philo);
		usleep(20);
		return (0);
	}
	return (0);
}

void	drop_one(t_philo *philo)
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
	else
		*(philo->taken_ptr) = true;
	pthread_mutex_unlock(philo->taken_lock_ptr);
	return ;
}

int	drop_forks(t_philo *philo)
{
	if (check_status(philo))
		return (1);
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
	return (0);
}

void	drop_left(t_philo *philo)
{
	*(philo->l_fork) = 0;
	print_event(philo, "has dropped a fork");
	pthread_mutex_unlock(philo->l_lock);
}

void   drop_right(t_philo *philo)
{
	*(philo->r_fork) = 0;
	print_event(philo, "has dropped a fork");
	pthread_mutex_unlock(philo->r_lock);
}

