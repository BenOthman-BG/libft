#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int main (int ac, char **av)
{
	if (ac == 2)
	{
		printf("ft_atoi : %d\n", ft_atoi(av[1]));
		printf("atoi : %d\n", atoi(av[1]));
	}
	return (0);
}
