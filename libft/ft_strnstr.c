/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 11:17:17 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/13 14:45:07 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t i;
	size_t h;

	i = 0;
	h = 0;
	if (!(*small))
		return ((char*)big);
	while (big[i] && i < len)
	{
		while (big[i + h] && big[i + h] == small[h] && (i + h) < len)
			h++;
		if (!small[h])
			return ((char*)(big + i));
		else
			h = 0;
		i++;
	}
	return (NULL);
}
