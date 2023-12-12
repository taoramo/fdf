#include "include/fdf.h"

t_transform	*init_transform(t_transform *t)
{
	t->a = 0;
	t->b = 0;
	t->c = 0;
	t->tx = 0;
	t->ty = 0;
	t->tz = 0;
	return (t);
}

void	make_fustrum(double fovy, double aspect, t_transform *t)
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

t_transform	*default_transform(t_transform *t)
{
	t->a = 0;
	t->b = 20 * M_PI / 180;
	t->c = -1 * 60 * M_PI / 180;
	t->near = 2;
	t->far = 10;
	make_fustrum(120, 1280.0 / 1080.0, t);
	t->tx = -100;
	t->ty = 0;
	t->tz = -100;
	return (t);
}
