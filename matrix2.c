#include "include/fdf.h"

void	apply_m(t_vertex *model, double **m)
{
	int	i;

	i = 0;
	while (model[i].w)
	{
		mmult(model[i], m);
		i++;
	}
}
