/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_figure_point.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:44:26 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/26 18:45:47 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

t_xyzpoint		find_sphere_point(t_scene *scene, t_index fig)
{
	int			i;
	t_sphere	*tmp_sp;
	
	i = fig.ind_fig_n;
	tmp_sp = scene->sphere;
	while (i--)
		tmp_sp = tmp_sp->next;
	return (tmp_sp->center);
}

t_xyzpoint		find_plane_point(t_scene *scene, t_index fig)
{
	int			i;
	t_plane		*tmp_pl;
	
	i = fig.ind_fig_n;
	tmp_pl = scene->plane;
	while (i--)
		tmp_pl = tmp_pl->next;
	return (normalize_orient(tmp_pl->center, tmp_pl->orient, scene->camera->center));
}

t_xyzpoint		find_triangle_point(t_scene *scene, t_index fig)
{
	int				i;
	t_triangle		*tmp_tr;
	
	i = fig.ind_fig_n;
	tmp_tr = scene->triangle;
	while (i--)
		tmp_tr = tmp_tr->next;
	return (normalize_orient(tmp_tr->angle_one, vector_mult(substruct_vector(tmp_tr->angle_two, \
			tmp_tr->angle_one), substruct_vector(tmp_tr->angle_three, tmp_tr->angle_one)), 
			scene->camera->center));
}

t_xyzpoint		find_square_point(t_scene *scene, t_index fig)
{
	int			i;
	t_square	*tmp_sq;
	
	i = fig.ind_fig_n;
	tmp_sq = scene->square;
	while (i--)
		tmp_sq = tmp_sq->next;
	return (normalize_orient(tmp_sq->center, tmp_sq->orient, scene->camera->center));
}

t_xyzpoint		find_cylin_point(t_scene *scene, t_index fig, t_xyzpoint canvas)
{
	int			i;
	t_cylin		*tmp_cy;
	t_xyzpoint	point;
	
	i = fig.ind_fig_n;
	tmp_cy = scene->cylin;
	while (i--)
		tmp_cy = tmp_cy->next;
	if (fig.t == check_cylin_wall(tmp_cy, normalize_vector(substruct_vector(canvas, scene->camera->center)), MAXFLOAT, scene->camera->center))
		point = tmp_cy->normal;
	else
		point = tmp_cy->orient;
	return (point);
}