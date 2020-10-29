/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:20:04 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/28 14:00:10 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

int	ft_strncmp(const char *str1, const char *str2, size_t len)
{
	size_t i;

	i = 0;
	if (len == 0)
		return (0);
	while (str1[i] && str1[i] == str2[i] && i < (len - 1))
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

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
		write(2, "Error\nwrong scene\n", 18);
	}
}

int		minirt(int argc, char **argv)
{
	char	*line;
	int		fd;
	t_scene	scene;

	if (argc != 2 && !(argc == 3 && !check_save(argv[2])))
		return (write(2, "Error\nerror of quantity of arguments\n", 37));
	line = argv[1];
	fd = open(line, O_RDONLY);
	parser(&scene, fd);
	t_init_points(&scene);
	check_scene(&scene);
	if (argc == 3 && !check_save(argv[2]))
	{
		scene.save = 1;
		scene.scene_name = ft_strdup(argv[1]);
	}
	else
		scene.save = 0;
	if (scene.mistake)
		start_work(&scene);
	return (0);
}

double	check_save(char *frase)
{
	char	*save;

	save = "--save";
	return (ft_strncmp(frase, save, 7));
}

int		main(int argc, char **argv)
{
	minirt(argc, argv);
	return (0);
}

// проверка на валидность файла
// if (ft_strncmp(&(rt[ft_strlen(rt) - 3]), ".rt", 4))
//     {
//         ft_putstr_fd("Exit with error: Invalid file extension\n", 2);
//         exit(1);
//     }