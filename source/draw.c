/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:12:26 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/02 14:40:28 by pgritsen         ###   ########.fr       */
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
		ft_memcpy(&win->pixels.buff[i], &color, 4);
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, win->pixels.p, 0, 0);
}

void		ft_print_debug(t_env env, t_window *win)
{
	char	buff[128];

	if (!ft_strcmp(win->title, PROGRAM_NAME))
		return ;
	sprintf(buff, "X:    %a", win->pivot.x);
	mlx_string_put(env.mlx_p, win->win_p, 10, 10, 0x00FF00, buff);
	sprintf(buff, "Y:    %a", win->pivot.y);
	mlx_string_put(env.mlx_p, win->win_p, 10, 30, 0x00FF00, buff);
	sprintf(buff, "Zoom: %a", win->dx);
	mlx_string_put(env.mlx_p, win->win_p, 10, 50, 0x00FF00, buff);
	if (ft_strcmp(win->title, JULIAFRACT))
		return ;
	sprintf(buff, "CX:   %a", win->c.x);
	mlx_string_put(env.mlx_p, win->win_p, 10, 70, 0x00FF00, buff);
	sprintf(buff, "CY:   %a", win->c.y);
	mlx_string_put(env.mlx_p, win->win_p, 10, 90, 0x00FF00, buff);
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
		pix = (int)(tmp.y) * win->pixels.s_l + (int)(tmp.x) * 4;
		if (pix <= win->pixels.s_l * win->height)
			ft_memcpy(&win->pixels.buff[pix], &color, 4);
	}
}

int			ft_draw(t_env env, t_window *win)
{
	int		i;

	mlx_clear_window(env.mlx_p, win->win_p);
	ft_bzero(win->pixels.buff, win->height * win->width * win->pixels.bpp / 8);
	i = -1;
	while (env.dpndc[++i].key)
		if (!ft_strcmp(win->title, env.dpndc[i].key)
			&& env.dpndc[i].func)
		{
			env.dpndc[i].func(win);
			break ;
		}
	if (ft_strcmp(win->title, PROGRAM_NAME))
		mlx_put_image_to_window(env.mlx_p, win->win_p, win->pixels.p, 0, 0);
	ft_print_debug(env, win);
	return (0);
}
