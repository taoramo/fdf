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
# define WIDTH 1280
# define HEIGHT 1080
# define MODEL_SCALE 10

typedef struct s_vertex {
	float	x;
	float	y;
	float	z;
	float	w;
	int		color;
	bool	enabled;
}	t_vertex;
typedef struct s_fdf {
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
	int					msize;
	int					angle;
	float				max_y;
	float				min_y;
	t_vertex			*model;
	t_vertex			*raw;
	double				*m;
	mlx_t				*mlx;
	mlx_image_t			*img;
	int					stride;
	int					linecount;
	char				*map;
	int					dx;
	int					dy;
	int					yi;
	int					xi;
}	t_fdf;
void		parse(t_fdf *t);
int			find_min_x(t_vertex *array);
int			find_min_y(t_vertex *array);
int			find_min_z(t_vertex *array);
int			find_max_x(t_vertex *array);
int			find_max_y(t_vertex *array);
int			find_max_z(t_vertex *array);
void		translate(t_vertex *array, int x, int y, int z);
void		scale(t_vertex *array, int x, int y, int z);
t_vertex	find_vrtx_clsr(t_vertex *array, t_vertex vertex);
void		draw_lines(t_fdf *t);
double		*perspectivem(double *m, t_fdf *t);
double		*orthom(double *m, t_fdf *t);
double		*modelm(double *m, t_fdf *t);
void		mmult(t_vertex *v, double *m);
t_fdf		*default_fdf(t_fdf *t);
t_fdf		*init_fdf(t_fdf *t);
void		init_img(t_fdf *t);
double		*scalem(double *m, t_fdf *t);
void		hook(void *t);
void		apply_m(t_vertex *model, double *m);
int			ft_hexstr_to_int(char *str);
void		make_fustrum(double fovy, double aspect, t_fdf *t);
int			get_rgba(int r, int g, int b, int a);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);
void		placeholder_vertex(t_vertex *array, int k);
int			count_wordsperline(char *str);
int			wordsperline_max(char *str);
int			count_lines(char *map);
void		color(t_fdf *t);
void		render_loop(t_fdf *t);
int			vertex_is_valid(t_vertex v);
void		bres_low(t_vertex va, t_vertex vb, t_fdf *t);
void		bres_high(t_vertex va, t_vertex vb, t_fdf *t);
int			pixel_is_valid(int x, int y);
#endif
