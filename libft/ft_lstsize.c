/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 14:20:30 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/10 14:29:01 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*bonus;

	i = 0;
	if (!lst)
		return (0);
	bonus = lst;
	while (bonus)
	{
		i++;
		bonus = bonus->next;
	}
	return (i);
}
