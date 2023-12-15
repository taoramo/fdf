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

void	placeholder_vertex(t_vertex *array, int k)
{
	array[k].x = array[k - 1].x + 1;
	array[k].y = 0;
	array[k].z = array[k - 1].z;
	array[k].w = 1;
	array[k].color = 0;
}

int	vertex_is_valid(t_vertex v)
{
	if (!v.enabled || v.x < 0 || v.z < 0 || v.y < 0)
		return (0);
	else
		return (1);
}

int	pixel_is_valid(int x, int y)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		return (1);
	else
		return (0);
}
