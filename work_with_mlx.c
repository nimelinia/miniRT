/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 21:14:12 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/03 15:24:18 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

void	start_work(t_scene *scene)
{
	g_mlx = init_mlx();
	g_mlx.m_ptr = mlx_init();
	if (scene->save == 0)
		g_mlx.w_ptr = mlx_new_window(g_mlx.m_ptr, scene->resol.x_size, \
		scene->resol.y_size, "miniRT");
	check_resol(scene);
	g_mlx.img = mlx_new_image(g_mlx.m_ptr, scene->resol.x_size, \
		scene->resol.y_size);
	g_mlx.addr = mlx_get_data_addr(g_mlx.img, &g_mlx.bpp, \
		&g_mlx.length, &g_mlx.end);
	g_scene = scene;
	g_camera = scene->camera;
	g_ox = g_scene->camera->ox;
	g_oy = g_scene->camera->oy;
	prerender(scene, &g_mlx);
	if (g_mlx.w_ptr)
	{
		mlx_put_image_to_window(g_mlx.m_ptr, g_mlx.w_ptr, g_mlx.img, 0, 0);
		mlx_mouse_hook(g_mlx.w_ptr, mouse_pressed, scene);
		mlx_hook(g_mlx.w_ptr, 17, 1L << 17, free_struct, scene);
		mlx_hook(g_mlx.w_ptr, 2, 1L << 0, key_pressed, scene);
	}
	else if (scene->save)
		put_image_bmp(scene);
	mlx_loop(g_mlx.m_ptr);
}

void	check_resol(t_scene *scene)
{
	int		size_x;
	int		size_y;

	mlx_get_screen_size(g_mlx.m_ptr, &size_x, &size_y);
	if (scene->resol.x_size > size_x)
		scene->resol.x_size = size_x;
	if (scene->resol.y_size > size_y)
		scene->resol.y_size = size_y;
}

int		key_pressed(int keycode, t_scene *scene)
{
	if (keycode == 37)
		rotate_cam(scene);
	if (keycode == 15 || keycode == 5 || keycode == 11)
		change_colours(scene, keycode);
	if (keycode == 53)
		free_struct(scene);
	if (keycode == 8)
	{
		if (g_scene->camera->next)
			g_scene->camera = g_scene->camera->next;
		else if (g_scene->camera == g_camera)
			return (0);
		else
			g_scene->camera = g_camera;
		g_ox = g_scene->camera->ox;
		redraw_pic(scene);
	}
	return (0);
}

void	reinit_points(t_scene *scene)
{
	int		x;
	int		y;

	x = scene->resol.x_size;
	y = scene->resol.y_size;
	while (x >= 0)
	{
		while (y >= 0)
		{
			scene->points[x][y] = MAXFLOAT;
			y--;
		}
		y = scene->resol.y_size;
		x--;
	}
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int colour)
{
	int		offset;

	offset = (y * mlx->length + x * (mlx->bpp / 8));
	*(unsigned int*)(mlx->addr + offset) = colour;
}
