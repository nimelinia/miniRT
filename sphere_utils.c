/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:19:34 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/29 20:43:21 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

double		find_first_t(t_scene *scene, t_xyzpoint canvas, int i)
{
	t_xyzpoint		ray;
	t_xyzpoint		k;
	t_sphere		*tmp_sp;
	double			discriminant;

	tmp_sp = scene->sphere;
	while (i--)
		tmp_sp = tmp_sp->next;
	ray = substruct_vector(scene->camera->center, tmp_sp->center);
	k.x = scalar(canvas, canvas);
	k.y = 2 * scalar(ray, canvas);
	k.z = scalar(ray, ray) - pow((tmp_sp->diametr) / 2, 2);
	discriminant = k.y * k.y - 4 * k.x * k.z;
	if (discriminant < 0)
		return (0);
	else
		return ((-1 * k.y + sqrt(discriminant)) / (2 * k.x));
}

double		find_second_t(t_scene *scene, t_xyzpoint canvas, int i)
{
	t_xyzpoint		ray;
	t_xyzpoint		k;
	t_sphere		*tmp_sp;
	double			discriminant;

	tmp_sp = scene->sphere;
	while (i--)
		tmp_sp = tmp_sp->next;
	ray = substruct_vector(scene->camera->center, tmp_sp->center);
	k.x = scalar(canvas, canvas);
	k.y = 2 * scalar(ray, canvas);
	k.z = scalar(ray, ray) - pow(tmp_sp->diametr / 2, 2);
	discriminant = k.y * k.y - 4 * k.x * k.z;
	if (discriminant < 0)
		return (0);
	else
		return ((-1 * k.y - sqrt(discriminant)) / (2 * k.x));
}
