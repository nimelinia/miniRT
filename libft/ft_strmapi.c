/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 10:31:49 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/09 21:57:16 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*dest;
	unsigned int		i;

	i = 0;
	if (!f || !s)
		return (NULL);
	if (!(dest = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i])
	{
		dest[i] = f(i, s[i]);
		if (!dest[i])
			return (NULL);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
