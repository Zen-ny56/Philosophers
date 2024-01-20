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
		if (oj(philo) == 1 || ru_full(philo->info) == 1)
		{
			process_kill(philo->info);
			return (NULL);
		}
		get_a_table(philo);
		bon_appetit(philo);
	}
	return (NULL);
}

void	get_a_table(t_philo *philo)
{

	if (philo->id % 2 > 0)
	{
		if (avai_fork(philo) == 0 && satisfied(philo) == 0)
		{
	    	pthread_mutex_lock(philo->r_fork);
			pthread_mutex_lock(philo->l_fork);
			*(philo->rflag) = philo->id;
			*(philo->lflag) = philo->id;
			set_cutlery(philo);
			print_event(philo, "has taken a fork");
			print_event(philo, "has taken a fork");
		}
	}
	else
	{
		if (avai_fork(philo) == 0 && satisfied(philo) == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			pthread_mutex_lock(philo->r_fork);
			*(philo->rflag) = philo->id;
			*(philo->lflag)= philo->id;
			set_cutlery(philo);
			print_event(philo, "has taken a fork");
			print_event(philo, "has taken a fork");
		}
	}
}

void	bon_appetit(t_philo *philo)
{
	if (philo->is_eating == true )
	{
		eat(philo);
		drop_forks(philo);
		ft_sleep(philo);
		print_event(philo, "is thinking");
	}
	else if (satisfied(philo) == 1)
		print_event(philo, "is thinking");
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 > 0)
	{
		bri_the_check(philo);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else if (philo->id % 2 == 0)
	{
		bri_the_check(philo);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}
