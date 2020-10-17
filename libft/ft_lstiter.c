/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 19:57:04 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/10 20:26:45 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*bonus;

	if (!lst || !f)
		return ;
	bonus = lst;
	while (bonus)
	{
		f(bonus->content);
		bonus = bonus->next;
	}
}
