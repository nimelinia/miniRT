/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:46:56 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/26 19:01:07 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	draw_triangle(t_scene *scene, t_mlx *mlx, int x, int i) //void *mlx_ptr, void *win_ptr) //допилить свет и тени
{
	int			y;
	int			colour;
	// double	t[2];
	t_index		tr;
	t_triangle	*tmp_tr;

	y = 0;
	tr.ind_fig = 3;
	tr.ind_fig_n = i;
	tmp_tr = scene->triangle;
	tr.count = scene->triangle->count;
	while (i--)
		tmp_tr = tmp_tr->next;
	while (x < scene->resol.x_size)
	{
		while (y < scene->resol.y_size)
		{
			if ((tr.t = check_triangle(scene, x, y, tr.ind_fig_n)) && tr.t <= scene->points[x][y])
			{
				tr.ind_l_n = 0;
				colour = convert_colour(tmp_tr->colour, \
					find_colour_2(scene, x, y, tr));
				my_mlx_pixel_put(mlx, x, y, colour);
				// mlx_pixel_put(mlx_ptr, win_ptr, x, y, colour);
				scene->points[x][y] = tr.t;
			}
			y++;
		}
		x += 4;
		y = 0;
	}
}

double	check_triangle(t_scene *scene, int x, int y, int i)
{
	t_xyzpoint	canvas;
	double		t;
	t_xyzpoint	ray;
	t_triangle	*tr;

	canvas = find_center_canvas(scene, x, y);
	ray = substruct_vector(canvas, scene->camera->center);
	ray = normalize_vector(ray);
	tr = scene->triangle;
	while (i--)
		tr = tr->next;
	tr->normal = vector_mult(substruct_vector(tr->angle_two, \
		tr->angle_one), substruct_vector(tr->angle_three, tr->angle_one));
	tr->normal = normalize_orient(tr->angle_one, tr->normal, \
		scene->camera->center);
	// t =  (scalar(tr->angle_two, tr->normal) - scalar(tr->normal, \
	// 			scene->camera->center)) / scalar(tr->normal, ray);
	t = length_to_pl_point(scene->camera->center, tr->normal, \
		tr->angle_one, ray);
	if (t >= 1 && t < MAXFLOAT && check_inside_triangle( \
		scene->camera->center, tr, ray, t))
		return(t);
	else
		return (0);
}

int		check_inside_triangle(t_xyzpoint cam, t_triangle *triangle, t_xyzpoint ray, double t)
{
	t_xyzpoint	a;
	t_xyzpoint	b;
	t_xyzpoint	c;
	t_xyzpoint	point;

	a = substruct_vector(triangle->angle_one, \
		triangle->angle_two);
	b = substruct_vector(triangle->angle_two, \
		triangle->angle_three);
	c = substruct_vector(triangle->angle_three, \
		triangle->angle_one);
	// if (scalar (ray, triangle->normal) > 0)
	// 	ray = normalize_vector(ray);
	point = find_point_coordinates(cam, ray, t);
	if (scalar(vector_mult(a, substruct_vector(point, \
		triangle->angle_one)), vector_mult(b, substruct_vector(point, \
		triangle->angle_two))) > 0 && \
		scalar(vector_mult(b, substruct_vector(point, \
		triangle->angle_two)), vector_mult(c, substruct_vector(point, \
		triangle->angle_three))) > 0 && \
		scalar(vector_mult(a, substruct_vector(point, \
		triangle->angle_one)), vector_mult(c, substruct_vector(point, \
		triangle->angle_three))) > 0)
	// if (scalar(ray, vector_mult(a, substruct_vector(point, \
	// 	triangle->angle_one))) >= 0 &&
	// 	scalar(ray, vector_mult(b, substruct_vector(point, \
	// 	triangle->angle_two))) >= 0 &&
	// 	scalar(ray, vector_mult(c, substruct_vector(point, \
	// 	triangle->angle_three))) >= 0)
		return (1);
	else
		return (0);
}