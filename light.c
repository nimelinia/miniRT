/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:32:02 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/30 13:46:22 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

double		check_light(t_scene *scene, int x, int y, t_index sp)
{
	t_xyzpoint	point;
	t_xyzpoint	normal;
	double		res;
	int			i;
	t_light		*tmp_l;

	tmp_l = scene->light;
	i = sp.ind_l_n;
	while (i--)
		tmp_l = tmp_l->next;
	res = 0.0;
	point = find_point_coordinates(scene->camera->center, \
		find_center_canvas(scene, x, y), sp.t);
	normal = normalize_vector(substruct_vector(point, find_figure_center(\
		scene, sp, find_center_canvas(scene, x, y))));
	if (scalar(normal, normalize_vector(substruct_vector(tmp_l->center, \
			point))) > 0)
		res = (tmp_l->racio * scalar(normal, normalize_vector(\
			substruct_vector(tmp_l->center, point))));
	if (check_shadows_all(substruct_vector(tmp_l->center, point), scene, sp))
		res = 0.0;
	return (res);
}

double		check_light_2(t_scene *scene, int x, int y, t_index fig)
{
	t_xyzpoint	point;
	t_xyzpoint	figure_normal;
	double		res;
	int			i;
	t_light		*tmp_l;

	tmp_l = scene->light;
	i = fig.ind_l_n;
	while (i--)
		tmp_l = tmp_l->next;
	res = 0.0;
	figure_normal = find_figure_center(scene, fig, \
		find_center_canvas(scene, x, y));
	point = find_point_coordinates(scene->camera->center, \
		find_center_canvas(scene, x, y), fig.t);
	if (scalar(figure_normal, normalize_vector(substruct_vector(tmp_l->center,\
			point))) > 0)
		res = (tmp_l->racio * scalar(figure_normal, normalize_vector(\
			substruct_vector(tmp_l->center, point))));
	if (check_shadows_all(substruct_vector(tmp_l->center, point), scene, fig))
		res = 0.0;
	return (res);
}

t_xyzpoint	find_figure_center(t_scene *scene, t_index fig, t_xyzpoint canvas)
{
	t_xyzpoint	point;

	point.x = 0;
	point.y = 0;
	point.z = 0;
	if (fig.i_f == 1)
		return (find_sphere_point(scene, fig));
	else if (fig.i_f == 2)
		return (find_plane_point(scene, fig));
	else if (fig.i_f == 3)
		return (find_triangle_point(scene, fig));
	else if (fig.i_f == 4)
		return (find_square_point(scene, fig));
	else if (fig.i_f == 5)
		return (find_cylin_point(scene, fig, canvas));
	else
		return (point);
}

double		check_shadows_all(t_xyzpoint light, t_scene *scene, t_index fig)
{
	t_sphere	*current_sp;
	t_plane		*current_pl;
	t_triangle	*current_tr;
	t_square	*current_sq;
	t_cylin		*current_cy;

	current_sp = scene->sphere;
	current_pl = scene->plane;
	current_tr = scene->triangle;
	current_sq = scene->square;
	current_cy = scene->cylin;
	if (check_shadows_sphere(current_sp, light, scene, fig))
		return (1);
	if (check_shadows_plane(current_pl, light, scene, fig))
		return (1);
	if (check_shadows_triangle(current_tr, light, scene, fig))
		return (1);
	if (check_shadows_square(current_sq, light, scene, fig))
		return (1);
	if (check_shadows_cylin(current_cy, light, scene, fig))
		return (1);
	else
		return (0);
}
