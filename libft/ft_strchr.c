/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:40:22 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/08 19:24:24 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int sym)
{
	int i;

	i = 0;
	if (str[i] == sym)
		return ((char*)str);
	while (str[i])
	{
		if (str[i] == sym)
		{
			str = str + i;
			return ((char*)str);
		}
		i++;
		if (str[i] == sym)
		{
			str = str + i;
			return ((char*)str);
		}
	}
	return (NULL);
}
