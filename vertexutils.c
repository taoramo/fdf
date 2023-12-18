/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertexutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:06:44 by toramo            #+#    #+#             */
/*   Updated: 2023/12/18 10:06:45 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

float	find_min_y(t_vertex *array)
{
	int		i;
	float	smallest;

	i = 0;
	smallest = 1.0 * INT_MAX;
	while (array[i].w)
	{
		if (array[i].y < smallest)
			smallest = array[i].y;
		i++;
	}
	return (smallest);
}

float	find_max_y(t_vertex *array)
{
	int		i;
	float	biggest;

	i = 0;
	biggest = 1.0 * INT_MIN;
	while (array[i].w)
	{
		if (array[i].y > biggest)
			biggest = array[i].y;
		i++;
	}
	return (biggest);
}

void	translate(t_vertex *array, int x, int y, int z)
{
	int	i;

	i = 0;
	while (array[i].w)
	{
		array[i].x += x;
		array[i].y += y;
		array[i].z += z;
		i++;
	}
}
