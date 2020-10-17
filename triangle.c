/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:46:56 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/17 23:27:56 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	draw_triangle(t_scene *scene, void *mlx_ptr, void *win_ptr) //допилить свет и тени
{
	int		x;
	int		y;
	int		colour;
	double	t[2];

	x = 0;
	y = 0;
	t[1] = 3;
	while (x < scene->resol.x_size)
	{
		while (y < scene->resol.y_size)
		{
			if ((t[0] = check_triangle(scene, x, y)) && t[0] <= scene->points[x][y])
			{
				colour = convert_colour_2(scene->triangle->colour, \
					find_colour_2(scene, x, y, t)); // тут пока без света - только рассеянный и без теней
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, colour); //convert_colour(scene->sphere->colour, light));
				scene->points[x][y] = t[0];
			}
			y++;
		}
		x++;
		y = 0;
	}
}

double	check_triangle(t_scene *scene, int x, int y)
{
	t_xyzpoint	canvas;
	double		close_t;
	double		t;
	t_xyzpoint	ray;

	canvas = find_center_canvas(scene, x, y);
	close_t = MAXFLOAT;
	scene->triangle->normal = vector_mult(substruct_vector(scene->triangle->angle_two, \
		scene->triangle->angle_one), substruct_vector(scene->triangle->angle_three, scene->triangle->angle_one));
	scene->triangle->normal = normalize_orient(scene->triangle->angle_one, scene->triangle->normal, scene->camera->center);
	ray = substruct_vector(canvas, scene->camera->center);
	ray = normalize_vector(ray);
	t = (scalar(scene->triangle->angle_two, scene->triangle->normal) - scalar(scene->triangle->normal, \
		scene->camera->center)) / scalar(scene->triangle->normal, ray);
	if (t >= 1 && t < close_t && check_inside_triangle(scene->camera->center, scene->triangle, ray, t))
		close_t = t;
	else
		return (0);
	return (close_t); 
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
	// ray = normalize_vector(ray);
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

// int		check_inside_triangle(t_scene *scene, t_xyzpoint ray, double t)
// {
// 	t_xyzpoint	a;
// 	t_xyzpoint	b;
// 	t_xyzpoint	c;
// 	t_xyzpoint	point;

// 	a = substruct_vector(scene->triangle->angle_one, \
// 		scene->triangle->angle_two);
// 	b = substruct_vector(scene->triangle->angle_two, \
// 		scene->triangle->angle_three);
// 	c = substruct_vector(scene->triangle->angle_three, \
// 		scene->triangle->angle_one);
// 	if (scalar (ray, scene->triangle->normal) > 0)
// 		ray = mult_num_vect(ray, -1);
// 	point = find_point_coordinates(scene->camera->center, ray, t);
// 	if (scalar(ray, vector_mult(a, substruct_vector(point, \
// 		scene->triangle->angle_one))) >= 0 &&
// 		scalar(ray, vector_mult(b, substruct_vector(point, \
// 		scene->triangle->angle_two))) >= 0 &&
// 		scalar(ray, vector_mult(c, substruct_vector(point, \
// 		scene->triangle->angle_three))) >= 0)
// 		return (1);
// 	else
// 		return (0);
// }