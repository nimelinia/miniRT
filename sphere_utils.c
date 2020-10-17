/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:19:34 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/09 15:05:32 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

double		find_first_t(t_scene *scene, t_xyzpoint canvas)
{
	t_xyzpoint	ray;
	double		k1;
	double		k2;
	double		k3;
	double		discriminant;

	ray = substruct_vector(scene->camera->center, scene->sphere->center);
	k1 = scalar(canvas, canvas);
	k2 = 2 * scalar(ray, canvas);
	k3 = scalar(ray, ray) - pow((scene->sphere->diametr) / 2, 2);
	discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
		return (0);
	else
		return ((-1 * k2 + sqrt(discriminant)) / (2 * k1));
}

double		find_second_t(t_scene *scene, t_xyzpoint canvas)
{
	t_xyzpoint	ray;
	double		k1;
	double		k2;
	double		k3;
	double		discriminant;

	ray = substruct_vector(scene->camera->center, scene->sphere->center);
	k1 = scalar(canvas, canvas);
	k2 = 2 * scalar(ray, canvas);
	k3 = scalar(ray, ray) - pow(scene->sphere->diametr / 2, 2);
	discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
		return (0);
	else
		return ((-1 * k2 - sqrt(discriminant)) / (2 * k1));
}
