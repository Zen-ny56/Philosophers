#include "philosophers.h"

int main(int ac, char **av)
{
	t_data	*info;

	if (ac > 6 || ac < 5)
	{
		write(1, "invalid no. of parameters\n", 27);
		return (1);
	}
	parse(av);
	info = (t_data *)malloc(sizeof(t_data) * 1);
	init(av, info);
	if (info->num_philo == 1)
		case_one(info);
	else
	{
		alloc(info);
		mutex_init(info);
		thread_process(info);
		free_mem(info);
	}
	exit(0);
}