/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:24:03 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/02 17:56:43 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void	right_buttons(t_window *win, void *button)
{
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, button, 50, 290);
	mlx_string_put(win->env->mlx_p, win->win_p, 140, 308, 0, "Tricorn Set");
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, button, 50, 360);
	mlx_string_put(win->env->mlx_p, win->win_p, 125, 378, 0, "Mandelbrot Set");
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, button, 50, 430);
	mlx_string_put(win->env->mlx_p, win->win_p, 140, 448, 0, "BurningShip");
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, button, 50, 500);
	mlx_string_put(win->env->mlx_p, win->win_p, 150, 518, 0, "Julia Set");
}

static inline void	left_buttons(t_window *win, void *button)
{
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, button, 450, 290);
	mlx_string_put(win->env->mlx_p, win->win_p, 540, 308, 0, "BarnsleyFern");
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, button, 450, 360);
	mlx_string_put(win->env->mlx_p, win->win_p, 535, 378, 0, "PythagorasTree");
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, button, 450, 430);
	mlx_string_put(win->env->mlx_p, win->win_p, 540, 448, 0, "Fractal Tree");
}

void				ft_menu(t_window *win)
{
	int		t;
	void	*button;
	void	*logo;

	ft_set_background(win, 0xFFFFFF);
	button = mlx_xpm_file_to_image(win->env->mlx_p,
		"resource/menu_button.xpm", &t, &t);
	logo = mlx_xpm_file_to_image(win->env->mlx_p, "resource/logo.xpm", &t, &t);
	!button || !logo ? ft_err_handler("Can't find resource!", NULL, 0) : 0;
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, logo, 50, 50);
	mlx_string_put(win->env->mlx_p, win->win_p, 635, 225, 0, "By pgritsen");
	mlx_string_put(win->env->mlx_p, win->win_p, 50, 570, 0, "HELP: 'TAB'");
	mlx_string_put(win->env->mlx_p, win->win_p, 640, 570, 0, "'ESC' :EXIT");
	right_buttons(win, button);
	left_buttons(win, button);
}
