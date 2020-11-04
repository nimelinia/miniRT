/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formules_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:46:24 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/30 12:51:35 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

t_xyzpoint	find_center_canvas(t_scene *scene, int x, int y)
{
	t_xyzpoint	coord_x;
	t_xyzpoint	coord_y;
	double		weight;
	double		hight;
	double		d;

	weight = find_weight_screen(scene);
	hight = weight * (double)scene->resol.y_size / (double)scene->resol.x_size;
	d = weight * (1. - 2. * (double)x / (double)scene->resol.x_size);
	coord_x = mult_num_vect(scene->camera->ox, d);
	d = hight * (1. - 2. * (double)y / (double)scene->resol.y_size);
	coord_y = mult_num_vect(scene->camera->oy, d);
	return (sum_vect(sum_vect(coord_x, coord_y), scene->camera->orient));
}

double		find_weight_screen(t_scene *scene)
{
	double	b;

	b = tan(scene->camera->fov * M_PI / 360.);
	return (b);
}

t_xyzpoint	find_point_coordinates(t_xyzpoint cntr, t_xyzpoint orient, double s)
{
	t_xyzpoint	result;

	result.x = cntr.x + orient.x * s;
	result.y = cntr.y + orient.y * s;
	result.z = cntr.z + orient.z * s;
	return (result);
}

t_xyzpoint	mult_point_matrix(t_xyzpoint point, t_matrix matrix)
{
	t_xyzpoint	result;

	result.x = matrix.str_1.x * point.x + matrix.str_1.y * point.y \
		+ matrix.str_1.z * point.z;
	result.y = matrix.str_2.x * point.x + matrix.str_2.y * point.y \
		+ matrix.str_2.z * point.z;
	result.z = matrix.str_3.x * point.x + matrix.str_3.y * point.y \
		+ matrix.str_3.z * point.z;
	return (result);
}

double		length_to_pl_point(t_xyzpoint start, t_xyzpoint normal, \
			t_xyzpoint pl_point, t_xyzpoint vect)
{
	double	d;
	double	lenght;

	d = -scalar(pl_point, normal);
	lenght = -(d + scalar(normal, start)) / scalar(normal, vect);
	return (lenght);
}
