/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:16:41 by toramo            #+#    #+#             */
/*   Updated: 2023/12/18 10:16:42 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	float				dx;
	float				dy;
	float				y;
	float				x;
	bool				persp;
}	t_fdf;
void		parse(t_fdf *t);
float		find_min_y(t_vertex *array);
float		find_max_y(t_vertex *array);
void		translate(t_vertex *array, int x, int y, int z);
void		scale(t_vertex *array, int x, int y, int z);
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
void		make_fustrum_ortho(double fovy, double aspect, t_fdf *t);
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
int			pixel_is_valid(int x, int y);
void		dda(t_vertex v1, t_vertex v2, t_fdf *t);
float		ft_abs_float(float x);
void		apply_ortho(t_fdf *t);
void		apply_perspective(t_fdf *t);
void		black_img(mlx_image_t *black);
void		viewport(t_fdf *t);
void		normalize_and_clip(t_fdf *t);
void		memset_color(mlx_image_t *img, int rgba);
#endif
