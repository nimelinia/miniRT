/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 21:15:42 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/29 17:04:18 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	prerender(t_scene *scene, t_mlx *mlx)
{
	int			x[4];

	(void)scene;
	(void)mlx;
	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	render(&x[0]);
	render(&x[1]);
	render(&x[2]);
	render(&x[3]);
}

void	*render(void *x)
{
	t_mlx		*mlx;
	t_scene		*scene;

	scene = g_scene;
	mlx = &g_mlx;
	render_threads(scene, mlx, *(int*)x);
	return (NULL);
}

void	render_threads(t_scene *scene, t_mlx *mlx, int x)
{
	int			i;
	int			count;

	i = 0;
	count = scene->sphere->count;
	while (count--)
		draw_sphere(scene, mlx, x, i++);
	i = 0;
	count = scene->plane->count;
	while (count--)
		draw_plane(scene, mlx, x, i++);
	i = 0;
	count = scene->triangle->count;
	while (count--)
		draw_triangle(scene, mlx, x, i++);
	i = 0;
	count = scene->square->count;
	while (count--)
		draw_square(scene, mlx, x, i++);
	i = 0;
	count = scene->cylin->count;
	while (count--)
		draw_cylin(scene, mlx, x, i++);
	fill_ambient(scene, mlx, x);
}

void	fill_ambient(t_scene *scene, t_mlx *mlx, int x)
{
	int		y;
	int		colour;

	y = 0;
	while (x < scene->resol.x_size)
	{
		while (y < scene->resol.y_size)
		{
			if (scene->points[x][y] == MAXFLOAT)
			{
				colour = convert_colour_ambi(scene->ambi.colour, \
					scene->ambi.racio);
				my_mlx_pixel_put(mlx, x, y, colour);
			}
			y++;
		}
		x += 4;
		y = 0;
	}
}
