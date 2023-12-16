#include "MLX42/include/MLX42/MLX42.h"
#include "include/fdf.h"

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
	if (master->model)
		free(master->model);
	if (master->raw)
		free(master->raw);
	if (master->map)
		free(master->map);
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

void	render_loop(t_fdf *t)
{
	mlx_image_t	*img_new;
	mlx_image_t	*temp;

	ft_memcpy(t->model, t->raw, t->msize * sizeof(t_vertex));
	img_new = mlx_new_image(t->mlx, WIDTH, HEIGHT);
	if (!img_new)
		ft_error(t);
	apply_m(t->model, modelm(t->m, t));
	apply_m(t->model, perspectivem(t->m, t));
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
	ft_memcpy(t->model, t->raw, t->msize * sizeof(t_vertex));
	apply_m(t->model, modelm(t->m, t));
	apply_m(t->model, perspectivem(t->m, t));
	normalize_and_clip(t);
	viewport(t);
	draw_lines(t);
	mlx_image_to_window(t->mlx, t->img, 0, 0);
	mlx_loop_hook(t->mlx, &hook, t);
	mlx_loop(t->mlx);
	ft_error(t);
}

void	init_img(t_fdf *t)
{
	double		m[16];
	mlx_t		*mlx;
	mlx_image_t	*img;

	t->model = ft_calloc(sizeof(t_vertex), t->msize);
	mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!mlx)
		ft_error(t);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		mlx_terminate(mlx);
		ft_error(t);
	}
	t->m = m;
	t->mlx = mlx;
	t->img = img;
	if (!mlx || !img)
		ft_error(t);
	render(t);
}
