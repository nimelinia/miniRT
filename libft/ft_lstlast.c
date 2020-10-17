/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:42:18 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/10 20:31:20 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*bonus;

	if (!lst)
		return (NULL);
	bonus = lst;
	while (bonus->next != NULL)
		bonus = bonus->next;
	return (bonus);
}
