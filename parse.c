#include "include/fdf.h"

int	count_strs(char **lines)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (lines[i])
	{
		count += ft_strlen(lines[i]);
		i++;
	}
	return (count);
}

int	count_vertex(char **lines)
{
	char	**vertex;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (lines[i])
	{
		vertex = ft_split(lines[i], ' ');
		if (!vertex)
			return (-1);
		count += count_strs(vertex);
		i++;
		ft_free_split(vertex);
	}
	return (count);
}

void	fill_array(t_vertex *array, char **lines, int i, int k)
{
	int		j;
	char	**verteces;

	while (lines[i])
	{
		verteces = ft_split(lines[i], ' ');
		if (!verteces)
			return ;
		j = 0;
		while (verteces[j])
		{
			array[k].x = j;
			array[k].y = -1 * ft_atoi(verteces[j]);
			array[k].z = i;
			array[k].w = 1;
			j++;
			k++;
		}
		ft_free_split(verteces);
		i++;
	}
}

t_vertex	*parse(char *map)
{
	int			linecount;
	int			vertexcount;
	char		**lines;
	t_vertex	*array;

	lines = ft_split(map, '\n');
	if (!lines)
		return (0);
	linecount = count_strs(lines);
	vertexcount = count_vertex(lines);
	array = ft_calloc(sizeof(int) * 4, vertexcount + 1);
	if (!array)
	{
		ft_free_split(lines);
		return (0);
	}
	fill_array(array, lines, 0, 0);
	ft_free_split(lines);
	return (array);
}
