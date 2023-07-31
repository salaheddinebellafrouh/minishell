#include "stdlib.h"
#include "unistd.h"

int	main(void)
{
	while (1)
	{
		system("leaks minishell");
		sleep(1);
	}
}