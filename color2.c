#include "include/fdf.h"

void	color(t_fdf *t)
{
	int		i;
	int		red;
	int		green;
	int		blue;
	double	ratio;

	t->max_y = find_max_y(t->raw);
	t->min_y = find_min_y(t->raw);
	i = 0;
	while (i < t->msize)
	{
		ratio = 2 * (t->raw[i].y - t->min_y) / (t->max_y - t->min_y);
		if (255 * (1 - ratio) > 0)
			red = 255 * (1 - ratio);
		else
			red = 0;
		if (ratio - 1 > 0)
			blue = 255 * (ratio - 1);
		else
			blue = 0;
		green = 255 - blue - red;
		if (t->raw[i].color != 0)
			t->raw[i].color = get_rgba(red, green, blue, 255);
		i++;
	}
}
