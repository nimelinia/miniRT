/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:20:04 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/09 15:00:02 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

int		ft_isdigit(int sym)
{
	if (sym >= 48 && sym <= 57)
		return (1);
	else
		return (0);
}

void	check_scene(t_scene *scene) // проверка на наличие обязательных элементов: размер окна, освещение, камера
{
	if (scene->camera->count < 1 || scene->ambi.count != 1 || scene->resol.count != 1)
	{
		scene->mistake = 0;
		write(2, "wrong scene\n", 12);
	}
}

int		minirt(int argc, char **argv)
{
	char	*line;
	int		fd;
	t_scene	scene;

	if (argc != 2)
		return (write(2, "error of quantity of arguments\n", 31));
	line = argv[1];
	fd = open(line, O_RDONLY);
	parser(&scene, fd);
	t_init_points(&scene);
	check_scene(&scene);
	if (scene.mistake)
		start_work(&scene);
	return (0);
}

int		main(int argc, char **argv)
{
	minirt(argc, argv);
	return (0);
}
