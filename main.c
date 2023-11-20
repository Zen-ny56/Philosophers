#include "philosophers.h"

int main(int ac, char **av)
{
	t_data	ap;
	if (ac > 6 || ac < 5)
	{
		write(1, "invalid no. of parameters\n", 27);
		return (1);
	}
	if (parse(av) == 0)
		write(1, "Parsed Successfully\n", 21);
	init(av, &ap);
	alloc(&ap);
	mutex_init(&ap);
	// pthread_create();
	return (0);
}