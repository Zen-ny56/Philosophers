#include "philosophers.h"

void	thread_process(t_data *ap)
{
	int	i;

	i = 0;
	init_personal_data(ap);
	ap->start = get_time();
	while (i < ap->num_philo)
	{
		ap->philos[i].last_meal_time = ap->start;
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
	{
		pthread_create(&ap->philos[i].thread, NULL, &routine, &ap->philos[i]);
		i++;
	}
	pthread_create(&ap->monitor, NULL, &monitor, ap);
	pthread_create(&ap->waiter, NULL, &waiter, ap);
	if (terminate(ap) == 1)
	{
		join_threads(ap);
		free_memory(ap);
	}
	return ;
}

void	*routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	while (1)
	{
		get_a_table(philo);
		if (check(philo) == 0)
		{
			eat(philo);
			drop_forks(philo);
			ft_sleep(philo);
			print_event(philo, "is thinking");
		}
		print_event(philo, "is thinking");
	}
	return (NULL);
}

void	get_a_table(t_philo *philo)
{
	while (1)
	{
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
	pthread_mutex_lock(&philo->l_fork);
	philo->l_fork = 1;
	print_event(philo, "has taken a fork");
}

void	pick_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	philo->r_fork = 1;
	print_event(philo, "has taken a fork");
}

int	check(t_philo *philo)
{
	pthread_mutex_lock(&philo->checkp);
	if (philo->r_fork == 0 && philo->l_fork == 1)
	{
		drop_left(philo);
		pthread_mutex_unlock(&philo->checkp);
		return (1);
	}
	else if (philo->l_fork == 0 && philo->r_fork == 1)
	{
		drop_right(philo);
		pthread_mutex_unlock(&philo->checkp);
		return (1);
	}
	else if (philo->l_fork == 0 && philo->r_fork == 0)
	{
		pthread_mutex_unlock(&philo->checkp);
		return (1);
	}
	pthread_mutex_unlock(&philo->checkp);
	return (0);
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

// void	bon_appetit(t_philo *philo)
// {
// 	eat(philo);
// 	drop_forks(philo);
// 	ft_sleep(philo);
// }

// void	get_a_table(t_philo *philo)
// {

// 	if (philo->id % 2 > 0)
// 	{
// 		// pthread_mutex_lock(&philo->p_data);
// 		// if (*(philo->ra) == false && *(philo->la) == false)
// 		// {
// 	    // 	pthread_mutex_lock(philo->r_lock);
// 		// 	philo->r_fork = 1;
// 		// 	pthread_mutex_lock(philo->l_lock);
// 		// 	philo->l_fork = 1;
// 		// 	*(philo->ra) = false; 
// 		// 	*(philo->la) = false;
// 		// 	pthread_mutex_unlock(&philo->p_data);
// 		// 	set_cutlery(philo);
// 		// 	print_event(philo, "has taken a fork");
// 		// 	print_event(philo, "has taken a fork");
// 		// }
// 		// pthread_mutex_unlock(&philo->p_data);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&philo->p_data);
// 		if (*(philo->la) == false && *(philo->ra) == false)
// 		{
// 			pthread_mutex_lock(philo->l_fork);
// 			pthread_mutex_lock(philo->r_fork);
// 			*(philo->la) = false;
// 			*(philo->ra) = false;
// 			pthread_mutex_unlock(&philo->p_data);
// 			set_cutlery(philo);
// 			print_event(philo, "has taken a fork");
// 			print_event(philo, "has taken a fork");
// 		}
// 		pthread_mutex_unlock(&philo->p_data);
// 	}
// }

// void	bon_appetit(t_philo *philo)
// {
// 	eat(philo);
// 	drop_forks(philo);
// 	ft_sleep(philo);
// 	print_event(philo, "is thinking");
// 	else if (satisfied(philo) == 1)
// 		print_event(philo, "is thinking");
// }

// void	drop_forks(t_philo *philo)
// {
// 	if (philo->id % 2 > 0)
// 	{
// 		bri_the_check(philo);
// 		pthread_mutex_unlock(philo->l_fork);
// 		pthread_mutex_unlock(philo->r_fork);
// 	}
// 	else if (philo->id % 2 == 0)
// 	{
// 		bri_the_check(philo);
// 		pthread_mutex_unlock(philo->r_fork);
// 		pthread_mutex_unlock(philo->l_fork);
// 	}
// }
