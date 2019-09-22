/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:51:59 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/02 20:31:09 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_init_fracttree(t_window *win)
{
	win->c.z = 60;
	win->c.color = 20;
	win->dx = 1;
	// mlx_hook(win->win_p, 2, 0, &ft_key_geom_handler, win);
	// mlx_mouse_hook(win->win_p, &ft_mouse_jf_handler, win);
}

static void		ft_fractrecurs(t_vertice start, int angle,
								int iter, t_window *win)
{
	t_vertice	c;
	int			color;
	double		angle_rad;

	angle_rad = ft_degtorad(angle);
	if (iter > 0)
	{
		c.x = start.x + cos(angle_rad) * iter / floor(win->dx) * win->c.z;
		c.y = start.y + sin(angle_rad) * iter / floor(win->dx) * win->c.z;
		color = ft_g_color(0xFF00, 0x8B4513, iter / floor(win->dx));
		ft_draw_line(win, start, c, color);
		ft_fractrecurs(c, angle + win->c.color, iter - 1, win);
		ft_fractrecurs(c, angle - win->c.color, iter - 1, win);
	}
}

void			ft_fracttree(t_window *win)
{
	win->pivot.x = win->width / 2;
	win->pivot.y = win->height - 400;
	win->dx > 16 ? win->dx = 16 : 0;
	win->dx <= 1 ? win->dx = 1 : 0;
	ft_fractrecurs(win->pivot, -90, win->dx, win);
}
