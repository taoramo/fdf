#include "include/fdf.h"

void	rotate_x(t_vertex *model, double a)
{
	int		i;
	double	x;
	double	y;
	double	z;

	i = 0;
	while (model[i].w)
	{
		x = model[i].x;
		y = cos(a) * model[i].y - sin(a) * model[i].z;
		z = sin(a) * model[i].y + cos(a) * model[i].z;
		model[i].y = round(y);
		model[i].z = round(z);
		i++;
	}
}

void	rotate_y(t_vertex *model, double a)
{
	int		i;
	double	x;
	double	y;
	double	z;

	i = 0;
	while (model[i].w)
	{
		model[i].y = y;
		x = cos(a) * model[i].x + sin(a) * model[i].z;
		z = -1 * sin(a) * model[i].x + cos(a) * model[i].z;
		model[i].x = round(x);
		model[i].z = round(z);
	}
}
