#include "include/fdf.h"

void	clip(t_vertex *model, t_transform *t)
{
	int	i;

	i = 0;
	while (i < t->msize)
	{
		if (!model[i].w)
			model[i].enabled = false;
		else if (model[i].x <= model[i].w && model[i].x >= -1 * model[i].w
			&& model[i].y <= model[i].w && model[i].y >= -1 * model[i].w
			&& model[i].z <= model[i].w && model[i].z >= -1 * model[i].w)
			model[i].enabled = true;
		else
			model[i].enabled = false;
		i++;
	}
}

void	normalize(t_vertex *model, t_transform *t)
{
	int	i;

	i = 0;
	while (i < t->msize)
	{
		if (model[i].enabled == true)
		{
			model[i].x /= model[i].w;
			model[i].y /= model[i].w;
			model[i].z /= model[i].w;
		}
		i++;
	}
}

void	viewport(t_transform *t)
{
	int	i;

	i = 0;
	while (i < t->msize)
	{
		t->model[i].x = WIDTH / 2.0 * t->model[i].x + t->model[i].x + WIDTH / 2.0;
		t->model[i].y = HEIGHT / 2.0 * t->model[i].y + t->model[i].y + HEIGHT / 2.0;
		t->model[i].z = (t->far - t->near) / 2.0 + (t->far + t->near) / 2.0;
		i++;
	}
}
		
void	normalize_and_clip(t_transform *t)
{
	int	i;

	i = 0;
	while (i < t->msize)
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

void	render_loop(t_transform *t)
{
	mlx_image_t	*img_new;
	int			i;

	img_new = mlx_new_image(t->mlx, WIDTH, HEIGHT);
	if (!img_new)
		ft_error(t);
	apply_m(t->model, modelm(t->m, t));
	apply_m(t->model, perspectivem(t->m, t));
	clip(t->model, t);
	normalize(t->model, t);
	apply_m(t->model, scalem(t->m, t));
	memset(img_new->pixels, 255, img_new->width * img_new->height * sizeof(int32_t));
	i = 0;
	while (t->model[i].w)
	{
		if (t->model[i].enabled == true)
			mlx_put_pixel(img_new, t->model[i].x, t->model[i].y, 255);
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
		t->tz = t->tz * 1.05;
	if (mlx_is_key_down(t->mlx, MLX_KEY_I))
		t->tz = t->tz / 1.05;
	if (mlx_is_key_down(t->mlx, MLX_KEY_J))
		t->tx = t->tx / 1.05;
	if (mlx_is_key_down(t->mlx, MLX_KEY_L))
		t->tx = t->tx * 1.05;
	render_loop(t);
}

void	render(t_transform *t)
{
	int	i;

	t = default_transform(t);
	apply_m(t->model, modelm(t->m, t));
	apply_m(t->model, perspectivem(t->m, t));
	normalize_and_clip(t);
	i = 0;
	while (i < t->msize)
	{
		printf("x%f, y%f, z%f, w%f, enabled = %i\n", t->model[i].x, t->model[i].y, t->model[i].z, t->model[i].w, t->model[i].enabled);
		i++;
	}
	printf("left %f, right %f, top %f, bottom %f, near %f, far %f", t->left, t->right, t->top, t->bottom, t->near, t->far);
//	clip(t->model, t);
//	normalize(t->model, t);
	viewport(t);
//	apply_m(t->model, scalem(t->m, t));
	memset(t->img->pixels, 255, t->img->width * t->img->height * sizeof(int32_t));
	fflush(0);
	i = 0;
	while (i < t->msize)
	{
		if (t->model[i].enabled == true && t->model[i].x > 0 && t->model[i].y > 0 && t->model[i].x < WIDTH && t->model[i].y < HEIGHT)
			mlx_put_pixel(t->img, round(t->model[i].x), round(t->model[i].y), 255);
		i++;
	}
	mlx_image_to_window(t->mlx, t->img, 0, 0);
//	mlx_loop_hook(t->mlx, &hook, t);
	mlx_loop(t->mlx);
	mlx_terminate(t->mlx);
	exit(EXIT_SUCCESS);
}

void	init_img(t_vertex *model, int count)
{
	double		m[16];
	t_transform	t;
	mlx_t		*mlx;
	mlx_image_t	*img;

//	m = ft_calloc(sizeof(double), 16);
//	t = ft_calloc(sizeof(t_transform), 1);
	mlx = mlx_init(WIDTH, HEIGHT, "asdf", true);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	t.model = model;
	t.m = m;
	t.mlx = mlx;
	t.img = img;
	t.msize = count;
	if (!mlx || !img)
		ft_error(&t);
	render(&t);
}
