/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:12:26 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/30 14:16:24 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_set_background(t_window *win, t_uint color)
{
	int		i;
	long	limit;

	limit = win->width * win->height * 4;
	i = -4;
	while ((i += 4) < limit)
		ft_memcpy(&win->pixels.buff[i], &color, 4);
	mlx_put_image_to_window(win->env->mlx_p, win->win_p, win->pixels.p, 0, 0);
}

void		ft_print_debug(t_env env, t_window *win)
{
	char	buff[128];

	if (!ft_strcmp(win->title, PROGRAM_NAME))
		return ;
	sprintf(buff, "X:    %a", win->pivot.x);
	mlx_string_put(env.mlx_p, win->win_p, 10, 10, 0x00FF00, buff);
	sprintf(buff, "Y:    %a", win->pivot.y);
	mlx_string_put(env.mlx_p, win->win_p, 10, 30, 0x00FF00, buff);
	sprintf(buff, "Zoom: %a", win->dx);
	mlx_string_put(env.mlx_p, win->win_p, 10, 50, 0x00FF00, buff);
	if (ft_strcmp(win->title, JULIAFRACT))
		return ;
	sprintf(buff, "CX:   %a", win->c.x);
	mlx_string_put(env.mlx_p, win->win_p, 10, 70, 0x00FF00, buff);
	sprintf(buff, "CY:   %a", win->c.y);
	mlx_string_put(env.mlx_p, win->win_p, 10, 90, 0x00FF00, buff);
}

int			ft_draw(t_env env, t_window *win)
{
	int		i;

	mlx_clear_window(env.mlx_p, win->win_p);
	ft_bzero(win->pixels.buff, win->height * win->width * win->pixels.bpp / 8);
	i = -1;
	while (env.dpndc[++i].key)
		if (!ft_strcmp(win->title, env.dpndc[i].key)
			&& env.dpndc[i].func)
		{
			env.dpndc[i].func(win);
			break ;
		}
	if (env.dpndc[i].kernel_name)
		mlx_put_image_to_window(env.mlx_p, win->win_p, win->pixels.p, 0, 0);
	ft_print_debug(env, win);
	return (0);
}
