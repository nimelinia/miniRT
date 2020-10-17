/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 10:56:21 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/11 20:28:42 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa3(char *dest, int n, int count, int h)
{
	while (count > 0)
	{
		dest[h] = n / count + '0';
		n = n % count;
		count = count / 10;
		h++;
	}
	dest[h] = '\0';
	return (dest);
}

static char	*ft_itoa2(int n, char *dest)
{
	int		count;
	int		i;
	int		h;

	count = 1;
	h = 0;
	if (n < 0)
	{
		dest[h] = '-';
		h++;
		if (n == -2147483648)
		{
			dest[h] = '2';
			h++;
			n = -147483648;
		}
		n = -n;
	}
	i = n;
	while (i > 9)
	{
		i = i / 10;
		count = count * 10;
	}
	return (ft_itoa3(dest, n, count, h));
}

char		*ft_itoa(int n)
{
	int		size;
	int		temp;
	char	*dest;

	size = 0;
	if (n == 0)
		size = 1;
	temp = n;
	while (temp != 0)
	{
		temp /= 10;
		size++;
	}
	if (n < 0)
		size++;
	if (!(dest = (char*)malloc(size + 1)))
		return (NULL);
	return (ft_itoa2(n, dest));
}
