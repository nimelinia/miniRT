/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:20:49 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/05 14:37:10 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*scont;
	int		i;
	int		h;

	if (!s1 || !s2)
		return (NULL);
	scont = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char*));
	if (!scont)
		return (NULL);
	i = 0;
	h = 0;
	while (s1[i] != '\0')
	{
		scont[i] = s1[i];
		i++;
	}
	while (s2[h] != '\0')
	{
		scont[i + h] = s2[h];
		h++;
	}
	scont[i + h] = '\0';
	return (scont);
}
