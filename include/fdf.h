#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"
# include <limits.h>
# include "../MLX42/include/MLX42/MLX42.h"
# define WIDTH 720
# define HEIGHT 480
# define MODEL_SCALE 100

typedef struct s_vertex {
	float	x;
	float	y;
	float	z;
	float	w;
	bool	enabled;
}	t_vertex;
typedef struct s_transform {
	float				tx;
	float				ty;
	float				tz;
	float				a;
	float				b;
	float				c;
	float				top;
	float				bottom;
	float				left;
	float				right;
	float				near;
	float				far;
	t_vertex			*model;
	double				*m;
	mlx_t				*mlx;
	mlx_image_t			*img;
	int					msize;
}	t_transform;
t_vertex	*parse(char *map);
int			find_min_x(t_vertex *array);
int			find_min_y(t_vertex *array);
int			find_min_z(t_vertex *array);
int			find_max_x(t_vertex *array);
int			find_max_y(t_vertex *array);
int			find_max_z(t_vertex *array);
void		translate(t_vertex *array, int x, int y, int z);
bool		vertex_exists_xz(t_vertex *array, int x, int z);
void		scale(t_vertex *array, int x, int y, int z);
t_vertex	find_vrtx_clsr(t_vertex *array, t_vertex vertex);
void		draw_lines(t_vertex *array);
double		*perspectivem(double *m, t_transform *t);
double		*orthom(double *m, t_transform *t);
double		*modelm(double *m, t_transform *t);
void		mmult(t_vertex *v, double *m);
t_transform	*default_transform(t_transform *t);
t_transform	*init_transform(t_transform *t);
void		init_img(t_vertex *model, int count);
double		*scalem(double *m, t_transform *t);
void		hook(void *t);
void		apply_m(t_vertex *model, double *m);
#endif
