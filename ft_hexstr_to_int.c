#include "include/fdf.h"

int	ft_hexstr_to_int(char *str)
{
	int	i;
	int	result;

	result = 0;
	if (!str)
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			result = result * 16 + str[i] - 48;
		else if (str[i] >= 65 && str[i] <= 70)
			result = result * 16 + str[i] - 65 + 10;
		i++;
	}
	return (result);
}
