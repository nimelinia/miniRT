/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:39:01 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/27 11:17:44 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	draw_plane(t_scene *scene, t_mlx *mlx, int x, int i) // void *mlx_ptr, void *win_ptr)
{
	int		y;
	int		colour;
	// double	t[2];
	t_index		pl;
	t_plane		*tmp_pl;

	y = 0;
	pl.ind_fig = 2;
	pl.ind_fig_n = i;
	pl.count = scene->plane->count;
	tmp_pl = scene->plane;
	while (i--)
		tmp_pl = tmp_pl->next;
	while (x < scene->resol.x_size)
	{
		while (y < scene->resol.y_size)
		{
			if ((pl.t = check_plane(scene, x, y, pl.ind_fig_n)) && pl.t <= scene->points[x][y])
			{
				pl.ind_l_n = 0;
				colour = convert_colour(tmp_pl->colour, \
					find_colour_2(scene, x, y, pl));
				my_mlx_pixel_put(mlx, x, y, colour);
				// mlx_pixel_put(mlx_ptr, win_ptr, x, y, colour);
				scene->points[x][y] = pl.t;
			}
			y++;
		}
		x += 4;
		y = 0;
	}
}

double	check_plane(t_scene *scene, int x, int y, int i)
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
	
	tmp_pl->orient = normalize_orient(tmp_pl->center, tmp_pl->orient, scene->camera->center);
	d = -scalar(tmp_pl->center, tmp_pl->orient);
	// ray = normalize_vector(substruct_vector(canvas, scene->camera->center));
	ray = substruct_vector(canvas, scene->camera->center);
	t = -(d + scalar(tmp_pl->orient, scene->camera->center)) / \
		scalar(tmp_pl->orient, ray);
	if (t >= 1 && t < 6000)
		return (t);
	else
		return (0);
}
// написать функцию, которая делает нормаль противоположной направлению камеры, если перпендикулярно
// то тогда справа налево
// возможно нужно убрать нормализацию вектора
t_xyzpoint	normalize_orient(t_xyzpoint xyz, t_xyzpoint orient, t_xyzpoint camera)
{
	t_xyzpoint	new_orient;

	if (scalar(substruct_vector(xyz, camera), orient) > 0.)
		new_orient = normalize_vector(mult_num_vect(orient, -1.));
	else if (scalar(substruct_vector(xyz, camera), orient) == 0.)
		new_orient = normalize_orient_perp(xyz, orient, camera);
	else
		new_orient = normalize_vector(orient);
	return(new_orient);
}

t_xyzpoint	normalize_orient_perp(t_xyzpoint xyz, t_xyzpoint orient, t_xyzpoint camera)
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