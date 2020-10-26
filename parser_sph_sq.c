/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sph_sq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:56:58 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/19 23:09:54 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

int		pars_square_list(char *line, t_scene *scene)
{
	line = line + 2;
	while (line && *line == ' ')
		line++;
	scene->square->center = pars_center(&line, scene);
	while (line && *line == ' ')
		line++;
	scene->square->orient = pars_orient(&line, scene);
	while (line && *line == ' ')
		line++;
	if (!line || !(ft_isdigit(*line)))
		return (write(2, "Error\nwrong square\n", 19));
	scene->square->lenght = pars_double(0, &line);
	while (line && *line == ' ')
		line++;
	scene->square->colour = pars_colour(&line, scene);
	if (!scene->mistake)
		return (write(2, "Error\nwrong square\n", 19));
	return (0);
}

int		pars_square(char *line, t_scene *scene)
{
	static int	count_square = 0;
	t_square	*new;

	if (count_square == 0)
	{
		count_square = 1;
		scene->square->count++;
		return (pars_square_list(line, scene));
	}
	else
	{
		count_square = 0;
		new = sq_init();
		new->next = scene->square;
		scene->square = new;
		return (pars_square(line, scene));
	}
}

int		pars_sphere_list(char *line, t_scene *scene)
{
	line = line + 2;
	while (line && *line == ' ')
		line++;
	scene->sphere->center = pars_center(&line, scene);
	while (line && *line == ' ')
		line++;
	if (!line || !(ft_isdigit(*line)))
		return (write(2, "Error\nwrong sphere\n", 19));
	scene->sphere->diametr = pars_double(0, &line);
	while (line && *line == ' ')
		line++;
	scene->sphere->colour = pars_colour(&line, scene);
	if (!scene->mistake)
		return (write(2, "Error\nwrong sphere\n", 19));
	return (0);
}

int		pars_sphere(char *line, t_scene *scene)
{
	static int	count_sphere = 0;
	t_sphere	*new;

	if (count_sphere == 0)
	{
		count_sphere = 1;
		scene->sphere->count++;
		return (pars_sphere_list(line, scene));
	}
	else
	{
		count_sphere = 0;
		new = sp_init();
		new->next = scene->sphere;
		scene->sphere = new;
		return (pars_sphere(line, scene));
	}
}
