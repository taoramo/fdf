#include "include/fdf.h"

int	count_vertex(char **lines)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (lines[i])
	{
		j = 0;
		count += 1;
		while (lines[i][j])
		{
			if (lines[i][j] == ' ')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

//int	parse_color(int)
//{
	

void	fill_array(t_vertex *array, char **lines, int i, int k)
{
	int		j;
	char	**verteces;
	char	**split;

	while (lines[i])
	{
		verteces = ft_split(lines[i], ' ');
		if (!verteces)
			return ;
		j = 0;
		while (verteces[j])
		{
			split = ft_split(verteces[j], ',');
			if (!split)
			{
				ft_free_split(verteces);
				return ;
			}
			array[k].x = j;
			array[k].y = -1 * ft_atoi(split[0]);
			array[k].z = i;
			array[k].w = 1;
			if (split[1])
				array[k].color = ft_hexstr_to_int(split[1]) << 2 + 255;
			else
				array[k].color = 0x000000FF;
			j++;
			k++;
			ft_free_split(split);
		}
		ft_free_split(verteces);
		i++;
	}
}

t_vertex	*parse(char *map)
{
	int			vertexcount;
	char		**lines;
	t_vertex	*array;

	lines = ft_split(map, '\n');
	if (!lines)
		return (0);
	vertexcount = count_vertex(lines);
	array = ft_calloc(sizeof(t_vertex), vertexcount);
	if (!array)
	{
		ft_free_split(lines);
		return (0);
	}
	fill_array(array, lines, 0, 0);
	ft_free_split(lines);
	return (array);
}
