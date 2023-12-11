#include "include/fdf.h"

t_vertex	mmult(t_vertex v, double **m)
{
	v.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
	v.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
	v.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
	v.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
	return (v);
}

double	**modelm(double **m, t_transform *t)
{
	m[0][0] = cos(t->a) * cos(t->b);
	m[0][1] = cos(t->a) * sin(t->b) * sin(t->c) - sin(t->a) * cos(t->c);
	m[0][2] = cos(t->a) * sin(t->b) * cos(t->c) + sin(t->a) * sin(t->c);
	m[0][3] = t->tx;
	m[1][0] = sin(t->a) * cos(t->b);
	m[1][1] = sin(t->a) * sin(t->b) * sin(t->c) + cos(t->a) * cos(t->c);
	m[1][2] = sin(t->a) * sin(t->b) * cos(t->c) - cos(t->a) * sin(t->c);
	m[1][3] = t->ty;
	m[2][0] = -1 * sin(t->b);
	m[2][1] = cos(t->b) * sin(t->c);
	m[2][2] = cos(t->b) * cos(t->c);
	m[2][3] = t->tz;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
	return (m);
}

double	**orthom(double **m, t_transform *t)
{
	m[0][0] = 2 / (t->right - t->left);
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = -1 * (t->right + t->left) / (t->right - t->left);
	m[1][0] = 0;
	m[1][1] = 2 / (t->top - t->bottom);
	m[1][2] = 0;
	m[1][3] = -1 * (t->top + t->bottom) / (t->top - t->bottom);
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = -2 / (t->far - t->near);
	m[2][3] = -1 * (t->near + t->far) / (t->near - t->far);
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 0;
	return (m);
}

double	**perspectivem(double **m, t_transform *t)
{
	m[0][0] = 2 * t->near / (t->right - t->left);
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = -t->near * (t->right + t->left) / (t->right - t->left);
	m[1][0] = 0;
	m[1][1] = 2 * t->near / (t->top - t->bottom);
	m[1][2] = 0;
	m[1][3] = -1 * t->near * (t->top + t->bottom) / (t->top - t->bottom);
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = -1 * (t->far + t->near) / (t->far - t->near);
	m[2][3] = 2 * t->far * t->near / (t->near - t->far);
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = -1;
	m[3][3] = 0;
	return (m);
}

double	**scalem(double **m, t_transform *t)
{
	m[0][0] = WIDTH * 1.0 / 2;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = WIDTH * 1.0 / 2;
	m[1][0] = 0;
	m[1][1] = HEIGHT * 1.0 / 2;
	m[1][2] = 0;
	m[1][3] = HEIGHT * 1.0 / 2;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
	return (m);
}
