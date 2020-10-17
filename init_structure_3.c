/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:33:57 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/15 20:31:55 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

t_sphere	*sp_init(void)
{
	t_sphere	*sphere;
	static int	count = 0;

	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	sphere->center = init_center();
	sphere->diametr = 0;
	sphere->colour = init_colour();
	sphere->count = count++;
	sphere->next = NULL;
	return (sphere);
}

t_plane		*p_init(void)
{
	t_plane		*plane;
	static int	count = 0;

	plane = (t_plane*)malloc(sizeof(t_plane));
	plane->center = init_center();
	plane->orient = init_orient();
	plane->colour = init_colour();
	plane->count = count++;
	plane->next = NULL;
	return (plane);
}

t_square	*sq_init(void)
{
	t_square	*square;
	static int	count = 0;

	square = (t_square*)malloc(sizeof(t_square));
	square->center = init_center();
	square->orient = init_orient();
	square->lenght = 0;
	square->colour = init_colour();
	square->count = count++;
	square->next = NULL;
	return (square);
}

t_cylin		*cy_init(void)
{
	t_cylin		*cylin;
	static int	count = 0;

	cylin = (t_cylin*)malloc(sizeof(t_cylin));
	cylin->center = init_center();
	cylin->orient = init_orient();
	cylin->normal = init_orient();
	cylin->diametr = 0;
	cylin->lenght = 0;
	cylin->colour = init_colour();
	cylin->count = count++;
	cylin->next = NULL;
	return (cylin);
}

t_triangle	*t_init(void)
{
	t_triangle	*triangle;
	static int	count = 0;

	triangle = (t_triangle*)malloc(sizeof(t_triangle));
	triangle->angle_one = init_center();
	triangle->angle_two = init_center();
	triangle->angle_three = init_center();
	triangle->colour = init_colour();
	triangle->normal = init_center();
	triangle->count = count++;
	triangle->next = NULL;
	return (triangle);
}
