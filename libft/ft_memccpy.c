/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 21:26:10 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/14 16:27:48 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int s, size_t count)
{
	size_t			i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	i = 0;
	if (!src && !dst)
		return ((unsigned char*)src);
	else if (!src && count == 0)
		return ((unsigned char*)dst);
	temp1 = (unsigned char*)src;
	temp2 = (unsigned char*)dst;
	while (temp1[i] && (i < count))
	{
		temp2[i] = temp1[i];
		if (temp1[i] == (unsigned char)s)
			return (temp2 + i + 1);
		i++;
		if (!temp1[i] && i != count)
			temp2[i] = '\0';
	}
	return (NULL);
}
