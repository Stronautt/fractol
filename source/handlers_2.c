/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 13:07:45 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/02 16:02:48 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			ft_mouse_move_handler(int x, int y, t_window *win)
{
	char		e;

	e = 0;
	win->intra_m && ++e ? win->c.x = (-1.4 * x) / win->width : 0;
	win->intra_m && ++e ? win->c.y = 0.5403 * y / win->height : 0;
	return (e ? ft_draw(*win->env, win) : 0);
}

t_window	*ft_button_actions(int key, int x, int y, t_window *win)
{
	t_window	*fract;

	fract = NULL;
	if (key == M_B_LEFT && x >= 450 && x <= 750 && y >= 360 && y <= 423
		&& !ft_get_win(win->env->wins, PYTHTREEFRACT))
		fract = ft_new_win(win->env, FW_WIDTH, FW_HEIGHT, PYTHTREEFRACT);
	return (fract);
}
