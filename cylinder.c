/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:15:51 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/17 01:52:15 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

// нужно дописать тени и свет

void	draw_cylin(t_scene *scene, void *mlx_ptr, void *win_ptr)
{
	int		x;
	int		y;
	int		colour;
	double	t[2];

	x = 0;
	y = 0;
	t[1] = 5;
	while (x < scene->resol.x_size)
	{
		while (y < scene->resol.y_size)
		{
			if ((t[0] = check_cylin(scene, x, y)) && t[0] <= scene->points[x][y])
			{
				colour = convert_colour_2(scene->cylin->colour, \
					find_colour_2(scene, x, y, t)); // тут пока без света - только рассеянный и без теней
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, colour); //convert_colour(scene->sphere->colour, light));
				scene->points[x][y] = t[0];
			}
			y++;
		}
		x++;
		y = 0;
	}
}

double	check_cylin(t_scene *scene, int x, int y)
{
	t_xyzpoint	canvas;
	double		close_t;
	t_xyzpoint	ray;

	scene->cylin->orient = normalize_orient(scene->cylin->center, scene->cylin->orient, scene->camera->center);
	canvas = find_center_canvas(scene, x, y);
	ray = normalize_vector(substruct_vector(canvas, scene->camera->center));
	close_t = check_cylin_wall(scene, ray, MAXFLOAT, canvas);
	if (close_t == MAXFLOAT || close_t == 0)
		return (0);
	return (close_t);
}

double	check_cylin_wall(t_scene *scene, t_xyzpoint ray, double t, \
	t_xyzpoint canvas)
{
	double		t1;
	double		t2;
	double		t3;
	double		t4;

	t1 = find_t1_cyl(canvas, scene, ray);
	t2 = find_t2_cyl(canvas, scene, ray);
	t3 = find_t3_cyl(canvas, scene, ray);
	t4 = find_t4_cyl(canvas, scene, ray);
	if (t1 >= 1 && t1 < t)
		t = t1;
	if (t2 >= 1 && t2 < t)
		t = t2;
	if (t3 >= 1 && t3 < t)
		t = t3;
	if (t4 >= 1 && t4 < t)
		t = t4;
	if (t == t1 || t == t2)
		scene->cylin->normal = scene->cylin->orient;
	if (t == t3 || t == t4)
		scene->cylin->normal = find_cylin_normal_2(scene->cylin, scene, t, ray);
	if (t == MAXFLOAT)
		return (0);
	return (t);
}

t_xyzpoint	find_cylin_normal_2(t_cylin *cylin, t_scene *scene, double t, t_xyzpoint ray)
{
	t_xyzpoint	point;
	t_xyzpoint	gipot;
	t_xyzpoint	normal;
	double		lenght;

	point = find_point_coordinates(scene->camera->center, ray, t);
	gipot = substruct_vector(point, cylin->center);
	lenght = sqrt(pow(length_vector(gipot), 2) - pow(cylin->diametr / 2,2));
	if (scalar(cylin->orient, substruct_vector(point, cylin->center)) > 0)
		normal = substruct_vector(point, find_point_coordinates(cylin->center, cylin->orient, lenght));
	else if (scalar(cylin->orient, substruct_vector(point, cylin->center)) < 0)
		normal = substruct_vector(point, find_point_coordinates(cylin->center, mult_num_vect(cylin->orient, -1), lenght));
	else
		normal = substruct_vector(point, cylin->center);
	normal = normalize_vector(normal);
	return (normal);
}