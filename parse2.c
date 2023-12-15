#include "include/fdf.h"

int	count_wordsperline(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (str[0] != 0 && str[0] != '\n')
		count++;
	while (str[i] != '\n')
	{
		if (str[i] == ' ')
			count++;
		i++;
	}
	return (count);
}

int	wordsperline_max(char *map)
{
	int	i;
	int	maxwpl;

	i = 0;
	maxwpl = 0;
	while (map[i])
	{
		if (count_wordsperline(&map[i]) > maxwpl)
			maxwpl = count_wordsperline(&map[i]);
		while (map[i] != '\n' && map[i] != 0)
			i++;
		if (map[i] == '\n')
			i++;
	}
	return (maxwpl);
}

int	count_lines(char *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (map[0] != 0)
		count++;
	while (map[i])
	{
		if (map[i] == '\n')
			count ++;
		i++;
	}
	return (count);
}

void	parse2(char *map, t_transform *t)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
	}
}

void	parse(char *map, t_transform *t)
{
	int			i;
	t_vertex	*array;
	int			wpl_max;
	int			linecount;

	wpl_max = wordsperline_max(map);
	linecount = count_lines(map);
	array = ft_calloc(sizeof(t_vertex), wpl_max * linecount);
	if (!array)
	{
		free(map);
		exit(1);
	}
	t->stride = wpl_max;
	t->raw = array;
	parse2(array, map, t);
}
