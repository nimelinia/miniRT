/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:44:58 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/09 11:06:43 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t count)
{
	unsigned int	i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	i = 0;
	if (!src && !dst)
		return (dst);
	temp1 = (unsigned char*)src;
	temp2 = (unsigned char*)dst;
	while (i < count)
	{
		temp2[i] = temp1[i];
		i++;
	}
	return (temp2);
}
