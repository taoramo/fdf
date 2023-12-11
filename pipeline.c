#include "include/fdf.h"

void	clip(t_vertex *model)
{
	int	i;

	i = 0;
	while (model[i].w)
	{
		if (model[i].x < 1 && model[i].x > -1
			&& model[i].y < 1 && model[i].y > -1
			&& model[i].z < 1 && model[i].z > -1)
			model[i].enabled = true;
		else
			model[i].enabled = false;
		i++;
	}
}

static void	ft_error(t_transform *master)
{
	if (master->img)
		mlx_delete_image(master->mlx, master->img);
	if (master->mlx)
		mlx_terminate(master->mlx);
	if (master->m)
		free(master->m);
	if (master)
		free(master);
	free(master->model);
}

void	hook(void *t)
{
}

void	render(t_transform *t)
{
	int	i;

	t = default_transform(t);
	apply_m(t->model, modelm(t->m, t));
	apply_m(t->model, perspectivem(t->m, t));
	clip(t->model);
	apply_m(t->model, scalem(t->m, t));
	i = 0;
	while (t->model[i].w)
	{
		if (t->model[i].enabled == true)
			mlx_put_pixel(t->img, t->model[i].x, t->model[i].y, 0xFFFFFFFF);
		i++;
	}
	mlx_image_to_window(t->mlx, t->img, 0, 0);
	mlx_loop_hook(t->mlx, &hook, t);
	mlx_loop(t->mlx);
	mlx_terminate(t->mlx);
	exit(EXIT_SUCCESS);
}

void	init_img(t_vertex *model)
{
	double		**m;
	t_transform	*t;
	mlx_t		*mlx;
	mlx_image_t	*img;

	m = ft_calloc(sizeof(double), 16);
	t = ft_calloc(sizeof(t_transform), 1);
	mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	t->model = model;
	t->m = m;
	t->mlx = mlx;
	t->img = img;
	if (!m || !t || !mlx || !img)
		ft_error(t);
	render(t);
}
