#include "include/fdf.h"

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
		if (v2.x - x >= 0.5)
			model[i].color = v1.color;
		else
			model[i].color = v2.color;
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
		if (v2.z - z >= 0.5)
			model[i].color = v1.color;
		else
			model[i].color = v2.color;
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
		if (vertex_exists_xz(&array[i], array[i].x + 1, array[i].z))
			draw_line_x(model, j, array[i], array[i + 1]);
		while (model[j].w)
			j++;
		if (vertex_exists_xz(&array[i], array[i].x, array[i].z + 1))
			draw_line_z(model, j, array[i], find_vrtx_clsr(&array[i], array[i]));
		while (model[j].w)
			j++;
		i++;
	}
	free(array);
	init_img(model, j);
}
