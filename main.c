#include "philosophers.h"

int main(int ac, char **av)
{
	t_data	ap;

	if (ac > 6 || ac < 5)
	{
		write(1, "invalid no. of parameters\n", 27);
		return (1);
	}
	parse(av);
	ap.start = get_start_time(&ap);
	init(av, &ap);
	alloc(&ap);
	mutex_init(&ap);
	thread_process(&ap);
	return (0);
}