/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_colours.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:18:13 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/03 15:32:33 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	change_colours_sphere(t_scene *scene, int keycode)
{
	t_sphere	*new;

	(void)scene;
	new = g_scene->sphere;
	while (g_scene->sphere)
	{
		if (keycode == 15)
			g_scene->sphere->colour.r_colour = \
				g_scene->sphere->colour.r_colour + 80;
		if (keycode == 5)
			g_scene->sphere->colour.g_colour = \
				g_scene->sphere->colour.g_colour + 80;
		if (keycode == 11)
			g_scene->sphere->colour.b_colour = \
				g_scene->sphere->colour.b_colour + 80;
		g_scene->sphere = g_scene->sphere->next;
	}
	g_scene->sphere = new;
}

void	change_colours_plane(t_scene *scene, int keycode)
{
	t_plane	*new;

	(void)scene;
	new = g_scene->plane;
	while (g_scene->plane)
	{
		if (keycode == 15)
			g_scene->plane->colour.r_colour = \
				g_scene->plane->colour.r_colour + 80;
		if (keycode == 5)
			g_scene->plane->colour.g_colour = \
				g_scene->plane->colour.g_colour + 80;
		if (keycode == 11)
			g_scene->plane->colour.b_colour = \
				g_scene->plane->colour.b_colour + 80;
		g_scene->plane = g_scene->plane->next;
	}
	g_scene->plane = new;
}

void	change_colours_triangle(t_scene *scene, int keycode)
{
	t_triangle	*new;

	(void)scene;
	new = g_scene->triangle;
	while (g_scene->triangle)
	{
		if (keycode == 15)
			g_scene->triangle->colour.r_colour = \
				g_scene->triangle->colour.r_colour + 80;
		if (keycode == 5)
			g_scene->triangle->colour.g_colour = \
				g_scene->triangle->colour.g_colour + 80;
		if (keycode == 11)
			g_scene->triangle->colour.b_colour = \
				g_scene->triangle->colour.b_colour + 80;
		g_scene->triangle = g_scene->triangle->next;
	}
	g_scene->triangle = new;
}

void	change_colours_square(t_scene *scene, int keycode)
{
	t_square	*new;

	(void)scene;
	new = g_scene->square;
	while (g_scene->square)
	{
		if (keycode == 15)
			g_scene->square->colour.r_colour = \
				g_scene->square->colour.r_colour + 80;
		if (keycode == 5)
			g_scene->square->colour.g_colour = \
				g_scene->square->colour.g_colour + 80;
		if (keycode == 11)
			g_scene->square->colour.b_colour = \
				g_scene->square->colour.b_colour + 80;
		g_scene->square = g_scene->square->next;
	}
	g_scene->square = new;
}

void	change_colours_cylin(t_scene *scene, int keycode)
{
	t_cylin		*new;

	(void)scene;
	new = g_scene->cylin;
	while (g_scene->cylin)
	{
		if (keycode == 15)
			g_scene->cylin->colour.r_colour = \
				g_scene->cylin->colour.r_colour + 80;
		if (keycode == 5)
			g_scene->cylin->colour.g_colour = \
				g_scene->cylin->colour.g_colour + 80;
		if (keycode == 11)
			g_scene->cylin->colour.b_colour = \
				g_scene->cylin->colour.b_colour + 80;
		g_scene->cylin = g_scene->cylin->next;
	}
	g_scene->cylin = new;
}
