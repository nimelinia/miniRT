/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:16:11 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/17 02:35:13 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

double		find_k_1_3(t_xyzpoint vect, t_scene *scene)
{
	t_xyzpoint	normal;
	t_xyzpoint	temp_1;
	t_xyzpoint	temp_2;
	double		k;

	normal = normalize_vector(scene->cylin->orient);
	temp_1.x = normal.x * scalar(vect, normal);
	temp_1.y = normal.y * scalar(vect, normal);
	temp_1.z = normal.z * scalar(vect, normal);
	temp_2 = substruct_vector(vect, temp_1);
	k = scalar(temp_2, temp_2);
	return (k);
}

double		find_k_2(t_xyzpoint vect_1, t_xyzpoint vect_2, t_scene *scene)
{
	t_xyzpoint	normal;
	t_xyzpoint	temp_1;
	t_xyzpoint	temp_2;
	t_xyzpoint	temp_3;
	t_xyzpoint	temp_4;

	normal = normalize_vector(scene->cylin->orient);
	temp_1.x = normal.x * scalar(vect_1, normal);
	temp_1.y = normal.y * scalar(vect_1, normal);
	temp_1.z = normal.z * scalar(vect_1, normal);
	temp_2.x = normal.x * scalar(vect_2, normal);
	temp_2.y = normal.y * scalar(vect_2, normal);
	temp_2.z = normal.z * scalar(vect_2, normal);
	temp_3 = substruct_vector(vect_1, temp_1);
	temp_4 = substruct_vector(vect_2, temp_2);
	return (scalar(temp_3, temp_4));
}
