/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:06:35 by toramo            #+#    #+#             */
/*   Updated: 2023/12/18 10:06:36 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	apply_m(t_vertex *model, double *m)
{
	int	i;

	i = 0;
	while (model[i].w)
	{
		mmult(&model[i], m);
		i++;
	}
}

void	memset_color(mlx_image_t *img, int rgba)
{
	unsigned long	i;

	i = 0;
	while (i < img->width * img->height * sizeof(int))
	{
		if (i % 4 == 0)
			memset(&img->pixels[i], get_r(rgba), 1);
		if (i % 4 == 1)
			memset(&img->pixels[i], get_g(rgba), 1);
		if (i % 4 == 2)
			memset(&img->pixels[i], get_b(rgba), 1);
		if (i % 4 == 3)
			memset(&img->pixels[i], get_a(rgba), 1);
		i++;
	}
}

void	black_img(mlx_image_t *black)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < black->height)
	{
		while (i < black->width)
		{
			mlx_put_pixel(black, i, j, get_rgba(255, 255, 255, 255));
			i++;
		}
		j++;
	}
}

void	viewport(t_fdf *t)
{
	int	i;

	i = 0;
	while (i < t->msize)
	{
		t->model[i].x = WIDTH / 2.0 * t->model[i].x
			+ t->model[i].x + WIDTH / 2.0;
		t->model[i].y = HEIGHT / 2.0 * t->model[i].y
			+ t->model[i].y + HEIGHT / 2.0;
		t->model[i].z = (t->far - t->near) / 2.0 + (t->far + t->near) / 2.0;
		if (round(t->model[i].x <= 0) || round(t->model[i].y) <= 0
			|| round(t->model[i].z) <= 0 || round(t->model[i].x) >= WIDTH
			|| round(t->model[i].y) >= HEIGHT)
			t->model[i].enabled = false;
		i++;
	}
}

void	normalize_and_clip(t_fdf *t)
{
	int	i;

	i = 0;
	{
		while (i < t->msize)
		{
			if (t->persp == true && t->model[i].z < 0)
				t->model[i].enabled = false;
			else
			{
				t->model[i].x = t->model[i].x / t->model[i].w;
				t->model[i].y = t->model[i].y / t->model[i].w;
				t->model[i].z = t->model[i].z / t->model[i].w;
				if (t->model[i].z > -1 && t->model[i].z < 1
					&& t->model[i].x > -1 && t->model[i].x < 1
					&& t->model[i].y > -1 && t->model[i].y < 1)
					t->model[i].enabled = true;
				else
					t->model[i].enabled = false;
			}
			i++;
		}
	}
}
