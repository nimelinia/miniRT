/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_multithread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 21:16:33 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/29 20:38:10 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	prerender(t_scene *scene, t_mlx *mlx)
{
	int			x[4];
	pthread_t	thr_1;
	pthread_t	thr_2;
	pthread_t	thr_3;
	pthread_t	thr_4;

	(void)scene;
	(void)mlx;
	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	pthread_create(&thr_1, NULL, render, &x[0]);
	pthread_create(&thr_2, NULL, render, &x[1]);
	pthread_create(&thr_3, NULL, render, &x[2]);
	pthread_create(&thr_4, NULL, render, &x[3]);
	pthread_join(thr_1, NULL);
	pthread_join(thr_2, NULL);
	pthread_join(thr_3, NULL);
	pthread_join(thr_4, NULL);
}

void	*render(void *x)
{
	t_mlx		*mlx;
	t_scene		*scene;

	scene = g_scene;
	mlx = &g_mlx;
	render_threads(scene, mlx, *(int*)x);
	pthread_exit(NULL);
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
