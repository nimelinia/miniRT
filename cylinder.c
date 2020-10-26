/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:15:51 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/26 19:00:12 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

// нужно дописать тени и свет

void	draw_cylin(t_scene *scene, t_mlx *mlx, int x, int i) //void *mlx_ptr, void *win_ptr)
{
	int			y;
	int			colour;
	// double	t[2];
	t_index		cy;
	t_cylin		*tmp_cy;

	
	y = 0;
	cy.ind_fig = 5;
	cy.ind_fig_n = i;
	cy.count = scene->cylin->count;
	tmp_cy = scene->cylin;
	while(i--)
		tmp_cy = tmp_cy->next;
	while (x < scene->resol.x_size)
	{
		while (y < scene->resol.y_size)
		{
			if ((cy.t = check_cylin(scene, x, y, cy.ind_fig_n)) && cy.t <= scene->points[x][y])
			{
				cy.ind_l_n = 0;
				colour = convert_colour(tmp_cy->colour, \
					find_colour_2(scene, x, y, cy)); // тут пока без света - только рассеянный и без теней
				my_mlx_pixel_put(mlx, x, y, colour);
				// mlx_pixel_put(mlx_ptr, win_ptr, x, y, colour); //convert_colour(scene->sphere->colour, light));
				scene->points[x][y] = cy.t;
			}
			y++;
		}
		x += 4;
		y = 0;
	}
}

double	check_cylin(t_scene *scene, int x, int y, int i)
{
	t_xyzpoint	canvas;
	double		close_t;
	t_xyzpoint	ray;
	t_cylin		*cy;

	cy = scene->cylin;
	while(i--)
		cy = cy->next;
	canvas = find_center_canvas(scene, x, y);
	ray = normalize_vector(substruct_vector(canvas, scene->camera->center));
	cy->orient = normalize_orient(cy->center, cy->orient, scene->camera->center);
	close_t = check_cylin_wall(cy, ray, MAXFLOAT, scene->camera->center);
	if (close_t == MAXFLOAT || close_t == 0)
		return (0);
	return (close_t);
}

double	check_cylin_wall(t_cylin *cylin, t_xyzpoint ray, double t, \
	t_xyzpoint start)
{
	double		t1;
	double		t2;
	double		t3;
	double		t4;

	t1 = find_t1_cyl(start, cylin, ray);
	t2 = find_t2_cyl(start, cylin, ray);
	t3 = find_t3_cyl(start, cylin, ray);
	t4 = find_t4_cyl(start, cylin, ray);
	if (t1 >= 1 && t1 < t)
		t = t1;
	if (t2 >= 1 && t2 < t)
		t = t2;
	if (t3 >= 1 && t3 < t)
		t = t3;
	if (t4 >= 1 && t4 < t)
		t = t4;
	if (t == t1 || t == t2)
		cylin->normal = cylin->orient;
	if (t == t3 || t == t4)
		cylin->normal = find_cylin_normal(cylin, start, t, ray);
	if (t == MAXFLOAT)
		return (0);
	return (t);
}

t_xyzpoint	find_cylin_normal(t_cylin *cylin, t_xyzpoint camera, double t, t_xyzpoint ray)
{
	t_xyzpoint	point;
	t_xyzpoint	gipot;
	t_xyzpoint	normal;
	double		lenght;

	point = find_point_coordinates(camera, ray, t);
	gipot = substruct_vector(point, cylin->center);
	lenght = sqrt(pow(length_vector(gipot), 2) - pow(cylin->diametr / 2,2));
	if (scalar(cylin->orient, substruct_vector(point, cylin->center)) > 0)
		normal = substruct_vector(point, find_point_coordinates(cylin->center, cylin->orient, lenght));
	else if (scalar(cylin->orient, substruct_vector(point, cylin->center)) < 0)
		normal = substruct_vector(point, find_point_coordinates(cylin->center, mult_num_vect(cylin->orient, -1), lenght));
	else
		normal = substruct_vector(point, cylin->center);
	normal = normalize_vector(normal);
	return (normal);
}



// double	check_cylin_wall(t_scene *scene, t_xyzpoint ray, double t, \
// 	t_xyzpoint canvas)
// {
// 	double		t1;
// 	double		t2;
// 	double		t3;
// 	double		t4;

// 	t1 = find_t1_cyl(canvas, scene, ray);
// 	t2 = find_t2_cyl(canvas, scene, ray);
// 	t3 = find_t3_cyl(canvas, scene, ray);
// 	t4 = find_t4_cyl(canvas, scene, ray);
// 	if (t1 >= 1 && t1 < t)
// 		t = t1;
// 	if (t2 >= 1 && t2 < t)
// 		t = t2;
// 	if (t3 >= 1 && t3 < t)
// 		t = t3;
// 	if (t4 >= 1 && t4 < t)
// 		t = t4;
// 	if (t == t1 || t == t2)
// 		scene->cylin->normal = scene->cylin->orient;
// 	if (t == t3 || t == t4)
// 		scene->cylin->normal = find_cylin_normal_2(scene->cylin, scene, t, ray);
// 	if (t == MAXFLOAT)
// 		return (0);
// 	return (t);
// }

// t_xyzpoint	find_cylin_normal_2(t_cylin *cylin, t_scene *scene, double t, t_xyzpoint ray)
// {
// 	t_xyzpoint	point;
// 	t_xyzpoint	gipot;
// 	t_xyzpoint	normal;
// 	double		lenght;

// 	point = find_point_coordinates(scene->camera->center, ray, t);
// 	gipot = substruct_vector(point, cylin->center);
// 	lenght = sqrt(pow(length_vector(gipot), 2) - pow(cylin->diametr / 2,2));
// 	if (scalar(cylin->orient, substruct_vector(point, cylin->center)) > 0)
// 		normal = substruct_vector(point, find_point_coordinates(cylin->center, cylin->orient, lenght));
// 	else if (scalar(cylin->orient, substruct_vector(point, cylin->center)) < 0)
// 		normal = substruct_vector(point, find_point_coordinates(cylin->center, mult_num_vect(cylin->orient, -1), lenght));
// 	else
// 		normal = substruct_vector(point, cylin->center);
// 	normal = normalize_vector(normal);
// 	return (normal);
// }