/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 18:46:54 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/02 21:22:06 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double		ft_lerp(double a, double b, double t)
{
	return ((1.0 - t) * a + t * b);
}

void		ft_make_draw_dependencies(t_env *env)
{
	const t_dpndc	dpndc[] = {{MANDELFRACT, &ft_mandelfract, F_MF, K_MF},
		{BURNINGSHIP, &ft_burningshipfract, F_BS, K_BS},
		{JULIAFRACT, &ft_julia, F_JF, K_JF},
		{TRICORNFRACT, &ft_tricornfract, F_TF, K_TF},
		{FERNFRACT, &ft_fernfract, 0, 0},
		{PYTHTREEFRACT, &ft_pythtreefract, 0, 0},
		{FRACTTREE, &ft_fracttree, 0, 0},
		{SIERPINSKI, &ft_sierpinski, 0, 0}, {0, 0, 0, 0}};
	const t_dpndc	init_table[] = {{MANDELFRACT, &ft_init_mandelfract, 0, 0},
		{BURNINGSHIP, &ft_init_buringship, 0, 0},
		{JULIAFRACT, &ft_init_julia, 0, 0},
		{TRICORNFRACT, &ft_init_tricornfract, 0, 0},
		{FERNFRACT, &ft_init_fernfract, 0, 0},
		{PYTHTREEFRACT, &ft_init_pythtree, 0, 0},
		{FRACTTREE, &ft_init_fracttree, 0, 0},
		{SIERPINSKI, &ft_init_sierpinski, 0, 0}, {0, 0, 0, 0}};

	!(env->dpndc = malloc(sizeof(dpndc))) ?
								ft_err_handler("Memmory fail!", NULL, 0) : 0;
	!(env->init_table = malloc(sizeof(init_table))) ?
								ft_err_handler("Memmory fail!", NULL, 0) : 0;
	ft_memmove(env->dpndc, dpndc, sizeof(dpndc));
	ft_memmove(env->init_table, init_table, sizeof(init_table));
}

void		ft_make_environment(t_env *env)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		ft_err_handler("SDL", SDL_GetError(), 0);
	ft_init_cl(env, CL_DEVICE_TYPE_GPU);
	// mlx_hook(main->win_p, 2, 0, &ft_key_handler, main);
	// mlx_mouse_hook(main->win_p, &ft_menu_mouse_handler, main);
}
