/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:29:21 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/10 20:27:21 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*bonus;
	t_list	*nxt;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		bonus = *lst;
		nxt = bonus->next;
		del(bonus->content);
		free(bonus);
		*lst = nxt;
	}
}
