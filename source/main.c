/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:46:02 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/30 11:24:16 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_make_draw_dependencies(t_env *env)
{
	const t_dpndc	dpndc[] = {
		{PROGRAM_NAME, &ft_menu, NULL, NULL},
		{MANDELFRACT, &ft_mandelfract, F_MF, K_MF},
		{BURNINGSHIP, &ft_burningshipfract, F_BS, K_BS},
		{JULIAFRACT, &ft_julia, F_JF, K_JF},
		{TRICORNFRACT, &ft_tricornfract, F_TF, K_TF},
		{NULL, NULL, NULL, NULL}};
	const t_dpndc	init_table[] = {
		{MANDELFRACT, &ft_init_mandelfract, NULL, NULL},
		{BURNINGSHIP, &ft_init_buringship, NULL, NULL},
		{JULIAFRACT, &ft_init_julia, NULL, NULL},
		{TRICORNFRACT, &ft_init_tricornfract, NULL, NULL},
		{NULL, NULL, NULL, NULL}};

	!(env->dpndc = malloc(sizeof(dpndc))) ? ft_err_handler("Memmory fail!",
															NULL, 0) : 0;
	!(env->init_table = malloc(sizeof(init_table))) ?
								ft_err_handler("Memmory fail!", NULL, 0) : 0;
	ft_memmove(env->dpndc, dpndc, sizeof(dpndc));
	ft_memmove(env->init_table, init_table, sizeof(init_table));
}

void	ft_make_environment(t_env *env)
{
	t_window	*main;

	env->mlx_p = mlx_init();
	ft_init_cl(env, CL_DEVICE_TYPE_GPU);
	main = ft_new_win(env, MW_WIDTH, MW_HEIGHT, PROGRAM_NAME);
	ft_draw(*env, main);
	mlx_hook(main->win_p, 2, 0, &ft_key_handler, main);
	mlx_mouse_hook(main->win_p, &ft_menu_mouse_handler, main);
}

int		main(void)
{
	static t_env	env;

	ft_make_draw_dependencies(&env);
	ft_make_environment(&env);
	mlx_loop(env.mlx_p);
	return (0);
}
