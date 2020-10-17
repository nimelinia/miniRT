/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:33:43 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/09 15:14:43 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

t_resol		r_init(void)
{
	t_resol		resol;
	static int	count = 0;

	resol.x_size = 0;
	resol.y_size = 0;
	resol.count = count++;
	return (resol);
}

t_ambi		a_init(void)
{
	t_ambi		ambi;
	static int	count = 0;

	ambi.racio = 0;
	ambi.colour = init_colour();
	ambi.count = count++;
	return (ambi);
}

t_camera	*c_init(void)
{
	t_camera	*camera;
	static int	count = 0;

	camera = (t_camera*)malloc(sizeof(t_camera));
	camera->center = init_center();
	camera->orient = init_orient();
	camera->fov = 0;
	camera->count = count++;
	camera->next = NULL;
	return (camera);
}

t_light		*l_init(void)
{
	t_light		*light;
	static int	count = 0;

	light = (t_light*)malloc(sizeof(t_light));
	light->center = init_center();
	light->racio = 0;
	light->colour = init_colour();
	light->count = count++;
	light->next = NULL;
	return (light);
}

void		t_init_points(t_scene *scene)
{
	int		x;
	int		y;

	x = scene->resol.x_size;
	y = scene->resol.y_size;
	scene->points = (double**)malloc((x + 1) * sizeof(double*));
	while (x >= 0)
	{
		scene->points[x] = (double*)malloc((y + 1) * sizeof(double));
		while (y >= 0)
		{
			scene->points[x][y] = MAXFLOAT;
			y--;
		}
		y = scene->resol.y_size;
		x--;
	}
}
