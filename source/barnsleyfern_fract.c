/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barnsleyfern_fract.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 16:17:15 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/02 13:44:39 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void					ft_fernhelp(t_window *win)
{
	mlx_string_put(win->env->mlx_p, win->win_p, 100, 105,
					0x8C8C, "Barnsley Fern Fractal HELP");
	mlx_string_put(win->env->mlx_p, win->win_p, 20, 165,
					0, "- You can grow this fern, controls: ");
	mlx_string_put(win->env->mlx_p, win->win_p, 40, 185,
					0xAC, "'+' to grow up, '-' - otherwise.");
	mlx_string_put(win->env->mlx_p, win->win_p, 20, 275, 0x8C, "ESC");
	mlx_string_put(win->env->mlx_p, win->win_p, 60, 275, 0, "- to close.");
}

void					ft_init_fernfract(t_window *win)
{
	win->pivot.x = 0.0;
	win->pivot.y = 0.0;
	win->dx = 1000000.0;
	win->c.z = 20;
	mlx_hook(win->win_p, 2, 0, &ft_key_handler, win);
}

inline static t_vertice	ft_distribute(int dt, t_vertice p0)
{
	t_vertice	p1;

	if (dt == 0)
		p1 = (t_vertice){.x = 0, .y = 0.2 * p0.y};
	else if (dt >= 1 && dt <= 7)
		p1 = (t_vertice){.x = -0.15 * p0.x + 0.24 * p0.y,
						.y = 0.24 * p0.x + 0.24 * p0.y + 0.44};
	else if (dt >= 8 && dt <= 15)
		p1 = (t_vertice){.x = 0.2 * p0.x - 0.31 * p0.y,
						.y = 0.255 * p0.x + 0.245 * p0.y + 0.29};
	else
		p1 = (t_vertice){.x = 0.845 * p0.x + 0.035 * p0.y,
						.y = -0.035 * p0.x + 0.82 * p0.y + 1.6};
	return (p1);
}

void					ft_fernfract(t_window *win)
{
	t_vertice	p1;
	t_vertice	p0;
	int			pix;
	int			dt;
	long		max_it;

	p0 = (t_vertice){.x = 0, .y = 0};
	max_it = win->dx;
	while (max_it-- > 0)
	{
		dt = rand() % 100;
		p1 = ft_distribute(dt, p0);
		pix = (int)(win->height - 135 - p1.y * win->c.z) * win->pixels.s_l\
				+ (int)(win->c.z * p1.x + win->width / 2) * 4 + 1;
		if (pix <= win->width * win->height * 4 && pix >= 0)
			win->pixels.buff[pix] = 0xFF;
		p0 = p1;
	}
}
