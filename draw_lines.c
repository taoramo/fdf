#include "include/fdf.h"

void	draw_line(t_fdf *t, int i)
{
	if (i % t->stride != t->stride - 1 && (vertex_is_valid(t->model[i])
			|| vertex_is_valid(t->model[i + 1])) && t->model[i].color != 0
		&& t->model[i + 1].color != 0)
		dda(t->model[i], t->model[i + 1], t);
	if (t->raw[i + t->stride].z < t->linecount && (vertex_is_valid(t->model[i])
			|| vertex_is_valid(t->model[i + t->stride]))
		&& i + t->stride < t->msize
		&& t->model[i].color != 0 && t->model[i + t->stride].color != 0)
		dda(t->model[i], t->model[i + t->stride], t);
}

void	draw_lines(t_fdf *t)
{
	int	i;

	i = 0;
	while (i < t->msize)
	{
		draw_line(t, i);
		i++;
	}
}
