/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 13:48:24 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/24 17:30:03 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_vertice	**ft_init_z_buffer(t_window win)
{
	t_vertice	**z_buff;
	int			y;

	if (!(z_buff = (t_vertice **)malloc(sizeof(t_vertice *) * win.height)))
		ft_err_handler("Z_Buffer alloation fails!", NULL, 0);
	y = -1;
	while (++y < win.height)
		if (!(z_buff[y] = (t_vertice *)malloc(sizeof(t_vertice) * win.width)))
			ft_err_handler("Z_Buffer alloation fails!", NULL, 0);
	return (z_buff);
}

void		ft_clear_window(t_window *win)
{
	intmax_t	x;
	intmax_t	y;
	int			bytespp;

	mlx_clear_window(win->env->mlx_p, win->win_p);
	bytespp = win->pixels.bpp / 8;
	ft_bzero(win->pixels.buff, win->height * win->width * bytespp);
	y = -1;
	while (++y < win->height && (x = -1))
		while (++x < win->width)
			win->pixels.z_buff[y][x] = (t_vertice){.z = 0, .color = 0};
}

void		ft_fill_image(t_window *win)
{
	int			x;
	int			y;
	int			bpp;
	unsigned	c;

	bpp = win->pixels.bpp / 8;
	y = -1;
	while (++y < win->height && (x = -1))
		while (++x < win->width)
		{
			c = win->pixels.z_buff[y][x].color;
			if (win->pixels.endian)
				ft_strrev((char *)&c);
			ft_memcpy(win->pixels.buff + y * win->pixels.s_l + x * bpp,
				&c, bpp);
		}
}

void		ft_parse_z_buff(t_env env, t_window *win)
{
	int		i;

	ft_clear_window(win);
	i = -1;
	while (env.dpndc[++i].key)
		if (!ft_strcmp(win->title, env.dpndc[i].key)
			&& env.dpndc[i].func)
				env.dpndc[i].func(win);
	ft_fill_image(win);
	mlx_put_image_to_window(env.mlx_p, win->win_p, win->pixels.p, 0, 0);
}
