/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 22:54:37 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/14 16:23:14 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *src, int v, size_t num)
{
	unsigned char	*dest;

	dest = (unsigned char*)src;
	while (num > 0)
	{
		num--;
		dest[num] = (unsigned char)v;
	}
	return (src);
}
