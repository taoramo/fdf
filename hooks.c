#include "MLX42/include/MLX42/MLX42.h"
#include "include/fdf.h"

void	hook(void *param)
{
	t_fdf	*t;

	t = (t_fdf *)param;
	if (mlx_is_key_down(t->mlx, MLX_KEY_LEFT))
		t->a = t->a - 0.1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_RIGHT))
		t->a = t->a + 0.1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_UP))
		t->b = t->b + 0.1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_DOWN))
		t->b = t->b - 0.1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_APOSTROPHE))
		t->c = t->c + 0.1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_SLASH))
		t->c = t->c - 0.1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_K))
		t->tz = t->tz + 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_I))
		t->tz = t->tz - 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_J))
		t->tx = t->tx - 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_L))
		t->tx = t->tx + 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_O))
		t->ty = t->ty - 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_U))
		t->ty = t->ty + 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_A))
	{
		t->angle += 10;
		make_fustrum(t->angle % 180, WIDTH * 1.0 / HEIGHT, t);
	}
	if (mlx_is_key_down(t->mlx, MLX_KEY_Z))
	{
		t->angle -= 10;
		make_fustrum(t->angle % 180, WIDTH * 1.0 / HEIGHT, t);
	}
	if (mlx_is_key_down(t->mlx, MLX_KEY_C))
		color(t);
	if (mlx_is_key_down(t->mlx, MLX_KEY_ESCAPE))
	{
		if (t->model)
			free(t->model);
		if (t->raw)
			free(t->raw);
		if (t->map)
			free(t->map);
		exit(0);
	}
	render_loop(t);
}
