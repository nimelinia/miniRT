/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:04:12 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/05 22:13:06 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t count)
{
	unsigned char		*d;
	unsigned char		*s;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	if (s == d)
		return (dst);
	if (s < d)
	{
		s = (unsigned char*)src + count - 1;
		d = dst + count - 1;
		while (count--)
			*d-- = *s--;
	}
	else
	{
		while (count--)
			*d++ = *s++;
	}
	return (dst);
}
