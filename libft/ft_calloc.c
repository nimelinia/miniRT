/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 12:25:22 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/11 23:28:43 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = (char*)malloc(num * size);
	if (!dest)
		return (NULL);
	while (i < num * size)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}
