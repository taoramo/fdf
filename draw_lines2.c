#include "include/fdf.h"

int	inter_color_low(t_vertex va, t_vertex vb, int x)
{
	int		red;
	int		green;
	int		blue;
	float	p;

	p = (x - va.x) / (vb.x - va.x);
	if (p < 0)
		p *= -1;
	red = get_r(va.color) * p + get_r(vb.color) * (1 - p);
	green = get_g(va.color) * p + get_g(vb.color) * (1 - p);
	blue = get_b(va.color) * p + get_b(vb.color) * (1 - p);
	return (get_rgba(red, green, blue, 255));
}

int	inter_color_high(t_vertex va, t_vertex vb, int y)
{
	int		red;
	int		green;
	int		blue;
	float	p;

	p = (y - va.y) / (vb.y - va.y);
	if (p < 0)
		p *= -1;
	red = get_r(va.color) * p + get_r(vb.color) * (1 - p);
	green = get_g(va.color) * p + get_g(vb.color) * (1 - p);
	blue = get_b(va.color) * p + get_b(vb.color) * (1 - p);
	return (get_rgba(red, green, blue, 255));
}

void	bres_low(t_vertex va, t_vertex vb, t_fdf *t)
{
	int	d;
	int	x;
	int	y;

	d = (2 * t->dy) - t->dx;
	y = round(va.y);
	x = round(va.x);
	while (x <= vb.x)
	{
		if (pixel_is_valid(x, y))
			mlx_put_pixel(t->img, x, y, 0x000000FF);
		if (d > 0)
		{
			y = y + t->yi;
			d = d + (2 * (t->dy - t->dx));
		}
		else
			d = d + 2 * t->dy;
		x++;
	}
}

void	bres_high(t_vertex va, t_vertex vb, t_fdf *t)
{
	int	d;
	int	x;
	int	y;

	d = (2 * t->dx) - t->dy;
	x = round(va.x);
	y = round(va.y);
	while (y <= vb.y)
	{
		if (pixel_is_valid(x, y))
			mlx_put_pixel(t->img, x, y, 0x000000FF);
		if (d > 0)
		{
			x = x + t->xi;
			d = d + (2 * (t->dx - t->dy));
		}
		else
			d = d + 2 * t->dx;
		y++;
	}
}
