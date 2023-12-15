#include "include/fdf.h"

void	draw_high(t_vertex v1, t_vertex v2, t_fdf *t)
{
	{
		if (v1.y > v2.y)
		{
			t->dx = round(v1.x - v2.x);
			t->dy = round(v1.y - v1.y);
			t->xi = 1;
			if (t->dy < 0)
			{
				t->xi = -1;
				t->dx = -1 * t->dx;
			}
			bres_high(v2, v1, t);
		}
		else
		{
			t->dx = round(v2.x - v1.x);
			t->dy = round(v2.y - v1.y);
			t->xi = 1;
			if (t->dy < 0)
			{
				t->xi = -1;
				t->dx = -1 * t->dx;
			}
			bres_high(v1, v2, t);
		}
	}
}

void	draw(t_vertex v1, t_vertex v2, t_fdf *t)
{
	if (ft_abs(v2.y - v1.y) < ft_abs(v2.x - v1.x))
	{
		if (v1.x > v2.x)
		{
			t->dx = round(v1.x - v2.x);
			t->dy = round(v1.y - v2.y);
			t->yi = 1;
			if (t->dx < 0)
			{
				t->yi = -1;
				t->dy = -1 * t->dy;
			}
			bres_low(v2, v1, t);
		}
		else
		{
			t->dx = round(v2.x - v1.x);
			t->dy = round(v2.y - v1.y);
			t->yi = 1;
			if (t->dx < 0)
			{
				t->yi = -1;
				t->dy = -1 * t->dy;
			}
			bres_low(v1, v2, t);
		}
	}
	else
		draw_high(v1, v2, t);
}

void	draw_line(t_fdf *t, int i)
{
	if (i % t->stride != t->stride - 1 && (vertex_is_valid(t->model[i])
			&& vertex_is_valid(t->model[i + 1])))
		draw(t->model[i], t->model[i + 1], t);
	if (i / t->stride < t->linecount && (vertex_is_valid(t->model[i])
			&& vertex_is_valid(t->model[i + t->stride])))
		draw(t->model[i], t->model[i + t->stride], t);
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
