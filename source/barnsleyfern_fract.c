/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barnsleyfern_fract.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 16:17:15 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/30 19:09:55 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_fernhelp(t_window *win)
{
	mlx_string_put(win->env->mlx_p, win->win_p, 100, 105,
					0x8C8C, "Barnsley Fern Fractal HELP");
	mlx_string_put(win->env->mlx_p, win->win_p, 20, 275, 0x8C, "ESC");
	mlx_string_put(win->env->mlx_p, win->win_p, 60, 275, 0, "- to close.");
}

void	ft_init_fernfract(t_window *win)
{
	win->pivot.x = 0.0;
	win->pivot.y = 0.0;
	win->dx = 1000000.0;
	mlx_hook(win->win_p, 2, 0, &ft_key_handler, win);
}

void	ft_fernfract(t_window *win)
{
	t_vertice	p1;
	t_vertice	p0;
	int			dt;
	time_t		t;

	p0 = (t_vertice){.x = 0, .y = 0};
	srand((unsigned)time(&t));
	while (win->dx-- > 0 && !((dt = rand() % 100) * 0))
	{
		if (dt == 0)
			p1 = (t_vertice){.x = 0, 0.16 * p0.y};
		else if (dt >= 1 && dt <= 7)
			p1 = (t_vertice){.x = -0.15 * p0.x + 0.28 * p0.y,
								0.26 * p0.x + 0.24 * p0.y + 0.44};
		else if (dt >= 8 && dt <= 15)
			p1 = (t_vertice){.x = 0.2 * p0.x - 0.26 * p0.y,
								.y = 0.23 * p0.x + 0.22 * p0.y + 1.6};
		else
			p1 = (t_vertice){.x = 0.85 * p0.x + 0.04 * p0.y,
								.y = -0.04 * p0.x + 0.85 * p0.y + 1.6};
		win->pixels.buff[(int)(win->height - 135 - p1.y * 110)\
							* win->pixels.s_l + (int)(110 * p1.x\
							+ win->width / 2) * 4 + 1] = 0xFF;
		p0 = p1;
	}
}
