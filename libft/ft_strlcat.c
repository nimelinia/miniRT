/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 20:50:07 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/07 20:25:00 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t count;
	size_t countdst;
	size_t i;

	i = 0;
	count = 0;
	countdst = 0;
	while (src[count] != '\0')
		count++;
	while (dst[countdst] != '\0')
		countdst++;
	if (countdst >= size)
		count = count + size;
	else
		count = count + countdst;
	while (src[i] != '\0' && (int)(countdst + i) < (int)(size - 1))
	{
		dst[countdst + i] = src[i];
		i++;
	}
	dst[countdst + i] = '\0';
	return (count);
}
