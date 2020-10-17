/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:43:29 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/05 16:03:24 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *src, size_t num)
{
	size_t			i;
	unsigned char	*dest;

	i = num;
	dest = (unsigned char*)src;
	while (i > 0)
	{
		i--;
		dest[i] = 0;
	}
	src = dest;
}
