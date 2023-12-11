#include "include/fdf.h"

int	get_map_size(char *file)
{
	char	str[100];
	int		fd;
	int		size;
	int		i;

	i = 1;
	size = 0;
	fd = open(file, O_RDONLY);
	while (i)
	{
		i = read(fd, &str, 100);
		size += i;
	}
	close(fd);
	return (size);
}

int	main(int argc, char **argv)
{
	int			fd;
	char		*map;
	t_vertex	*array;
	int			i;

	map = ft_calloc(sizeof(char), get_map_size(argv[1]));
	fd = open(argv[1], O_RDONLY);
	if (!fd || !map)
		return (1);
	read(fd, map, get_map_size(argv[1]));
	ft_printf("%s", map);
	array = parse(map);
	free(map);
	if (!array)
		return (1);
	i = 0;
	while (array[i].w)
	{
		ft_printf("x%i y%i z%i i%i\n", array[i].x, array[i].y, array[i].z, i);
		i++;
	}
	draw_lines(array);
}
