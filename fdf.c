#include "include/fdf.h"

int	get_map_size(char *file)
{
	char	str[2000];
	int		fd;
	int		size;
	int		i;

	i = 1;
	size = 0;
	fd = open(file, O_RDONLY);
	while (i)
	{
		i = read(fd, &str, 2000);
		size += i;
	}
	close(fd);
	return (size);
}

int	main(int argc, char **argv)
{
	int			fd;
	char		*map;
	t_fdf		t;

	if (argc != 2)
		return (1);
	map = ft_calloc(sizeof(char), get_map_size(argv[1]));
	fd = open(argv[1], O_RDONLY);
	if (!fd || !map)
		return (1);
	read(fd, map, get_map_size(argv[1]));
	t.map = map;
	close(fd);
	parse(&t);
}
