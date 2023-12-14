#include "include/fdf.h"

void	bresenham_right(t_vertex *model, int i,
	t_vertex vertex1, t_vertex vertex2)
{
	int	m;
	int	x;
	int	y;
	int	slope_error;

	m = 2 * (vertex2.y - vertex1.y);
	slope_error = m - (vertex2.x - vertex1.x);
	x = vertex1.x;
	y = vertex1.y;
	while (x <= vertex2.x)
	{
		model[i].x = x++;
		model[i].y = y;
		model[i].z = vertex1.z;
		model[i].w = 1;
		slope_error += m;
		if (slope_error >= 0)
		{
			y++;
			slope_error -= 2 * (vertex2.x - vertex1.x);
		}
		i++;
	}
}

void	bresenham_near(t_vertex *model, int i,
	t_vertex vertex1, t_vertex vertex2)
{
	int	m;
	int	z;
	int	y;
	int	slope_error;

	m = 2 * (vertex2.y - vertex1.y);
	slope_error = m - (vertex2.z - vertex1.z);
	z = vertex1.z;
	y = vertex1.y;
	while (z <= vertex2.z)
	{
		model[i].z = z++;
		model[i].y = y;
		model[i].x = vertex1.x;
		model[i].w = 1;
		slope_error += m;
		if (slope_error >= 0)
		{
			y++;
			slope_error -= 2 * (vertex2.z - vertex1.z);
		}
		i++;
	}
}

void	draw_line_x(t_vertex *model, int i, t_vertex v1, t_vertex v2)
{
	double	dx;
	double	dy;
	double	x;
	double	y;

	x = v1.x;
	y = v1.y;
	dx = v2.x - v1.x;
	dy = v2.y - v1.y;
	while (x < v2.x)
	{
		model[i].x = x;
		model[i].y = y;
		model[i].z = v1.z;
		model[i].w = 1;
		x += dx / MODEL_SCALE;
		y += dy / MODEL_SCALE;

		i++;
	}
}

void	draw_line_z(t_vertex *model, int i, t_vertex v1, t_vertex v2)
{
	double	dz;
	double	dy;
	double	z;
	double	y;

	z = v1.z;
	y = v1.y;
	dz = v2.z - v1.z;
	dy = v2.y - v1.y;
	while (z < v2.z)
	{
		model[i].z = z;
		model[i].y = y;
		model[i].x = v1.x;
		model[i].w = 1;
		z += dz / MODEL_SCALE;
		y += dy / MODEL_SCALE;
		i++;
	}
}

static t_vertex	*exit_function(t_vertex *array)
{
	free(array);
	return (0);
}

void	draw_lines(t_vertex *array)
{
	int			i;
	int			j;
	t_vertex	*model;

	model = ft_calloc(sizeof(t_vertex), (find_max_x(array)
				* find_max_z(array) * 3 * MODEL_SCALE));
	if (!model)
		exit_function(array);
	i = 0;
	j = 0;
	while (array[i].w)
	{
		if (vertex_exists_xz(array, array[i].x + 1, array[i].z))
			draw_line_x(model, j, array[i], array[i + 1]);
		while (model[j].w)
			j++;
		if (vertex_exists_xz(array, array[i].x, array[i].z + 1))
			draw_line_z(model, j, array[i], find_vrtx_clsr(array, array[i]));
		while (model[j].w)
			j++;
		i++;
	}
	free(array);
	init_img(model, j);
}
