/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_triangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:58:52 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/19 23:10:10 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

int		pars_triangle_list(char *line, t_scene *scene)
{
	line = line + 2;
	while (line && *line == ' ')
		line++;
	scene->triangle->angle_one = pars_center(&line, scene);
	while (line && *line == ' ')
		line++;
	scene->triangle->angle_two = pars_center(&line, scene);
	while (line && *line == ' ')
		line++;
	scene->triangle->angle_three = pars_center(&line, scene);
	while (line && *line == ' ')
		line++;
	scene->triangle->colour = pars_colour(&line, scene);
	if (!scene->mistake)
		return (write(2, "Error\nwrong triangle\n", 21));
	return (0);
}

int		pars_triangle(char *line, t_scene *scene)
{
	static int	count_triangle = 0;
	t_triangle	*new;

	if (count_triangle == 0)
	{
		count_triangle = 1;
		scene->triangle->count++;
		return (pars_triangle_list(line, scene));
	}
	else
	{
		count_triangle = 0;
		new = t_init();
		new->next = scene->triangle;
		scene->triangle = new;
		return (pars_triangle(line, scene));
	}
}
