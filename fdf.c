/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:05:09 by toramo            #+#    #+#             */
/*   Updated: 2023/12/18 10:05:11 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (fd < 0)
		return (0);
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
	map = ft_calloc(sizeof(char), get_map_size(argv[1]) + 1);
	if (!map)
		free(map);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	if (!read(fd, map, get_map_size(argv[1])))
		return (1);
	t.map = map;
	close(fd);
	parse(&t);
}
