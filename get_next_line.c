/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 15:32:51 by scopycat          #+#    #+#             */
/*   Updated: 2020/06/08 22:18:23 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** в случае, если было что-то пошло не так, данная
** функция чистит пространство и возвращает -1
*/

static int	free_buf(char **buf)
{
	if (*buf)
		free(*buf);
	*buf = NULL;
	return (-1);
}

/*
** в случае, если где-то маллок не выделил память, нам нужно почистить то,
** что было выделено, и индикатор err приравнять к -1. благодаря этому, мы
** в основной функции больше никуда не зайдем, и вернем -1. а eof занулим.
*/

static char	*wrong_malloc(int *err, char **hub)
{
	*err = free_buf(hub);
	return (NULL);
}

/*
** при первом заходе функция просто инициализирует line \0, в дальнейшем,
** в случае, если после считывания после \n был какой-то текст и он был
** записан в hub, то в line записывается та его часть, которая идет до \n
** или, если \n нет в hub, то в line записывается он целиком. hub
** перезаписывается строкой, которая идет после \n.
*/

static char	*check_hub(char **hub, char **line, int *err)
{
	char	*eof;
	char	*tmp;

	eof = NULL;
	if (hub && *hub)
	{
		if ((eof = ft_strchr_gnl(*hub)))
		{
			if (!(*line = ft_strdup(*hub)))
				return (wrong_malloc(err, hub));
			tmp = *hub;
			if (!(*hub = ft_strdup(eof + 1)))
				return (wrong_malloc(err, hub));
			free_buf(&tmp);
		}
		else
		{
			if (!(*line = ft_strdup(*hub)))
				return (wrong_malloc(err, hub));
			free_buf(hub);
		}
	}
	else
		*line = ft_strdup("");
	return (eof);
}

/*
** функция возвращает -1 (ошибка), 0 (файл прочитан до конца), 1 (строка
** прочитана до \n). при этом, по адресу line записывается считанная до
** \n строка. остаток записывается в переменную hub, который через
** функцию check_hub записывается в line. 0 вернется, только если в
** функции check_hub в остатке не нашли \n и при прочтении на \n не
** наткнулись + дочитали до конца.
*/

int			get_next_line(int fd, char **line)
{
	char		*buf;
	size_t		i;
	static char	*hub;
	char		*eof;
	int			err;

	err = 1;
	if (!(buf = (char*)malloc(BUFFER_SIZE + 1)) || fd < 0 ||
				BUFFER_SIZE < 1 || !line || read(fd, buf, 0) < 0)
		return (free_buf(&buf) * free_buf(&hub) * -1);
	eof = check_hub(&hub, line, &err);
	while (!eof && err == 1 && (i = read(fd, buf, BUFFER_SIZE)))
	{
		buf[i] = '\0';
		if ((eof = ft_strchr_gnl(buf)))
		{
			free_buf(&hub);
			if (!(hub = ft_strdup(eof + 1)))
				return (free_buf(line) * free_buf(&buf) * free_buf(&hub));
		}
		if (!(*line = ft_strjoin_gnl(*line, buf)))
			return (free_buf(line) * free_buf(&buf) * free_buf(&hub));
	}
	free(buf);
	return ((!eof && !i) ? 0 * (free_buf(&hub)) : 1 * err);
}
