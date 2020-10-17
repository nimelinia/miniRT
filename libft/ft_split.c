/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:55:33 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/11 21:37:12 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	**ft_free(char **dest, int i)
{
	while (i > 0)
	{
		free(dest[i]);
		i--;
	}
	free(dest);
	dest = NULL;
	return (0);
}

static int	word_size(char const *s, char c)
{
	int		size;

	size = 0;
	while (s[size] != c && s[size])
		size++;
	return (size + 1);
}

static char	*word_creat(char const *s, char c)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char*)(malloc(sizeof(char) * word_size(s, c)));
	while (s[i] != c && s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	word_count(char const *s, char c)
{
	int		count;
	int		i;
	int		sym;
	int		l;

	count = 0;
	i = 0;
	sym = 0;
	l = 1;
	if (s[i] == c)
		l = 0;
	while (s[i])
	{
		if (s[i] != c)
			sym++;
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			count++;
		i++;
	}
	if (sym == 0)
		return (0);
	return (count + l);
}

char		**ft_split(char const *s, char c)
{
	int		i_s;
	int		i_d;
	char	**dest;

	if (!s)
		return (0);
	i_s = 0;
	i_d = 0;
	if (!(dest = (char**)(malloc(sizeof(s) * (word_count(s, c) + 1)))))
		return (NULL);
	while (s[i_s] != '\0' && i_d < word_count(s, c))
	{
		while (s[i_s] == c)
			i_s++;
		if (s[i_s])
		{
			dest[i_d++] = word_creat(s + i_s, c);
			if (!dest[i_d - 1])
				return (char**)(ft_free(dest, i_d - 1));
		}
		i_s = i_s + word_size(s + i_s, c) - 1;
	}
	if (dest)
		dest[word_count(s, c)] = 0;
	return (dest);
}
