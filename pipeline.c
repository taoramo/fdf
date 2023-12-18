/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:06:07 by toramo            #+#    #+#             */
/*   Updated: 2023/12/18 10:06:11 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void static	ft_exit(t_fdf *master, int i)
{
	if (master->model)
		free(master->model);
	if (master->raw)
		free(master->raw);
	if (master->map)
		free(master->map);
	exit(i);
}

void	render_loop(t_fdf *t)
{
	mlx_image_t	*img_new;
	mlx_image_t	*temp;

	ft_memcpy(t->model, t->raw, t->msize * sizeof(t_vertex));
	img_new = mlx_new_image(t->mlx, WIDTH, HEIGHT);
	if (!img_new)
		ft_exit(t, 1);
	apply_m(t->model, modelm(t->m, t));
	if (!t->persp)
		apply_ortho(t);
	else
		apply_perspective(t);
	normalize_and_clip(t);
	viewport(t);
	temp = t->img;
	t->img = img_new;
	draw_lines(t);
	mlx_image_to_window(t->mlx, t->img, 0, 0);
	mlx_delete_image(t->mlx, temp);
	t->img = img_new;
}

void	render(t_fdf *t)
{
	mlx_image_t	*background;

	t = default_fdf(t);
	background = mlx_new_image(t->mlx, WIDTH, HEIGHT);
	memset_color(background, get_rgba(0, 0, 0, 255));
	mlx_image_to_window(t->mlx, background, 0, 0);
	render_loop(t);
	mlx_loop_hook(t->mlx, &hook, t);
	mlx_loop(t->mlx);
	ft_exit(t, 0);
}

void	init_img(t_fdf *t)
{
	double		m[16];
	mlx_t		*mlx;
	mlx_image_t	*img;

	t->model = ft_calloc(sizeof(t_vertex), t->msize);
	mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!mlx)
		ft_exit(t, 1);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		mlx_terminate(mlx);
		ft_exit(t, 1);
	}
	t->m = m;
	t->mlx = mlx;
	t->img = img;
	if (!mlx || !img)
		ft_exit(t, 1);
	render(t);
}
