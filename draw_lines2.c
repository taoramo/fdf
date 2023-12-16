#include "include/fdf.h"

float	ft_abs_float(float x)
{
	if (x < 0)
		return (-1.0 * x);
	else
		return (x);
}

int	inter_color(t_vertex va, t_vertex vb, t_fdf *t)
{
	int		red;
	int		green;
	int		blue;
	float	p;

	if (ft_abs(t->dx) >= ft_abs(t->dy))
		p = ft_abs_float((t->x - va.x) / (vb.x - va.x));
	else
		p = ft_abs_float((t->y - va.y) / (vb.y - va.y));
	red = get_r(vb.color) * p + get_r(va.color) * (p - 1);
	green = get_g(vb.color) * p + get_g(va.color) * (p - 1);
	blue = get_b(vb.color) * p + get_b(va.color) * (p - 1);
	return (get_rgba(red, green, blue, 255));
}

void	dda(t_vertex v1, t_vertex v2, t_fdf *t)
{
	float	step;
	int		i;

	t->dx = v2.x - v1.x;
	t->dy = v2.y - v1.y;
	if (ft_abs(t->dx) >= ft_abs(t->dy))
		step = ft_abs(t->dx);
	else
		step = ft_abs(t->dy);
	t->dx = t->dx / step;
	t->dy = t->dy / step;
	t->x = v1.x;
	t->y = v1.y;
	i = 0;
	while (i <= step)
	{
		if (pixel_is_valid(round(t->x), round(t->y)))
			mlx_put_pixel(t->img, round(t->x), round(t->y),
				v2.color);
		t->x = t->x + t->dx;
		t->y = t->y + t->dy;
		i++;
	}
}
