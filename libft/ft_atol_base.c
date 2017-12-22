/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 20:21:05 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/16 20:29:37 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_atol_base(const char *s, int base)
{
	intmax_t	ret;
	int			sign;
	int			it;
	int			tmp;

	if (base < 2 || base > 36)
		return (0);
	if (*s == 0)
		return (0);
	while (((*s > '\10' && *s <= '\16') || *s == '\40'))
		s++;
	sign = 1;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	ret = 0;
	it = 0;
	while (ft_isalnum(*s))
	{
		if ((tmp = ft_strclen(NUMERIC_ALPHABET, *s++)) > base)
			break ;
		ret = (ret * base) + tmp;
	}
	return (ret * sign);
}
