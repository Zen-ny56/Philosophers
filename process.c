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

		pthread_mutex_lock(&info->write);
		time = get_time();
		printf("%zu %d died\n", time - info->start, monitor_simulation(info));
		pthread_mutex_unlock(&info->write);
	}
	i = 0;
	while (i < info->num_philo)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
}

void	*routine(void *arg)
{
	
	t_philo	*philo;
	philo = (t_philo *)arg;
	
	while (!check_status(philo))
	{
		usleep(30);
		if (pick_forks(philo))
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

int		pick_forks(t_philo *philo)
{

	if (check_status(philo))
		return (1);
	if (philo->id % 2 != 0)
	{
		usleep(1500);
		pthread_mutex_lock(philo->r_lock);
		pthread_mutex_lock(philo->l_lock);
		while (*(philo->r_fork) == philo->id || *(philo->l_fork) == philo->id)
		{
			pthread_mutex_unlock(philo->l_lock);
			pthread_mutex_unlock(philo->r_lock);
			usleep(100);
			pthread_mutex_lock(philo->r_lock);
			pthread_mutex_lock(philo->l_lock);
		}
		*(philo->l_fork) = philo->id;
		*(philo->r_fork) = philo->id;
		print_event(philo, "has taken a fork");
		print_event(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info->time_lock);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->info->time_lock);
		print_event(philo, "is eating");
	}
	else
	{
		pthread_mutex_lock(philo->l_lock);
		pthread_mutex_lock(philo->r_lock);
		while (*(philo->l_fork) == philo->id || *(philo->l_fork) == philo->id)
		{
			pthread_mutex_unlock(philo->r_lock);
			pthread_mutex_unlock(philo->l_lock);
			usleep(100);
			pthread_mutex_lock(philo->l_lock);
			pthread_mutex_lock(philo->r_lock);
		}
		*(philo->r_fork) = philo->id;
		*(philo->l_fork) = philo->id;
		print_event(philo, "has taken a fork");
		print_event(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info->time_lock);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->info->time_lock);
		print_event(philo, "is eating");
	}
	return (0);
}



int	drop_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->l_lock);
		pthread_mutex_unlock(philo->r_lock);
	}
	else
	{
		pthread_mutex_unlock(philo->r_lock);
		pthread_mutex_unlock(philo->l_lock);
	}
	pthread_mutex_lock(&philo->info->meal_lock);
	if (philo->meals_eaten == philo->info->max_meals)
	{
		philo->info->full_philos++;
		pthread_mutex_unlock(&philo->info->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->meal_lock);
	return (0);
}
