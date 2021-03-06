/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:16:28 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/29 21:01:19 by scopycat         ###   ########.fr       */
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

double	find_t1_cyl(t_xyzpoint start, t_cylin *cylin, t_xyzpoint ray)
{
	t_xyzpoint	cntr;
	double		t;
	double		length;
	t_xyzpoint	point;

	cntr = find_point_coordinates(cylin->center, \
		normalize_vector(cylin->orient), (cylin->lenght / 2));
	t = length_to_pl_point(start, cylin->orient, cntr, ray);
	point = find_point_coordinates(start, ray, t);
	length = length_vector(substruct_vector(point, cntr));
	if (t >= 1 && t < MAXFLOAT && (length <= cylin->diametr / 2))
		return (t);
	else
		return (0);
}

double	find_t2_cyl(t_xyzpoint start, t_cylin *cylin, t_xyzpoint ray)
{
	t_xyzpoint	cntr;
	double		t;
	double		lenght;
	t_xyzpoint	orient_temp;
	t_xyzpoint	point;

	orient_temp = normalize_vector(mult_num_vect(cylin->orient, -1));
	cntr = find_point_coordinates(cylin->center, orient_temp, \
		cylin->lenght / 2);
	t = length_to_pl_point(start, orient_temp, cntr, ray);
	point = find_point_coordinates(start, ray, t);
	lenght = length_vector(substruct_vector(point, cntr));
	if (t >= 1 && t < MAXFLOAT && (lenght <= cylin->diametr / 2))
		return (t);
	else
		return (0);
}

double	find_t3_cyl(t_xyzpoint start, t_cylin *cylin, t_xyzpoint ray)
{
	t_xyzpoint	cylin_osn;
	t_xyzpoint	k;
	double		discriminant;
	double		t;

	cylin_osn = find_point_coordinates(cylin->center, \
		normalize_vector(cylin->orient), cylin->lenght / 2);
	k.x = find_k_1_3(ray, cylin->orient);
	k.y = -2 * find_k_2(substruct_vector(cylin_osn, start), \
		ray, cylin->orient);
	k.z = find_k_1_3(substruct_vector(cylin_osn, start), cylin->orient) \
		- pow((cylin->diametr) / 2, 2);
	discriminant = k.y * k.y - 4 * k.x * k.z;
	t = (-1 * k.y - sqrt(discriminant)) / (2 * k.x);
	if (discriminant < 0 || \
		length_vector(substruct_vector(find_point_coordinates(\
		start, ray, t), cylin->center)) > sqrt(pow(cylin->lenght \
		/ 2, 2) + pow(cylin->diametr / 2, 2)))
		return (0);
	else
		return (t);
}

double	find_t4_cyl(t_xyzpoint start, t_cylin *cylin, t_xyzpoint ray)
{
	t_xyzpoint	cylin_osn;
	double		k1;
	double		k2;
	double		k3;
	double		discriminant;

	cylin_osn = find_point_coordinates(cylin->center, \
		normalize_vector(cylin->orient), cylin->lenght / 2);
	k1 = find_k_1_3(ray, cylin->orient);
	k2 = -2 * find_k_2(substruct_vector(cylin_osn, start), \
		ray, cylin->orient);
	k3 = find_k_1_3(substruct_vector(cylin_osn, start), cylin->orient) \
		- pow((cylin->diametr) / 2, 2);
	discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0 || \
		length_vector(substruct_vector(find_point_coordinates(\
		start, ray, (-1 * k2 + sqrt(discriminant)) /  \
		(2 * k1)), cylin->center)) > sqrt(pow(cylin->lenght \
		/ 2, 2) + pow(cylin->diametr / 2, 2)))
		return (0);
	else
		return ((-1 * k2 + sqrt(discriminant)) / (2 * k1));
}
