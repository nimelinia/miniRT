/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:15:57 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/30 12:28:00 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	free_triangle(t_scene *scene)
{
	t_triangle	*new;

	new = scene->triangle;
	while (new)
	{
		scene->triangle = scene->triangle->next;
		free(new);
		new = scene->triangle;
	}
}

void	free_square(t_scene *scene)
{
	t_square	*new;

	new = scene->square;
	while (new)
	{
		scene->square = scene->square->next;
		free(new);
		new = scene->square;
	}
}

void	free_cylin(t_scene *scene)
{
	t_cylin	*new;

	new = scene->cylin;
	while (new)
	{
		scene->cylin = scene->cylin->next;
		free(new);
		new = scene->cylin;
	}
}

void	free_points(t_scene *scene)
{
	int		x;

	x = scene->resol.x_size;
	while (x >= 0)
	{
		free(scene->points[x]);
		x--;
	}
	free(scene->points);
}
