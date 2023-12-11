#include "include/fdf.h"

int	find_min_z(t_vertex *array)
{
	int	i;
	int	smallest;

	i = 0;
	smallest = INT_MAX;
	while (array[i].w)
	{
		if (array[i].z < smallest)
			smallest = array[i].z;
		i++;
	}
	return (smallest);
}
