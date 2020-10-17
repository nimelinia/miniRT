/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:19:20 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/11 12:36:52 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

void	draw_sphere(t_scene *scene, void *mlx_ptr, void *win_ptr)
{
	int		x;
	int		y;
	int		colour;
	double	t[2];

	x = 0;
	y = 0;
	t[1] = 1;
	while (x < scene->resol.x_size)
	{
		while (y < scene->resol.y_size)
		{
			if ((t[0] = check_sphere(scene, x, y)) && t[0] <= scene->points[x][y])
			{
				colour = convert_colour_2(scene->sphere->colour, find_colour(scene, x, y, t));
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, colour); //convert_colour(scene->sphere->colour, light));
				scene->points[x][y] = t[0];
			}
			y++;
		}
		x++;
		y = 0;
	}
}

double		check_sphere(t_scene *scene, int x, int y)
{
	double		t1;
	double		t2;
	double		close_t;
	t_xyzpoint	canvas;
	int			close_sp;

	canvas = find_center_canvas(scene, x, y); // canvas = normalize_vector(canvas); // не факт, что надо
	close_t = MAXFLOAT;
	close_sp = 0;
	t1 = find_first_t(scene, canvas);
	t2 = find_second_t(scene, canvas);
	if (t1 >= 1 && t1 < close_t)
	{
		close_t = t1;
		close_sp = scene->sphere->count;
	}
	if (t2 >= 1 && t2 < close_t)
	{
		close_t = t2;
		close_sp = scene->sphere->count;
	}
	if (!close_sp)
		return (0);
	else
		return (close_t);
}
