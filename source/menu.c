/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:24:03 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/30 14:28:41 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_menu(t_window *win)
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
	mlx_string_put(win->env->mlx_p, win->win_p, 50, 570, 0, "HELP: TAB");
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, button, 40, 290);
	mlx_string_put(win->env->mlx_p, win->win_p, 130, 308, 0, "Tricorn Set");
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, button, 40, 360);
	mlx_string_put(win->env->mlx_p, win->win_p, 115, 378, 0, "Mandelbrot Set");
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, button, 40, 430);
	mlx_string_put(win->env->mlx_p, win->win_p, 130, 448, 0, "BurningShip");
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, button, 40, 500);
	mlx_string_put(win->env->mlx_p, win->win_p, 140, 518, 0, "Julia Set");
}
