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
		while (str[i] == ' ')
			i++;
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
	while (map[i])
	{
		if (map[i] == '\n')
			count ++;
		i++;
	}
	return (count);
}
