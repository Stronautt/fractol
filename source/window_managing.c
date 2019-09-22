/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_managing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:18:42 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/30 11:13:58 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			init_data(t_env *env, t_window *w)
{
	int		i;

	w->win_p = SDL_CreateWindow(w->title, SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, w->width, w->height, SDL_WINDOW_OPENGL);
	w->surface = SDL_GetWindowSurface(w->win_p);
	w->cl_data.mem = clCreateBuffer(env->cl_data.context, CL_MEM_READ_WRITE,
				w->surface->h * w->surface->pitch, NULL, NULL);
	i = -1;
	while (env->dpndc[++i].func)
		if (!ft_strcmp(w->title, env->dpndc[i].key))
			break ;
	if (env->dpndc[i].func && env->dpndc[i].kernel_name)
		ft_parse_kernel(env, w,
			env->dpndc[i].kernel_name, env->dpndc[i].func_name);
}

t_window			*ft_new_win(t_env *env, int width, int height, char *title)
{
	t_window	*new;

	!(new = (t_window *)ft_memalloc(sizeof(t_window))) ? exit(-1) : 0;
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
	env->wins->next->prev = new;
	new->next = env->wins->next;
	new->prev = env->wins;
	new->env = env;
	init_data(env, new);
	return (env->wins->next = new);
}

t_window			*ft_get_win(t_window *wins, const char *title)
{
	t_window	*win;

	win = wins;
	while ((win = win->next) != wins)
		if (!ft_strcmp(win->title, title))
			return (win);
	return (NULL);
}

int					ft_destroy_win(t_window *win)
{
	win->next->prev = win->prev;
	win->prev->next = win->next;
	!ft_strcmp(win->title, PROGRAM_NAME) ? exit(0) : 0;
	win->safe_m ? SDL_DestroyWindow(win->win_p) : 0;
	clReleaseMemObject(win->cl_data.mem);
	clReleaseProgram(win->cl_data.program);
	clReleaseKernel(win->cl_data.kernel);
	ft_memdel((void **)&win->title);
	ft_memdel((void **)&win);
	return (0);
}
