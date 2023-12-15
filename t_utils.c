#include "include/fdf.h"

t_fdf	*init_fdf(t_fdf *t)
{
	t->a = 0;
	t->b = 0;
	t->c = 0;
	t->tx = 0;
	t->ty = 0;
	t->tz = 0;
	return (t);
}

void	make_fustrum(double fovy, double aspect, t_fdf *t)
{
	double		degtorad;
	double		tangent;
	double		height;

	degtorad = M_PI / 180;
	tangent = tan(fovy / 2 * degtorad);
	height = t->near * tangent;
	t->left = -1 * height * aspect;
	t->right = height * aspect;
	t->bottom = -1 * t->near * tangent;
	t->top = t->near * tangent;
}

t_fdf	*default_fdf(t_fdf *t)
{
	t->a = 0;
	t->b = 20 * M_PI / 180;
	t->c = -1 * 60 * M_PI / 180;
	t->near = 1;
	t->far = 10;
	t->angle = 120;
	make_fustrum(t->angle, WIDTH * 1.0 / HEIGHT, t);
	t->tx = 0;
	t->ty = 0;
	t->tz = -30;
	return (t);
}
