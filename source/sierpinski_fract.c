/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski_fract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 21:17:30 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/02 21:43:51 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_sierpinskihelp(t_window *win)
{
	mlx_string_put(win->env->mlx_p, win->win_p, 100, 105,
					0x8C8C, "Sierpinski triangle fractal HELP");
	mlx_string_put(win->env->mlx_p, win->win_p, 20, 165,
					0, "- You can scale this triangle, controls: ");
	mlx_string_put(win->env->mlx_p, win->win_p, 40, 185,
					0xAC, "SCROLL_UP to scale up, SCROLL_DOWN - otherwise.");
	mlx_string_put(win->env->mlx_p, win->win_p, 20, 355, 0x8C, "ESC");
	mlx_string_put(win->env->mlx_p, win->win_p, 60, 355, 0, "- to close.");
}

void			ft_init_sierpinski(t_window *win)
{
	win->dx = 3;
	mlx_hook(win->win_p, 2, 0, &ft_key_geom_handler, win);
	mlx_mouse_hook(win->win_p, &ft_mouse_jf_handler, win);
}

static void		ft_sierpinskirecurs(t_vertice v[3], int it, t_window *win)
{
	t_vertice	*m;

	m = (t_vertice[3]){{.x = (v[0].x + v[1].x) / 2, .y = (v[0].y + v[1].y) / 2},
		{.x = (v[0].x + v[2].x) / 2, .y = (v[0].y + v[2].y) / 2},
		{.x = (v[1].x + v[2].x) / 2, .y = (v[1].y + v[2].y) / 2}};
	if (it > 0)
	{
		ft_draw_line(win, v[0], v[1], 0xFFFFFF);
		ft_draw_line(win, v[1], v[2], 0xFFFFFF);
		ft_draw_line(win, v[0], v[2], 0xFFFFFF);
		ft_sierpinskirecurs((t_vertice[3]){v[0], m[0], m[1]}, it - 1, win);
		ft_sierpinskirecurs((t_vertice[3]){v[1], m[0], m[2]}, it - 1, win);
		ft_sierpinskirecurs((t_vertice[3]){v[2], m[1], m[2]}, it - 1, win);
	}
}

void			ft_sierpinski(t_window *win)
{
	win->dx > 10 ? win->dx = 10 : 0;
	win->dx <= 1 ? win->dx = 1 : 0;
	ft_sierpinskirecurs((t_vertice[3]){{.x = win->width / 2 - 600,
										.y = win->height - 250},
										{.x = win->width / 2,
										.y = win->height - 1250},
										{.x = win->width / 2 + 600,
										.y = win->height - 250}},
										win->dx, win);
}
