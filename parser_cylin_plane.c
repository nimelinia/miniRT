/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylin_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:54:31 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/09 15:22:28 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

int		pars_plane_list(char *line, t_scene *scene)
{
	line = line + 2;
	while (line && *line == ' ')
		line++;
	scene->plane->center = pars_center(&line, scene);
	while (line && *line == ' ')
		line++;
	scene->plane->orient = pars_orient(&line, scene);
	while (line && *line == ' ')
		line++;
	scene->plane->colour = pars_colour(&line, scene);
	if (!scene->mistake)
		return (write(2, "wrong plane\n", 12));
	return (0);
}

int		pars_plane(char *line, t_scene *scene)
{
	static int	count_plane = 0;
	t_plane		*new;

	if (count_plane == 0)
	{
		count_plane = 1;
		scene->plane->count++;
		return (pars_plane_list(line, scene));
	}
	else
	{
		count_plane = 0;
		new = p_init();
		new->next = scene->plane;
		scene->plane = new;
		return (pars_plane(line, scene));
	}
}

int		pars_cylin_list(char *line, t_scene *scene)
{
	line = line + 2;
	while (line && *line == ' ')
		line++;
	scene->cylin->center = pars_center(&line, scene);
	while (line && *line == ' ')
		line++;
	scene->cylin->orient = pars_orient(&line, scene);
	while (line && *line == ' ')
		line++;
	scene->cylin->colour = pars_colour(&line, scene);
	while (line && *line == ' ')
		line++;
	if (!line || !(ft_isdigit(*line)))
		return (write(2, "wrong cylinde1\n", 15));
	scene->cylin->diametr = pars_double(0, &line);
	while (line && *line == ' ')
		line++;
	if (!line || !(ft_isdigit(*line)))
		return (write(2, "wrong cylinde2\n", 15));
	scene->cylin->lenght = pars_double(0, &line);
	if (!scene->mistake)
		return (write(2, "wrong cylinde3\n", 15));
	return (0);
}

int		pars_cylin(char *line, t_scene *scene)
{
	static int	count_cylin = 0;
	t_cylin		*new;

	if (count_cylin == 0)
	{
		count_cylin = 1;
		scene->cylin->count++;
		return (pars_cylin_list(line, scene));
	}
	else
	{
		count_cylin = 0;
		new = cy_init();
		new->next = scene->cylin;
		scene->cylin = new;
		return (pars_cylin(line, scene));
	}
}