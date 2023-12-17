#include "include/fdf.h"

void	mmult(t_vertex *v, double *m)
{
	float	x;
	float	y;
	float	z;
	float	w;

	x = m[0] * v->x + m[1] * v->y + m[2] * v->z + m[3] * v->w;
	y = m[4] * v->x + m[5] * v->y + m[6] * v->z + m[7] * v->w;
	z = m[8] * v->x + m[9] * v->y + m[10] * v->z + m[11] * v->w;
	w = m[12] * v->x + m[13] * v->y + m[14] * v->z + m[15] * v->w;
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = w;
}

double	*modelm(double *m, t_fdf *t)
{
	m[0] = cos(t->a) * cos(t->b);
	m[1] = cos(t->a) * sin(t->b) * sin(t->c) - sin(t->a) * cos(t->c);
	m[2] = cos(t->a) * sin(t->b) * cos(t->c) + sin(t->a) * sin(t->c);
	m[3] = t->tx;
	m[4] = sin(t->a) * cos(t->b);
	m[5] = sin(t->a) * sin(t->b) * sin(t->c) + cos(t->a) * cos(t->c);
	m[6] = sin(t->a) * sin(t->b) * cos(t->c) - cos(t->a) * sin(t->c);
	m[7] = t->ty;
	m[8] = -1 * sin(t->b);
	m[9] = cos(t->b) * sin(t->c);
	m[10] = cos(t->b) * cos(t->c);
	m[11] = t->tz;
	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
	return (m);
}

double	*orthom(double *m, t_fdf *t)
{
	m[0] = 2 / (t->right - t->left);
	m[1] = 0;
	m[2] = 0;
	m[3] = -1 * (t->right + t->left) / (t->right - t->left);
	m[4] = 0;
	m[5] = 2 / (t->top - t->bottom);
	m[6] = 0;
	m[7] = -1 * (t->top + t->bottom) / (t->top - t->bottom);
	m[8] = 0;
	m[9] = 0;
	m[10] = -2 / (t->far - t->near);
	m[11] = -1 * (t->far + t->near) / (t->far - t->near);
	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
	return (m);
}

double	*perspectivem(double *m, t_fdf *t)
{
	m[0] = 2 * t->near / (t->right - t->left);
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	m[4] = 0;
	m[5] = 2 * t->near / (t->top - t->bottom);
	m[6] = 0;
	m[7] = 0;
	m[8] = (t->right + t->left) / (t->right - t->left);
	m[9] = (t->top + t->bottom) / (t->top - t->bottom);
	m[10] = -1 * (t->far + t->near) / (t->far - t->near);
	m[11] = -1;
	m[12] = 0;
	m[13] = 0;
	m[14] = -2 * (t->far * t->near) / (t->far - t->near);
	m[15] = 0;
	return (m);
}

double	*scalem(double *m, t_fdf *t)
{
	m[0] = WIDTH * 1.0 / 2;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	m[4] = 0;
	m[5] = HEIGHT * 1.0 / 2;
	m[6] = 0;
	m[7] = 0;
	m[8] = 0;
	m[9] = 0;
	m[10] = (t->far + t->near) / 2;
	m[11] = 0;
	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
	return (m);
}
