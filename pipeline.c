#include "include/fdf.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

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


void	color(t_transform *t)
{
	int		i;
	int		red;
	int		green;
	int		blue;
	double	ratio;

	t->max_y = find_max_y(t->raw);
	t->min_y = find_min_y(t->raw);
	i = 0;
	while (i < t->msize)
	{
		ratio = 2 * (t->raw[i].y - t->min_y) * (t->max_y - t->min_y);
		if (255 * (1 - ratio) > 0)
			red = 255 * (1 - ratio);
		else
			red = 0;
		if (ratio - 1 > 0)
			blue = 255 * (ratio - 1);
		else
			blue = 0;
		green = 255 - blue - red;
		t->raw[i].color = get_rgba(red, green, blue, 255);
		i++;
	}
}

void	viewport(t_transform *t)
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

void	normalize_and_clip(t_transform *t)
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

static void	ft_error(t_transform *master)
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

void	render_loop(t_transform *t)
{
	mlx_image_t	*img_new;
	int			i;

	ft_memcpy(t->model, t->raw, t->msize * sizeof(t_vertex));
	img_new = mlx_new_image(t->mlx, WIDTH, HEIGHT);
	if (!img_new)
		ft_error(t);
	black_img(img_new);
	apply_m(t->model, modelm(t->m, t));
	apply_m(t->model, perspectivem(t->m, t));
	normalize_and_clip(t);
	viewport(t);
	memset(img_new->pixels, 255, img_new->width
		* img_new->height * sizeof(int32_t));
	i = 0;
	while (i < t->msize)
	{
		if (t->model[i].enabled == true)
			mlx_put_pixel(img_new, round(t->model[i].x),
				round(t->model[i].y), t->model[i].color);
		i++;
	}
	mlx_image_to_window(t->mlx, img_new, 0, 0);
	mlx_delete_image(t->mlx, t->img);
	t->img = img_new;
}

void	hook(void *param)
{
	t_transform	*t;

	t = (t_transform *)param;
	if (mlx_is_key_down(t->mlx, MLX_KEY_LEFT))
		t->a = t->a - 0.1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_RIGHT))
		t->a = t->a + 0.1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_UP))
		t->b = t->b + 0.1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_DOWN))
		t->b = t->b - 0.1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_K))
		t->tz = t->tz + 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_I))
		t->tz = t->tz - 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_J))
		t->tx = t->tx - 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_L))
		t->tx = t->tx + 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_U))
		t->ty = t->ty - 1;
	if (mlx_is_key_down(t->mlx, MLX_KEY_O))
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
	render_loop(t);
}

void	render(t_transform *t)
{
	int	i;

	t = default_transform(t);
	ft_memcpy(t->raw, t->model, t->msize * sizeof(t_vertex));
	apply_m(t->model, modelm(t->m, t));
	apply_m(t->model, perspectivem(t->m, t));
	normalize_and_clip(t);
	viewport(t);
//	black_img(t->img);
	memset(t->img->pixels, 255, t->img->width
		* t->img->height * sizeof(int32_t));
	i = 0;
	while (i < t->msize)
	{
		if (t->model[i].enabled == true)
			mlx_put_pixel(t->img, round(t->model[i].x),
				round(t->model[i].y), t->model[i].color);
		i++;
	}
	mlx_image_to_window(t->mlx, t->img, 0, 0);
	mlx_loop_hook(t->mlx, &hook, t);
	mlx_loop(t->mlx);
	mlx_terminate(t->mlx);
	ft_error(t);
}

void	init_img(t_vertex *model, int count)
{
	double		m[16];
	t_transform	t;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_vertex	*raw;

	raw = ft_calloc(sizeof(t_vertex), count);
	mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	t.model = model;
	t.m = m;
	t.mlx = mlx;
	t.img = img;
	t.msize = count;
	if (!mlx || !img || !raw)
		ft_error(&t);
	t.raw = raw;
	render(&t);
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
