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
	printf("Parsing done\n");
	ap = (t_data *)malloc(sizeof(t_data) * 1);
	init(av, ap);
	printf("Init done\n");
	alloc(ap);
	mutex_init(ap);
	printf("Mutex init done\n");
	thread_process(ap);
	printf("asdfsa init done\n");
}