#include "libft.h"

int	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}
