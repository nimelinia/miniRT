/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:48:03 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/12 21:54:08 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*bonus;

	if (!new || !lst)
		return ;
	bonus = *lst;
	if (bonus)
	{
		while (bonus->next)
			bonus = bonus->next;
		bonus->next = new;
	}
	else
		*lst = new;
}
