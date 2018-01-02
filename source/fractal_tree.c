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

void			ft_fracttreehelp(t_window *win)
{
	mlx_string_put(win->env->mlx_p, win->win_p, 100, 105,
					0x8C8C, "Fractal Tree HELP");
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

void			ft_init_fracttree(t_window *win)
{
	win->c.z = 60;
	win->c.color = 20;
	win->dx = 1;
	mlx_hook(win->win_p, 2, 0, &ft_key_geom_handler, win);
	mlx_mouse_hook(win->win_p, &ft_mouse_jf_handler, win);
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
