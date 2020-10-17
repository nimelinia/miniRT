/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:34:11 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/14 16:19:46 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int s, size_t count)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char*)src;
	while (i < count)
	{
		if (temp[i] == (unsigned char)s)
			return (temp + i);
		i++;
	}
	return (NULL);
}
