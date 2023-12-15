#include "include/fdf.h"

void	black_img(mlx_image_t *black)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (j <= HEIGHT)
	{
		while (i <= WIDTH)
			mlx_put_pixel(black, 0x000000FF, j, i++);
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
	while (i < t->msize)
	{
		if (t->model[i].z < 0)
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

static void	ft_error(t_fdf *master)
{
	if (master->mlx)
		mlx_terminate(master->mlx);
	if (master->m)
		free(master->m);
	if (master->model)
		free(master->model);
	if (master->raw)
		free(master->raw);
	if (master)
		free(master);
	free(master->model);
}

void	render_loop(t_fdf *t)
{
	mlx_image_t	*img_new;
	mlx_image_t *temp;

	ft_memcpy(t->model, t->raw, t->msize * sizeof(t_vertex));
	img_new = mlx_new_image(t->mlx, WIDTH, HEIGHT);
	if (!img_new)
		ft_error(t);
	apply_m(t->model, modelm(t->m, t));
	apply_m(t->model, perspectivem(t->m, t));
	normalize_and_clip(t);
	viewport(t);
//	black_img(t->img);
	memset(img_new->pixels, 255, img_new->width
		* img_new->height * sizeof(int32_t));
	temp = t->img;
	t->img = img_new;
	draw_lines(t);
	mlx_image_to_window(t->mlx, t->img, 0, 0);
	mlx_delete_image(t->mlx, temp);
	t->img = img_new;
}

void	render(t_fdf *t)
{
	t = default_fdf(t);
	ft_memcpy(t->model, t->raw, t->msize * sizeof(t_vertex));
	apply_m(t->model, modelm(t->m, t));
	apply_m(t->model, perspectivem(t->m, t));
	normalize_and_clip(t);
	viewport(t);
	black_img(t->img);
	draw_lines(t);
	mlx_image_to_window(t->mlx, t->img, 0, 0);
	mlx_loop_hook(t->mlx, &hook, t);
	mlx_loop(t->mlx);
	mlx_terminate(t->mlx);
	ft_error(t);
}

void	init_img(t_fdf *t)
{
	double		m[16];
	mlx_t		*mlx;
	mlx_image_t	*img;

	t->model = ft_calloc(sizeof(t_vertex), t->msize);
	mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	t->m = m;
	t->mlx = mlx;
	t->img = img;
	if (!mlx || !img)
		ft_error(t);
	render(t);
}
/*
	i = 0;
	while (i < t->msize)
	{
		printf("x%f, y%f, z%f, w%f, enabled = %i\n", t->model[i].x, t->model[i].y, t->model[i].z, t->model[i].w, t->model[i].enabled);
		i++;
	}
	printf("left %f, right %f, top %f, bottom %f, near %f, far %f", t->left, t->right, t->top, t->bottom, t->near, t->far);
	*/
