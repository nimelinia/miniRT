/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 22:30:21 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/05 13:45:06 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_iterative_putnbr_fd(int nb, int count, int fd)
{
	while (count > 0)
	{
		ft_putchar_fd(((nb / count) + '0'), fd);
		nb = nb % count;
		count = count / 10;
	}
}

void		ft_putnbr_fd(int nb, int fd)
{
	int count;
	int i;

	count = 1;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		if (nb == -2147483648)
		{
			ft_putchar_fd('2', fd);
			nb = -147483648;
		}
		nb = -nb;
	}
	i = nb;
	while (i > 9)
	{
		i = i / 10;
		count = count * 10;
	}
	ft_iterative_putnbr_fd(nb, count, fd);
}
