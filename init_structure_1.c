/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:33:19 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/21 21:28:14 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

void		init_scene(t_scene *scene)
{
	scene->resol = r_init();
	scene->ambi = a_init();
	scene->camera = c_init();
	scene->light = l_init();
	scene->sphere = sp_init();
	scene->plane = p_init();
	scene->square = sq_init();
	scene->cylin = cy_init();
	scene->triangle = t_init();
	scene->mistake = 1;
}

t_mlx		init_mlx(void)
{
	// t_mlx	*mlx;
	t_mlx	mlx;
	// static int	count = 0;

	// mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx.m_ptr = NULL;
	mlx.w_ptr = NULL;
	mlx.img = NULL;
	mlx.addr = NULL;
	mlx.bpp = 0;
	mlx.length = 0;
	mlx.end = 0;
	// mlx->count = count++;
	// mlx->next = NULL;
	return (mlx);
	
}
t_xyzpoint	init_center(void)
{
	t_xyzpoint center;

	center.x = 0;
	center.y = 0;
	center.z = 0;
	return (center);
}

t_colour	init_colour(void)
{
	t_colour colour;

	colour.r_colour = 0;
	colour.g_colour = 0;
	colour.b_colour = 0;
	return (colour);
}

t_xyzpoint	init_orient(void)
{
	t_xyzpoint orient;

	orient.x = 0;
	orient.y = 0;
	orient.z = 0;
	return (orient);
}
