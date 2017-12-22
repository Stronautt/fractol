/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_managing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:18:42 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/21 12:25:36 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_window	*ft_new_win(t_env *env, int width, int height, char *title)
{
	t_window	*new;

	if (!(new = (t_window *)ft_memalloc(sizeof(t_window))))
		ft_err_handler("Can't create new window!", title, 0);
	if (!env->wins)
	{
		if (!(env->wins = (t_window *)ft_memalloc(sizeof(t_window))))
			ft_err_handler("Can't create new window!", title, 0);
		env->wins->next = env->wins;
		env->wins->prev = env->wins;
	}
	new->width = width;
	new->height = height;
	new->title = ft_strdup(title);
	new->win_p = mlx_new_window(env->mlx_p, width, height, title);
	new->pixels.z_buff = ft_init_z_buffer(*new);
	new->pixels.p = mlx_new_image(env->mlx_p, width, height);
	new->pixels.buff = mlx_get_data_addr(new->pixels.p, &new->pixels.bpp,
		&new->pixels.s_l, &new->pixels.endian);
	env->wins->next->prev = new;
	new->next = env->wins->next;
	new->prev = env->wins;
	env->wins->next = new;
	new->env = env;
	mlx_hook(new->win_p, 17, 0, &ft_destroy_win, new);
	return (new);
}

t_window	*ft_get_win(t_window *wins, const char *title)
{
	t_window	*win;

	win = wins;
	while ((win = win->next) != wins)
		if (!ft_strcmp(win->title, title))
			return (win);
	return (NULL);
}

int			ft_destroy_win(t_window	*win)
{
	win->next->prev = win->prev;
	win->prev->next = win->next;	
	!ft_strcmp(win->title, PROGRAM_NAME) ? exit (0) : 0;
	ft_memdel((void **)&win->title);
	ft_memdel((void **)&win);
	return (0);
}
