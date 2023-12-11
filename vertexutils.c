#include "include/fdf.h"

int	find_min_x(t_vertex *array)
{
	int	i;
	int	smallest;

	i = 0;
	smallest = INT_MAX;
	while (array[i].w)
	{
		if (array[i].x < smallest)
			smallest = array[i].x;
		i++;
	}
	return (smallest);
}

int	find_min_y(t_vertex *array)
{
	int	i;
	int	smallest;

	i = 0;
	smallest = INT_MAX;
	while (array[i].w)
	{
		if (array[i].y < smallest)
			smallest = array[i].y;
		i++;
	}
	return (smallest);
}

int	find_max_x(t_vertex *array)
{
	int	i;
	int	biggest;

	i = 0;
	biggest = INT_MIN;
	while (array[i].w)
	{
		if (array[i].x < biggest)
			biggest = array[i].x;
		i++;
	}
	return (biggest);
}

int	find_max_y(t_vertex *array)
{
	int	i;
	int	biggest;

	i = 0;
	biggest = INT_MIN;
	while (array[i].w)
	{
		if (array[i].y < biggest)
			biggest = array[i].y;
		i++;
	}
	return (biggest);
}

void	translate(t_vertex *array, int x, int y, int z)
{
	int	i;

	i = 0;
	while (array[i].w)
	{
		array[i].x += x;
		array[i].y += y;
		array[i].z += z;
		i++;
	}
}
