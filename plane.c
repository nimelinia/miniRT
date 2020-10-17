/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:39:01 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/17 20:28:24 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	draw_plane(t_scene *scene, void *mlx_ptr, void *win_ptr)
{
	int		x;
	int		y;
	int		colour;
	double	t[2];

	x = 0;
	y = 0;
	t[1] = 2;
	while (x < scene->resol.x_size)
	{
		while (y < scene->resol.y_size)
		{
			if ((t[0] = check_plane(scene, x, y)) && t[0] <= scene->points[x][y])
			{
				colour = convert_colour_2(scene->plane->colour, \
					find_colour_2(scene, x, y, t));
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, colour);
				scene->points[x][y] = t[0];
			}
			y++;
		}
		x++;
		y = 0;
	}
}

double	check_plane(t_scene *scene, int x, int y)
{
	t_xyzpoint	canvas;
	double		close_t;
	double		d;
	double		t;
	t_xyzpoint	ray;

	canvas = find_center_canvas(scene, x, y);
	close_t = 6000;
	
	scene->plane->orient = normalize_orient(scene->plane->center, scene->plane->orient, scene->camera->center);
	d = -scalar(scene->plane->center, scene->plane->orient);
	// ray = normalize_vector(substruct_vector(canvas, scene->camera->center));
	ray = substruct_vector(canvas, scene->camera->center);
	t = -(d + scalar(scene->plane->orient, scene->camera->center)) / \
		scalar(scene->plane->orient, ray);
	if (t >= 1 && t < close_t)
		close_t = t;
	else
		return (0);
	return (close_t);
}
// написать функцию, которая делает нормаль противоположной направлению камеры, если перпендикулярно
// то тогда справа налево
// возможно нужно убрать нормализацию вектора
t_xyzpoint	normalize_orient(t_xyzpoint xyz, t_xyzpoint orient, t_xyzpoint camera)
{
	t_xyzpoint	new_orient;

	if (scalar(substruct_vector(xyz, camera), orient) > 0)
		new_orient = normalize_vector(mult_num_vect(orient, -1));
	else if (scalar(substruct_vector(xyz, camera), orient) == 0)
		new_orient = normalize_orient_perp(xyz, orient, camera);
	else
		new_orient = normalize_vector(orient);
	return(new_orient);
}

t_xyzpoint	normalize_orient_perp(t_xyzpoint xyz, t_xyzpoint orient, t_xyzpoint camera)
{
	t_xyzpoint	new_orient;
	t_xyzpoint	vect_plus;
	t_xyzpoint	vect_minus;

	vect_plus = find_point_coordinates(xyz, orient, 1);
	vect_minus = find_point_coordinates(xyz, orient, -1);
	if (length_vector(substruct_vector(vect_plus, camera)) > \
		length_vector(substruct_vector(vect_minus, camera)))
		new_orient = normalize_vector(mult_num_vect(orient, -1));
	else
		new_orient = normalize_vector(orient);	
	return (new_orient);
}