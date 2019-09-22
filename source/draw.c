/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:12:26 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/02 19:56:58 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_set_background(t_window *win, t_uint color)
{
	int		i;
	long	limit;

	limit = win->width * win->height * 4;
	i = -4;
	while ((i += 4) < limit)
		ft_memcpy((char *)win->surface->pixels + i, &color, 4);
}

void		ft_draw_line(t_window *win, t_vertice p0, t_vertice p1, int color)
{
	t_vertice	tmp;
	int			pix;
	double		t;
	double		k;

	k = sqrt((p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y));
	k = 1.0 / k;
	t = -k;
	while ((t += k) <= 1)
	{
		tmp.x = p0.x + (p1.x - p0.x) * t;
		tmp.y = p0.y + (p1.y - p0.y) * t;
		pix = (int)(tmp.y) * win->surface->pitch + (int)(tmp.x) * 4;
		if (pix <= win->surface->pitch * win->height && pix >= 0)
			ft_memcpy((char *)win->surface->pixels + pix, &color, 4);
	}
}

int			ft_draw(t_env env, t_window *win)
{
	int		i;

	ft_bzero(win->surface->pixels, win->height * win->width * win->surface->format->BytesPerPixel);
	i = -1;
	while (env.dpndc[++i].key)
		if (!ft_strcmp(win->title, env.dpndc[i].key)
			&& env.dpndc[i].func)
		{
			env.dpndc[i].func(win);
			break ;
		}
	return (0);
}
