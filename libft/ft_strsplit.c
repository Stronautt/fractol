/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 20:24:49 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/13 15:42:28 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	s_count(char const *s, char c)
{
	size_t	words;

	if (!s)
		return (0);
	words = 1;
	while (*s)
	{
		if (*s == c)
		{
			words++;
			while (*s && *s == c)
				s++;
		}
		while (*s && *s != c)
			s++;
	}
	return (words);
}

static void		*clean_list(char **list)
{
	char	**tmp;

	tmp = list;
	while (tmp)
		free(*tmp++);
	if (list)
		free(list);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**list;
	char	*p_s;
	long	s_c;
	size_t	it;
	size_t	w_l;

	if (!s)
		return (NULL);
	s_c = (long)s_count(ft_strntrim(s, c), c);
	if (!(list = (char **)malloc(sizeof(char *) * (s_c + 1))))
		return (NULL);
	if (!*(p_s = ft_strntrim(s, c)))
		*list = (char *)--s_c;
	it = 0;
	while (s_c-- > 0)
	{
		p_s = ft_strntrim(p_s, c);
		w_l = ft_strclen(p_s, c);
		if (!(list[it] = (char *)malloc(sizeof(char) * (w_l + 1))))
			return (clean_list(list));
		*list[it] = 0;
		ft_strlcat(list[it++], (p_s += w_l) - w_l, w_l + 1);
	}
	list[it] = 0;
	return (list);
}
