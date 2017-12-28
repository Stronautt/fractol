/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:01:23 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/28 16:31:10 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_make_draw_dependencies(t_env *env)
{
	const t_dpndc	dpndc[] = {
		{MANDELFRACT, (void (*)(void *))&ft_mandelfract, F_MF, K_MF},
		{BURNINGSHIP, (void (*)(void *))&ft_burningshipfract, F_BS, K_BS},
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
	main = ft_new_win(env, W_WIDTH, W_HEIGHT, PROGRAM_NAME);
	mlx_hook(main->win_p, 2, 0, &ft_key_handler, main);
}

int		main(void)
{
	static t_env	env;

	ft_make_draw_dependencies(&env);
	ft_make_environment(&env);
	ft_new_win(&env, W_WIDTH, W_HEIGHT, MANDELFRACT);
	ft_new_win(&env, W_WIDTH, W_HEIGHT, BURNINGSHIP);
	ft_init_mandelfract(ft_get_win(env.wins, MANDELFRACT));
	ft_init_buringship(ft_get_win(env.wins, BURNINGSHIP));
	ft_draw(env, ft_get_win(env.wins, MANDELFRACT));
	ft_draw(env, ft_get_win(env.wins, BURNINGSHIP));
	mlx_loop(env.mlx_p);
	return (0);
}
