/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:39:01 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/30 13:43:55 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void		draw_plane(t_scene *scene, t_mlx *mlx, int x, int i)
{
	t_index		pl;

	pl.i_f = 2;
	pl.i_f_n = i;
	pl.count = scene->plane->count;
	draw_plane_util(scene, mlx, x, pl);
}

void		draw_plane_util(t_scene *scene, t_mlx *mlx, int x, t_index pl)
{
	int			y;
	int			i;
	t_plane		*tmp_pl;

	i = pl.i_f_n;
	tmp_pl = scene->plane;
	while (i--)
		tmp_pl = tmp_pl->next;
	while (x < scene->resol.x_size)
	{
		y = 0;
		while (y < scene->resol.y_size)
		{
			if ((pl.t = check_plane(scene, x, y, pl.i_f_n)) &&
				pl.t <= scene->points[x][y])
			{
				pl.ind_l_n = 0;
				my_mlx_pixel_put(mlx, x, y, convert_colour(tmp_pl->colour, \
					find_colour_2(scene, x, y, pl)));
				scene->points[x][y] = pl.t;
			}
			y++;
		}
		x += 4;
	}
}

double		check_plane(t_scene *scene, int x, int y, int i)
{
	t_xyzpoint	canvas;
	double		d;
	double		t;
	t_xyzpoint	ray;
	t_plane		*tmp_pl;

	tmp_pl = scene->plane;
	while (i--)
		tmp_pl = tmp_pl->next;
	canvas = find_center_canvas(scene, x, y);
	d = -scalar(tmp_pl->center, tmp_pl->orient);
	ray = substruct_vector(canvas, scene->camera->center);
	t = -(d + scalar(tmp_pl->orient, scene->camera->center)) / \
		scalar(tmp_pl->orient, canvas);
	if (t >= 0.1 && t < 6000)
		return (t);
	else
		return (0);
}

t_xyzpoint	normalize_orient(t_xyzpoint xyz, t_xyzpoint orient, \
			t_xyzpoint camera)
{
	t_xyzpoint	new_orient;

	if (scalar(substruct_vector(xyz, camera), orient) > 0.)
		new_orient = normalize_vector(mult_num_vect(orient, -1.));
	else if (scalar(substruct_vector(xyz, camera), orient) == 0.)
		new_orient = normalize_orient_perp(xyz, orient, camera);
	else
		new_orient = normalize_vector(orient);
	return (new_orient);
}

t_xyzpoint	normalize_orient_perp(t_xyzpoint xyz, t_xyzpoint orient, \
			t_xyzpoint camera)
{
	t_xyzpoint	new_orient;
	t_xyzpoint	vect_plus;
	t_xyzpoint	vect_minus;

	vect_plus = find_point_coordinates(xyz, orient, 1.);
	vect_minus = find_point_coordinates(xyz, orient, -1.);
	if (length_vector(substruct_vector(vect_plus, camera)) > \
		length_vector(substruct_vector(vect_minus, camera)))
		new_orient = normalize_vector(mult_num_vect(orient, -1.));
	else
		new_orient = normalize_vector(orient);
	return (new_orient);
}
