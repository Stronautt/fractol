/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:21:39 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/02 21:43:54 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_err_handler(char *msg, const char *add, int err)
{
	if (!msg)
		exit(-1);
	if (err && add)
		ft_printf("{red}%s: {yellow}%s{nc} - {red}%s{nc}\n",
		msg, add, strerror(errno));
	else if (msg && add)
		ft_printf("{red}Error: {yellow}%s : %s{nc}\n", msg, add);
	else if (err)
		ft_printf("%s: {red}%s{nc}\n", msg, strerror(err));
	else
		ft_printf("{red}Error: {yellow}%s{nc}\n", msg);
	exit(err ? err : -1);
}

int		ft_menu_mouse_handler(int key, int x, int y, t_window *win)
{
	t_window		*fract;
	int				i;

	if (key == M_B_LEFT && x >= 50 && x <= 350 && y >= 290 && y <= 353
		&& !ft_get_win(win->env->wins, TRICORNFRACT))
		fract = ft_new_win(win->env, FW_WIDTH, FW_HEIGHT, TRICORNFRACT);
	else if (key == M_B_LEFT && x >= 50 && x <= 350 && y >= 360 && y <= 423
		&& !ft_get_win(win->env->wins, MANDELFRACT))
		fract = ft_new_win(win->env, FW_WIDTH, FW_HEIGHT, MANDELFRACT);
	else if (key == M_B_LEFT && x >= 50 && x <= 350 && y >= 430 && y <= 493
		&& !ft_get_win(win->env->wins, BURNINGSHIP))
		fract = ft_new_win(win->env, FW_WIDTH, FW_HEIGHT, BURNINGSHIP);
	else if (key == M_B_LEFT && x >= 50 && x <= 350 && y >= 500 && y <= 563
		&& !ft_get_win(win->env->wins, JULIAFRACT))
		fract = ft_new_win(win->env, FW_WIDTH, FW_HEIGHT, JULIAFRACT);
	else
		fract = ft_button_actions(key, x, y, win);
	i = -1;
	while (fract && win->env->init_table[++i].func)
		if (!ft_strcmp(fract->title, win->env->init_table[i].key))
			win->env->init_table[i].func(fract);
	return (fract ? ft_draw(*win->env, fract) : 0);
}

int		ft_key_handler(int key, t_window *win)
{
	char			e;

	e = 0;
	if (ft_strcmp(win->title, JULIAFRACT))
	{
		key == KEY_ARR_UP && ++e ? win->pivot.y -= 30 * win->dx : 0;
		key == KEY_ARR_DOWN && ++e ? win->pivot.y += 30 * win->dx : 0;
		key == KEY_ARR_RIGHT && ++e ? win->pivot.x += 30 * win->dx : 0;
		key == KEY_ARR_LEFT && ++e ? win->pivot.x -= 30 * win->dx : 0;
	}
	else
	{
		key == KEY_ARR_UP && ++e ? win->pivot.y -= 0.06 / win->dx : 0;
		key == KEY_ARR_DOWN && ++e ? win->pivot.y += 0.06 / win->dx : 0;
		key == KEY_ARR_RIGHT && ++e ? win->pivot.x += 0.06 / win->dx : 0;
		key == KEY_ARR_LEFT && ++e ? win->pivot.x -= 0.06 / win->dx : 0;
	}
	key == KEY_ESC && (win->safe_m = 1) ? ft_destroy_win(win) : 0;
	!e && key == KEY_Q && !win->intra_m && ++e ? win->intra_m = 1 : 0;
	!e && key == KEY_Q && win->intra_m && ++e ? win->intra_m = 0 : 0;
	return (e ? ft_draw(*win->env, win) : 0);
}

int		ft_mouse_handler(int key, int x, int y, t_window *win)
{
	char			e;

	e = 0;
	if (key == M_SCROLL_UP)
	{
		win->pivot.x = ft_lerp(win->pivot.x,
			win->pivot.x + (x - win->width / 2.0) * win->dx, 0.07);
		win->pivot.y = ft_lerp(win->pivot.y,
			win->pivot.y + (y - win->height / 2.0) * win->dx, 0.07);
	}
	if (key == M_SCROLL_UP && ++e)
		win->dx -= win->dx / 18.0;
	else if (key == M_SCROLL_DOWN && ++e)
		win->dx += win->dx / 18.0;
	return (e ? ft_draw(*win->env, win) : 0);
}

int		ft_mouse_jf_handler(int key, int x, int y, t_window *win)
{
	char			e;

	e = 0;
	if (key == M_SCROLL_UP)
	{
		win->pivot.x = ft_lerp(win->pivot.x,
			1.5 * (x - win->width / 2) / (0.5 * win->dx *\
				win->width) + win->pivot.x, 0.06);
		win->pivot.y = ft_lerp(win->pivot.y,
			(y - win->height / 2) / (0.5 * win->dx *\
				win->height) + win->pivot.y, 0.06);
	}
	if (key == M_SCROLL_DOWN && ++e)
		win->dx -= win->dx / 18.0;
	else if (key == M_SCROLL_UP && ++e)
		win->dx += win->dx / 18.0;
	return (e ? ft_draw(*win->env, win) : 0);
}
