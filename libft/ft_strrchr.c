/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:42:26 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/03 22:59:32 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int sym)
{
	int i;
	int h;

	i = 0;
	h = -1;
	if (str[i] == sym && sym == '\0')
		return ((char*)str);
	while (str[i] != '\0')
	{
		if (str[i] == sym)
			h = i;
		i++;
	}
	if (str[i] == sym)
		return ((char*)(str + i));
	if (h == -1)
		return (NULL);
	else
		return ((char*)(str + h));
}
