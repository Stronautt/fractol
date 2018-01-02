/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:32:17 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/02 15:24:22 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_uchar		ft_get_alpha(intmax_t c)
{
	return (c / 16777216 % 256);
}

t_uchar		ft_get_red(intmax_t c)
{
	return (c / 65536 % 256);
}

t_uchar		ft_get_green(intmax_t c)
{
	return (c / 256 % 256);
}

t_uchar		ft_get_blue(intmax_t c)
{
	return (c % 256);
}

intmax_t	ft_g_color(intmax_t c1, intmax_t c2, double k)
{
	t_uchar	r;
	t_uchar	g;
	t_uchar	b;

	b = ft_get_blue(c1) + k * (ft_get_blue(c2) - ft_get_blue(c1));
	g = ft_get_green(c1) + k * (ft_get_green(c2) - ft_get_green(c1));
	r = ft_get_red(c1) + k * (ft_get_red(c2) - ft_get_red(c1));
	return (b + g * 256 + r * 65536);
}
