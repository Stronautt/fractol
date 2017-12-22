/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:21:39 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/22 17:29:45 by pgritsen         ###   ########.fr       */
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
	(void)win;
	key == KEY_ESC ? exit(0) : 0;
	return (0);
}

int		ft_mouse_handler(int key, int x, int y, t_window *win)
{
	char		e;

	e = 0;
	key == KEY_ESC && ++e ? exit(0) : 0;
	if (key == M_SCROLL_UP && ++e)
		win->dx -= 0.0000001;
	if (key == M_SCROLL_DOWN && ++e)
		win->dx += 0.0000001;
	(void)x;
	(void)y;
	/*if ((key == M_SCROLL_DOWN || key == M_SCROLL_UP) && ++e)
		win->pivot.x = (W_WIDTH - x) * -0.75 / W_WIDTH;*/
	e ? ft_parse_z_buff(*win->env, win) : 0;
	return (0);
}
