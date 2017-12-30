/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 13:07:45 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/30 13:08:23 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_mouse_move_handler(int x, int y, t_window *win)
{
	char		e;

	e = 0;
	win->intra_m && ++e ? win->c.x = (-1.4 * x) / win->width : 0;
	win->intra_m && ++e ? win->c.y = 0.5403 * y / win->height : 0;
	return (e ? ft_draw(*win->env, win) : 0);
}
