/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:21:39 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/28 18:50:58 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_err_handler(char *msg, char *add, int err)
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

int		ft_key_handler(int key, t_window *win)
{
	char			e;

	e = 0;
	key == KEY_ESC ? ft_destroy_win(win) : 0;
	key == KEY_ARR_UP && ++e ? win->pivot.y -= 30 * win->dx : 0;
	key == KEY_ARR_DOWN && ++e ? win->pivot.y += 30 * win->dx : 0;
	key == KEY_ARR_RIGHT && ++e ? win->pivot.x += 30 * win->dx : 0;
	key == KEY_ARR_LEFT && ++e ? win->pivot.x -= 30 * win->dx : 0;
	e ? ft_draw(*win->env, win) : 0;
	return (0);
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
	e ? ft_draw(*win->env, win) : 0;
	return (0);
}
