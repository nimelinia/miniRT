/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:35:46 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/14 15:59:46 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *str)
{
	int				i;
	int				znak;
	unsigned long	rez;

	i = 0;
	znak = 1;
	rez = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == 127)
		i++;
	if (str[i] == '-')
		znak = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((rez * 10 + (str[i] - '0')) < rez)
			return (znak == 1 ? -1 : 0);
		rez = (rez * 10) + (str[i] - '0');
		i++;
	}
	rez = rez * znak;
	return ((int)rez);
}
