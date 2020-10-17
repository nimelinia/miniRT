/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:56:20 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/09 09:47:14 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t count)
{
	unsigned int	i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	i = 0;
	if (count == 0)
		return (0);
	temp1 = (unsigned char*)s1;
	temp2 = (unsigned char*)s2;
	while ((temp1[i] == temp2[i]) && i < (count - 1))
		i++;
	return (temp1[i] - temp2[i]);
}
