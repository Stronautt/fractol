/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:46:02 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/29 18:42:27 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_make_draw_dependencies(t_env *env)
{
	const t_dpndc	dpndc[] = {
		{PROGRAM_NAME, (void (*)(void *))&ft_menu, NULL, NULL},
		{MANDELFRACT, (void (*)(void *))&ft_mandelfract, F_MF, K_MF},
		{BURNINGSHIP, (void (*)(void *))&ft_burningshipfract, F_BS, K_BS},
		{JULIAFRACT, (void (*)(void *))&ft_julia, F_JF, K_JF},
		{NULL, NULL, NULL, NULL}
	};

	!(env->dpndc = malloc(sizeof(dpndc))) ? ft_err_handler("Memmory fail!",
															NULL, 0) : 0;
	ft_memmove(env->dpndc, dpndc, sizeof(dpndc));
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
