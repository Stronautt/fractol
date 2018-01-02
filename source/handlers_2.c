/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 13:07:45 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/02 21:24:27 by pgritsen         ###   ########.fr       */
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
	if (key == M_B_LEFT && x >= 450 && x <= 750 && y >= 290 && y <= 353
		&& !ft_get_win(win->env->wins, FERNFRACT))
		fract = ft_new_win(win->env, FW_WIDTH, FW_HEIGHT, FERNFRACT);
	else if (key == M_B_LEFT && x >= 450 && x <= 750 && y >= 360 && y <= 423
		&& !ft_get_win(win->env->wins, PYTHTREEFRACT))
		fract = ft_new_win(win->env, FW_WIDTH, FW_HEIGHT, PYTHTREEFRACT);
	else if (key == M_B_LEFT && x >= 450 && x <= 750 && y >= 430 && y <= 493
		&& !ft_get_win(win->env->wins, FRACTTREE))
		fract = ft_new_win(win->env, FW_WIDTH, FW_HEIGHT, FRACTTREE);
	else if (key == M_B_LEFT && x >= 450 && x <= 750 && y >= 500 && y <= 563
		&& !ft_get_win(win->env->wins, SIERPINSKI))
		fract = ft_new_win(win->env, FW_WIDTH, FW_HEIGHT, SIERPINSKI);
	return (fract);
}

int			ft_key_geom_handler(int key, t_window *win)
{
	char			e;

	e = 0;
	key == KEY_ESC && (win->safe_m = 1) ? ft_destroy_win(win) : 0;
	key == KEY_PLUS && win->c.z < 120 && ++e ? win->c.z += win->c.z / 18 : 0;
	key == KEY_MINUS && win->c.z > 20 && ++e ? win->c.z -= win->c.z / 18 : 0;
	key == KEY_ARR_LEFT && win->c.color > 2 && ++e ? win->c.color-- : 0;
	key == KEY_ARR_RIGHT && win->c.color < 30 && ++e ? win->c.color++ : 0;
	key == KEY_TAB ? ft_open_help(win) : 0;
	return (e && ft_strcmp(win->title, HELP) ? ft_draw(*win->env, win) : 0);
}
