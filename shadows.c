/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:47:49 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/30 13:52:38 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

double			check_shadows_sphere(t_sphere *current_sp, t_xyzpoint light, \
					t_scene *scene, t_index fig)
{
	double		length;
	double		length_cur;
	t_light		*tmp_l;

	tmp_l = scene->light;
	while (fig.ind_l_n--)
		tmp_l = tmp_l->next;
	while (current_sp)
	{
		if (fig.i_f != 1 || (fig.count - fig.i_f_n) != \
				current_sp->count)
		{
			length = length_vector(vector_mult(light, substruct_vector(\
				tmp_l->center, current_sp->center))) / length_vector(light);
			length_cur = sqrt(pow(length_vector(substruct_vector(tmp_l->center,\
				current_sp->center)), 2) - pow(length, 2));
			if (length <= (current_sp->diametr / 2) && length_vector(light) > \
				length_cur && scalar(light, substruct_vector(tmp_l->center, \
				current_sp->center)) > 0)
				return (1);
		}
		current_sp = current_sp->next;
	}
	return (0);
}

double			check_shadows_plane(t_plane *current_pl, t_xyzpoint light, \
				t_scene *scene, t_index fig)
{
	double		d;
	double		length;
	t_light		*tmp_l;

	tmp_l = scene->light;
	while (fig.ind_l_n--)
		tmp_l = tmp_l->next;
	while (current_pl)
	{
		if (fig.i_f != 2 || (fig.count - fig.i_f_n) != \
			current_pl->count)
		{
			current_pl->orient = normalize_orient(current_pl->center, \
				current_pl->orient, g_scene->camera->center);
			d = -scalar(current_pl->center, current_pl->orient);
			length = -(d + scalar(current_pl->orient, tmp_l->center)) / \
			scalar(current_pl->orient, mult_num_vect(light, -1));
			if (length_vector(light) > length && scalar(normalize_vector(light)\
				, current_pl->orient) < 0 && length > 0)
				return (1);
		}
		current_pl = current_pl->next;
	}
	return (0);
}

double			check_shadows_triangle(t_triangle *current_tr, \
					t_xyzpoint light, t_scene *scene, t_index fig)
{
	double		length;
	t_xyzpoint	antilight;
	t_light		*tmp_l;

	tmp_l = scene->light;
	while (fig.ind_l_n--)
		tmp_l = tmp_l->next;
	antilight = normalize_vector(mult_num_vect(light, -1));
	while (current_tr)
	{
		if (fig.i_f != 3 || (fig.count - fig.i_f_n) != current_tr->count)
		{
			current_tr->normal = normalize_orient(current_tr->angle_one, \
				vector_mult(substruct_vector(current_tr->angle_two, \
				current_tr->angle_one), substruct_vector(current_tr->\
				angle_three, current_tr->angle_one)), g_scene->camera->center);
			length = length_to_pl_point(tmp_l->center, current_tr->normal, \
				current_tr->angle_one, antilight);
			if (check_inside_triangle(tmp_l->center, current_tr, antilight, \
				length) && length > 0 && length < length_vector(light))
				return (1);
		}
		current_tr = current_tr->next;
	}
	return (0);
}

double			check_shadows_square(t_square *current_sq, t_xyzpoint light, \
					t_scene *scene, t_index fig)
{
	double		length;
	t_xyzpoint	antilight;
	t_light		*tmp_l;

	tmp_l = scene->light;
	while (fig.ind_l_n--)
		tmp_l = tmp_l->next;
	antilight = normalize_vector(mult_num_vect(light, -1));
	while (current_sq)
	{
		if (fig.i_f != 4 || (fig.count - fig.i_f_n) != current_sq->count)
		{
			length = length_to_pl_point(tmp_l->center, current_sq->orient, \
				current_sq->center, antilight);
			if (check_inside_square(tmp_l->center, current_sq, \
				normalize_vector(light), length) && length > 0 && length < \
				length_vector(light))
				return (1);
		}
		current_sq = current_sq->next;
	}
	return (0);
}

double			check_shadows_cylin(t_cylin *current_cy, t_xyzpoint light, \
					t_scene *scene, t_index fig)
{
	t_light		*tmp_l;
	double		length;

	tmp_l = scene->light;
	while (fig.ind_l_n--)
		tmp_l = tmp_l->next;
	light = mult_num_vect(light, -1);
	while (current_cy)
	{
		if (fig.i_f != 5 || (fig.count - fig.i_f_n) != \
			current_cy->count)
		{
			current_cy->orient = normalize_orient(current_cy->center, \
				current_cy->orient, scene->camera->center);
			length = check_cylin_wall(current_cy, normalize_vector(light), \
				MAXFLOAT, tmp_l->center);
			if (length < length_vector(light) && length)
				return (1);
		}
		current_cy = current_cy->next;
	}
	return (0);
}
