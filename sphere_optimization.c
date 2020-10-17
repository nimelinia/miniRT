/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_optimization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 12:02:34 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/11 12:31:46 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

int     find_min_x_sp(t_scene *scene)
{
    int     x;
    double		weight;

	weight = find_weight_screen(scene);
    x = ((scene->sphere->center.x - scene->sphere->diametr / 2 + 0.5) * scene->resol.x_size) / weight;
    return (x - 2); 
}

int     find_max_x_sp(t_scene *scene)
{
    int     x;
    double		weight;

	weight = find_weight_screen(scene);
    x = ((scene->sphere->center.x + scene->sphere->diametr / 2 + 0.5) * scene->resol.x_size) / weight;
    return (x + 2); 
}

int     find_min_y_sp(t_scene *scene)
{
    int     y;
    double		weight;
	double		hight;

	weight = find_weight_screen(scene);
	hight = weight * scene->resol.y_size / scene->resol.x_size;
    y = ((scene->sphere->center.y - scene->sphere->diametr / 2 + 0.5) * scene->resol.y_size) / hight;
    return (y - 2); 
}

int     find_max_y_sp(t_scene *scene)
{
    int     y;
    double		weight;
	double		hight;

	weight = find_weight_screen(scene);
	hight = weight * scene->resol.y_size / scene->resol.x_size;
    y = ((scene->sphere->center.y + scene->sphere->diametr / 2 + 0.5) * scene->resol.y_size) / hight;
    return (y + 2); 
}