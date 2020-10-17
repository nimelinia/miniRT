/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:16:28 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/17 02:35:10 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

/*
** функции находят расстояния до внешней стороны цилиндра (тубуса), внутренней
** стороны цилиндра (тубуса), окружности, ограничивающей тубус с одной стороны
** и со второй. по точкам тубуса расстояние от центра до точки сравнивается с
** половиной диаганали цилиндра, чтобы ограничить цилиндр по его длине
*/

double	find_t1_cyl(t_xyzpoint canvas, t_scene *scene, t_xyzpoint ray)
{
	double		d;
	t_xyzpoint	cntr;
	double		t;
	double		close_t;
	double		length;

	cntr = find_point_coordinates(scene->cylin->center, \
		normalize_vector(scene->cylin->orient), (scene->cylin->lenght / 2));
	close_t = MAXFLOAT;
	d = -(scalar(cntr, scene->cylin->orient));
	t = -(d + scalar(scene->cylin->orient, scene->camera->center)) / \
		scalar(scene->cylin->orient, ray);
	canvas = find_point_coordinates(scene->camera->center, ray, t);
	length = length_vector(substruct_vector(canvas, cntr));
	if (t >= 1 && t < close_t && (length <= scene->cylin->diametr / 2))
		return (t);
	else
		return (0);
}

double	find_t2_cyl(t_xyzpoint canvas, t_scene *scene, t_xyzpoint ray)
{
	double		d;
	t_xyzpoint	cntr;
	double		t;
	double		close_t;
	double		lenght;
	t_xyzpoint	orient_temp;

	orient_temp = normalize_vector(mult_num_vect(scene->cylin->orient, -1));
	cntr = find_point_coordinates(scene->cylin->center, \
		normalize_vector(orient_temp), scene->cylin->lenght / 2);
	close_t = MAXFLOAT;
	d = -(scalar(cntr, orient_temp));
	t = -(d + scalar(orient_temp, scene->camera->center)) / \
		scalar(orient_temp, ray);
	canvas = find_point_coordinates(scene->camera->center, ray, t);
	lenght = length_vector(substruct_vector(canvas, cntr));
	if (t >= 1 && t < close_t && (lenght <= scene->cylin->diametr / 2))
		close_t = t;
	else
		return (0);
	return (close_t);
}

double	find_t3_cyl(t_xyzpoint canvas, t_scene *scene, t_xyzpoint ray)
{
	t_xyzpoint	cylin_osn;
	t_xyzpoint	k;
	double		discriminant;
	double		t;

	(void)canvas;
	cylin_osn = find_point_coordinates(scene->cylin->center, \
		normalize_vector(scene->cylin->orient), scene->cylin->lenght / 2);
	k.x = find_k_1_3(ray, scene);
	k.y = -2 * find_k_2(substruct_vector(cylin_osn, scene->camera->center), \
		ray, scene);
	k.z = find_k_1_3(substruct_vector(cylin_osn, scene->camera->center), scene) \
		- pow((scene->cylin->diametr) / 2, 2);
	discriminant = k.y * k.y - 4 * k.x * k.z;
	t = (-1 * k.y - sqrt(discriminant)) / (2 * k.x);
	if (discriminant < 0 || \
		length_vector(substruct_vector(find_point_coordinates(\
		scene->camera->center, ray, t), scene->cylin->center)) > sqrt(pow(scene->cylin->lenght \
		/ 2, 2) + pow(scene->cylin->diametr / 2, 2)))
		return (0);
	else
		return (t);
}

double	find_t4_cyl(t_xyzpoint canvas, t_scene *scene, t_xyzpoint ray)
{
	t_xyzpoint	cylin_osn;
	double		k1;
	double		k2;
	double		k3;
	double		discriminant;

	(void)canvas;
	cylin_osn = find_point_coordinates(scene->cylin->center, \
		normalize_vector(scene->cylin->orient), scene->cylin->lenght / 2);
	k1 = find_k_1_3(ray, scene);
	k2 = -2 * find_k_2(substruct_vector(cylin_osn, scene->camera->center), \
		ray, scene);
	k3 = find_k_1_3(substruct_vector(cylin_osn, scene->camera->center), scene) \
		- pow((scene->cylin->diametr) / 2, 2);
	discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0 || \
		length_vector(substruct_vector(find_point_coordinates(\
		scene->camera->center, ray, (-1 * k2 + sqrt(discriminant)) /  \
		(2 * k1)), scene->cylin->center)) > sqrt(pow(scene->cylin->lenght \
		/ 2, 2) + pow(scene->cylin->diametr / 2, 2)))
		return (0);
	else
		return ((-1 * k2 + sqrt(discriminant)) / (2 * k1));
}
