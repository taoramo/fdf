#include "include/fdf.h"

int	parsecolor(char *map, t_fdf *t, int i, int k)
{
	i++;
	t->raw[k].color = (ft_hexstr_to_int(&map[i]) << 8) + 0xFF;
	while (map[i] != ' ' && map[i] != '\n')
		i++;
	return (i);
}

void	make_vertex(t_fdf *t, int i, int k, int j)
{
	t->raw[k].y = ft_atoi(&t->map[i]);
	t->raw[k].x = k % t->stride;
	t->raw[k].z = j;
	t->raw[k].w = 1;
}

void	insert_placeholders(t_fdf *t, int *k)
{
	while (*k % t->stride != 0)
	{
		placeholder_vertex(t->raw, *k);
		*k = *k + 1;
	}
}

void	parse2(t_fdf *t)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (t->map[i])
	{
		make_vertex(t, i, k, j);
		while (ft_isdigit(t->map[i]))
			i++;
		if (t->map[i] == ',')
			i = parsecolor(t->map, t, i, k);
		else
			t->raw[k].color = get_rgba(0, 0, 0, 255);
		while (t->map[i] == ' ')
			i++;
		k++;
		if (t->map[i] == '\n')
		{
			insert_placeholders(t, &k);
			j++;
		}
		i++;
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
	parse2(t);
	init_img(t);
}
