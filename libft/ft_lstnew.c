/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 14:05:51 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/10 14:33:47 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*bonus;

	if (!(bonus = (t_list*)malloc(sizeof(bonus))))
		return (NULL);
	bonus->content = content;
	bonus->next = NULL;
	return (bonus);
}
