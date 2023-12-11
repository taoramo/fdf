#include "include/fdf.h"

void	center(t_vertex *array)
{
	int	middle_x;
	int	middle_y;

	middle_x = (find_max_x(array) - find_min_x(array)) / 2;
	middle_y = (find_max_y(array) - find_min_y(array)) / 2;
	translate(array, middle_x * -1, 0, 0);
	translate(array, 0, middle_y * -1, 0);
}

void	scale(t_vertex *array, int x, int y, int z)
{
	int	i;

	i = 0;
	while (array[i].w)
	{
		array[i].x *= x;
		array[i].y *= y;
		array[i].z *= z;
		i++;
	}
}

bool	vertex_exists_xz(t_vertex *array, int x, int z)
{
	int	i;

	i = 0;
	while (array[i].w)
	{
		if (array[i].x == x && array[i].z == z)
			return (1);
		i++;
	}
	return (0);
}

t_vertex	find_vrtx_clsr(t_vertex *array, t_vertex vertex)
{
	int			i;
	t_vertex	empty;

	i = 0;
	empty.x = 0;
	empty.y = 0;
	empty.z = 0;
	empty.w = 0;
	while (array[i].w)
	{
		if (array[i].x == vertex.x && array[i].z == vertex.z + MODEL_SCALE)
			return (array[i]);
		i++;
	}
	return (empty);
}

int	find_max_z(t_vertex *array)
{
	int	i;
	int	biggest;

	i = 0;
	biggest = INT_MIN;
	while (array[i].w)
	{
		if (array[i].z < biggest)
			biggest = array[i].z;
		i++;
	}
	return (biggest);
}
