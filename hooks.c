/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:05:29 by toramo            #+#    #+#             */
/*   Updated: 2023/12/18 10:05:31 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	hook3(t_fdf *t)
{
	if (mlx_is_key_down(t->mlx, MLX_KEY_SEMICOLON))
	{
		t->persp = false;
		t->tz = -50;
	}
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

void	hook2(t_fdf *t)
{
	if (mlx_is_key_down(t->mlx, MLX_KEY_L))
		t->tx = t->tx + 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_O))
		t->ty = t->ty - 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_U))
		t->ty = t->ty + 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_A))
		t->angle += 10;
	if (mlx_is_key_down(t->mlx, MLX_KEY_Z))
		t->angle -= 10;
	if (mlx_is_key_down(t->mlx, MLX_KEY_C))
		color(t);
	if (mlx_is_key_down(t->mlx, MLX_KEY_P))
	{
		t->persp = true;
		t->tz = 100;
	}
	hook3(t);
}

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
	hook2(t);
}
