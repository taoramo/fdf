#include "include/fdf.h"

void	apply_ortho(t_fdf *t)
{
	make_fustrum_ortho(ft_abs_float(t->angle % 180), WIDTH * 1.0 / HEIGHT, t);
	apply_m(t->model, orthom(t->m, t));
}

void	apply_perspective(t_fdf *t)
{
	make_fustrum(ft_abs_float(t->angle % 180), WIDTH * 1.0 / HEIGHT, t);
	apply_m(t->model, perspectivem(t->m, t));
}

void	make_fustrum(double fovy, double aspect, t_fdf *t)
{
	double		degtorad;
	double		tangent;
	double		height;

	degtorad = M_PI / 180;
	tangent = tan(fovy / 2 * degtorad);
	height = t->near * tangent;
	t->left = 1 * height * aspect;
	t->right = -1 * height * aspect;
	t->bottom = -1 * t->near * tangent;
	t->top = t->near * tangent;
	t->near = 10;
	t->far = 1;
}

void	make_fustrum_ortho(double fovy, double aspect, t_fdf *t)
{
	double		degtorad;
	double		tangent;
	double		height;

	degtorad = M_PI / 180;
	tangent = tan(fovy / 2 * degtorad);
	height = t->near * tangent;
	t->left = 1 * height * aspect;
	t->right = -1 * height * aspect;
	t->bottom = -1 * t->near * tangent;
	t->top = t->near * tangent;
	t->near = -8 * t->linecount;
	t->far = 8 * t->linecount;
}

t_fdf	*default_fdf(t_fdf *t)
{
	t->a = 0 * M_PI / 180;
	t->b = 0.5;
	t->c = 2.3;
	t->persp = false;
	t->angle = 60;
	t->tx = 0;
	t->ty = 0;
	t->tz = 0;
	return (t);
}
