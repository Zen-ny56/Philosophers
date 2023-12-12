#include "philosophers.h"

void	thread_process(t_data *ap)
{
	int	i;

	i = 0;
	init_personal_data(ap);
	ap->start = get_start_time();
	while (i < ap->num_philo)
	{
		pthread_create(&ap->philos[i].thread, NULL, &routine, &ap->philos[i]);
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
    {
        pthread_join(ap->philos[i].thread, NULL);
		printf("Joined thread %d\n", i);
        i++;
    }
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->info->meal_times > 0)
	{
		while (lock_mutex(philo) == 0 && philo->meals_eaten < philo->info->meal_times)
		{
			if (philo->info->started == false)
			{
				philo->info->started = true;
				registration(philo);
				pthread_mutex_unlock(&philo->info->lock);
				r_u_on_the_list(philo);
				get_a_table(philo);
				bon_appetit(philo);
			}
			else
			{
				pthread_mutex_unlock(&philo->info->lock);
				if (philo->lflag == philo->id && philo->rflag == philo->id)
				{
					pthread_mutex_unlock(&philo->info->lock);
					pthread_mutex_lock(&philo->front_desk);
					philo->just_ate = true;
					pthread_mutex_unlock(&philo->front_desk);
				}
				registration(philo);
				r_u_on_the_list(philo);
				get_a_table(philo);
				bon_appetit(philo);
			}
		}
	}
	return (NULL);
}

void	registration(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->picking_first);
	if (philo->id % 2 > 0 && philo->info->is_even == -1)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		print_event(philo, "has taken right fork");
		print_event(philo, "has taken left fork");
		philo->taken_forks = true;
		philo->pickup_forks = true;
		philo->info->is_even = 1;
	}
	else if (philo->id % 2 == 0 && philo->info->is_even == -1)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		print_event(philo, "has taken left fork");
		print_event(philo, "has taken right fork");
		philo->taken_forks = true;
		philo->pickup_forks = true;
		philo->info->is_even = 2;
	}
	pthread_mutex_unlock(&philo->info->picking_first);
}

void	r_u_on_the_list(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	if (philo->info->is_even == 1)
	{
		if (philo->id % 2 > 0)
		{
			pthread_mutex_lock(&philo->front_desk);
			philo->pickup_forks = true;
			pthread_mutex_unlock(&philo->front_desk);
		}
	}
	else if (philo->info->is_even == 2)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->front_desk);
			philo->pickup_forks = true;
			pthread_mutex_unlock(&philo->front_desk);
		}
	}
	pthread_mutex_unlock(&philo->info->lock);
}

void	get_a_table(t_philo *philo)
{
	if (philo->pickup_forks == true)
	{
		if (philo->id % 2 > 0 && philo->taken_forks == false)
		{
			pthread_mutex_lock(philo->r_fork);
			print_event(philo, "has taken right fork");
			pthread_mutex_lock(philo->r_fork);
			print_event(philo, "has taken left fork");
			philo->taken_forks = true;
		}
		else if (philo->id % 2 == 0 && philo->taken_forks == false)
		{
			pthread_mutex_lock(philo->r_fork);
			print_event(philo, "has taken left fork");
			pthread_mutex_lock(philo->l_fork);
			print_event(philo, "has taken right fork");
			philo->taken_forks = true;
		}
	}
}

void	bon_appetit(t_philo *philo)
{
	if (philo->taken_forks == true)
	{
		eat(philo);
		drop_forks(philo);
		ft_sleep(philo);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(&philo->info->lock);
	philo->last_meal_time = get_elapsed_time(philo->info);
	// philo->meals_eaten++;
	philo->taken_forks = false;
	pthread_mutex_unlock(&philo->info->lock);
}

int	lock_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	return (0);
}