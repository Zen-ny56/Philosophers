#include "philosophers.h"

int main(int ac, char **av)
{
	t_data	*ap;

	if (ac > 6 || ac < 5)
	{
		write(1, "invalid no. of parameters\n", 27);
		return (1);
	}
	parse(av);
	ap = (t_data *)malloc(sizeof(t_data) * 1);
	init(av, ap);
	alloc(ap);
	mutex_init(ap);
	thread_process(ap);
}