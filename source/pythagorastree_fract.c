/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pythagorastree_fract.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 14:08:53 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/02 20:43:44 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_pythtreehelp(t_window *win)
{
	mlx_string_put(win->env->mlx_p, win->win_p, 100, 105,
					0x8C8C, "Pythagoras Tree Fractal HELP");
	mlx_string_put(win->env->mlx_p, win->win_p, 20, 165,
					0, "- You can scale this tree, controls: ");
	mlx_string_put(win->env->mlx_p, win->win_p, 40, 185,
					0xAC, "'+' to scale up, '-' - otherwise.");
	mlx_string_put(win->env->mlx_p, win->win_p, 20, 215,
					0, "- You can grow this tree, controls: ");
	mlx_string_put(win->env->mlx_p, win->win_p, 40, 235,
					0xAC, "SCROLL_UP to grow up, SCROLL_DOWN - otherwise.");
	mlx_string_put(win->env->mlx_p, win->win_p, 20, 265,
					0, "- You can shrink this tree, controls: ");
	mlx_string_put(win->env->mlx_p, win->win_p, 40, 285,
				0xAC, "LEFT_ARROW to shrink wide, RIGHT_ARROW - otherwise.");
	mlx_string_put(win->env->mlx_p, win->win_p, 20, 355, 0x8C, "ESC");
	mlx_string_put(win->env->mlx_p, win->win_p, 60, 355, 0, "- to close.");
}

void			ft_init_pythtree(t_window *win)
{
	win->c.z = 20;
	win->c.color = 19;
	win->dx = 1;
	mlx_hook(win->win_p, 2, 0, &ft_key_geom_handler, win);
	mlx_mouse_hook(win->win_p, &ft_mouse_jf_handler, win);
}

static void		ft_pythrecurs(t_vertice a, t_vertice b, int iter, t_window *win)
{
	t_vertice	c;
	t_vertice	d;
	t_vertice	e;
	int			color;

	c.x = b.x - (a.y - b.y);
	c.y = b.y - (b.x - a.x);
	d.x = a.x - (a.y - b.y);
	d.y = a.y - (b.x - a.x);
	e.x = d.x + (b.x - a.x - (a.y - b.y)) / ft_degtorad(win->c.color) / 6.03;
	e.y = d.y - (b.x - a.x + a.y - b.y) / ft_degtorad(win->c.color) / 6.03;
	if (iter > 0)
	{
		color = ft_g_color(0xFF00, 0x8B4513, iter / floor(win->dx));
		ft_draw_line(win, a, b, color);
		ft_draw_line(win, c, b, color);
		ft_draw_line(win, c, d, color);
		ft_draw_line(win, a, d, color);
		ft_pythrecurs(d, e, iter - 1, win);
		ft_pythrecurs(e, c, iter - 1, win);
	}
}

void			ft_pythtreefract(t_window *win)
{
	win->pivot.x = 2.5 * win->c.z / 2.0 - 2.5 * win->c.z + win->width / 2;
	win->pivot.y = 4.5 * win->c.z + win->height / 2;
	win->c.x = 2.5 * win->c.z / 2.0 + win->width / 2;
	win->c.y = 4.5 * win->c.z + win->height / 2;
	win->c.color < 17 ? win->c.color = 17 : 0;
	win->dx > 18 ? win->dx = 18 : 0;
	win->dx <= 1 ? win->dx = 1 : 0;
	ft_pythrecurs(win->pivot, win->c, win->dx, win);
}
