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

t_transform	*default_transform(t_transform *t)
{
	t->a = 45 * M_PI / 180;
	t->b = 45 * M_PI / 180;
	t->c = 45 * M_PI / 180;
	t->left = 0;
	t->right = 15 * MODEL_SCALE;
	t->bottom = 0;
	t->top = 15 * MODEL_SCALE;
	t->near = -1 * 20 * MODEL_SCALE;
	t->far = 0;
	t->tx = 0;
	t->ty = 0;
	t->tz = 0;
	return (t);
}
