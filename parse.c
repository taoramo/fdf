#include "include/fdf.h"

int	parse_color(char *map, t_fdf *t, int i, int k)
{
	i++;
	t->raw[k].color = (ft_hexstr_to_int(&map[i]) << 8) + 0xFF;
	i += 2;
	while (ft_isdigit(map[i]) || (map[i] >= 65 && map[i] <= 70)
		|| (map[i] >= 97 && map[i] <= 102))
		i++;
	return (i);
}

int	make_vertex(t_fdf *t, int i, int k, int j)
{
	t->raw[k].y = -1 * ft_atoi(&t->map[i]);
	t->raw[k].x = k % t->stride;
	t->raw[k].z = j;
	t->raw[k].w = 1;
	return (1);
}

void	insert_placeholders(t_fdf *t, int *k)
{
	if (*k > (t->stride * t->linecount))
	{
		free(t->map);
		free(t->raw);
		exit(1);
	}
	while (*k % t->stride != 0)
	{
		placeholder_vertex(t->raw, *k);
		*k = *k + 1;
	}
}

void	parse2(t_fdf *t, int i, int j, int k)
{
	while (t->map[i])
	{
		while (!ft_isdigit(t->map[i]))
			i++;
		make_vertex(t, i, k, j);
		while (ft_isdigit(t->map[i]) || t->map[i] == '-')
			i++;
		if (t->map[i] == ',')
			i = parse_color(t->map, t, i, k);
		else
			t->raw[k].color = get_rgba(255, 255, 255, 255);
		while (t->map[i] == ' ')
			i++;
		k++;
		if (t->map[i] == '\n')
		{
			insert_placeholders(t, &k);
			j++;
			i++;
		}
	}
	t->msize = k;
}

void	parse(t_fdf *t)
{
	t_vertex	*array;
	int			wpl_max;
	int			linecount;

	wpl_max = wordsperline_max(t->map);
	linecount = count_lines(t->map);
	array = ft_calloc(sizeof(t_vertex), wpl_max * linecount);
	if (!array)
	{
		free(t->map);
		exit(1);
	}
	t->stride = wpl_max;
	t->raw = array;
	t->linecount = linecount;
	parse2(t, 0, 0, 0);
	init_img(t);
}
