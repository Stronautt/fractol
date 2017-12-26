/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:01:23 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/26 17:26:11 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_make_draw_dependencies(t_env *env)
{
	const t_dpndc	dpndc[] = {
		{PROGRAM_NAME, (void (*)(void *))&ft_mandelfract},
		{BURNINGSHIP, (void (*)(void *))&ft_burningshipfract},
		{NULL, NULL}
	};

	env->dpndc = malloc(sizeof(dpndc));
	ft_memmove(env->dpndc, dpndc, sizeof(dpndc));
}

void	ft_make_environment(t_env *env)
{
	t_window	*main;
	t_window	*burningship;

	*env = (t_env){
		.mlx_p = mlx_init()
	};
	main = ft_new_win(env, W_WIDTH, W_HEIGHT, PROGRAM_NAME);
	mlx_hook(main->win_p, 2, 0, &ft_key_handler, main);
	mlx_mouse_hook(main->win_p, &ft_mouse_handler, main);
	main->pivot.x = -0.75;
	main->pivot.y = 0.0;
	main->dx = 0.002;
	burningship = ft_new_win(env, W_WIDTH, W_HEIGHT, BURNINGSHIP);
	mlx_hook(burningship->win_p, 2, 0, &ft_key_handler, burningship);
	mlx_mouse_hook(burningship->win_p, &ft_mouse_handler, burningship);
	burningship->pivot.x = -0.75;
	burningship->pivot.y = 0.0;
	burningship->dx = 0.003;
}

int		main(int ac, char **av)
{
	static t_env	env;

	(void)ac;
	(void)av;
	ft_make_environment(&env);
	ft_make_draw_dependencies(&env);
	ft_parse_z_buff(env, ft_get_win(env.wins, BURNINGSHIP));
	ft_parse_z_buff(env, ft_get_win(env.wins, PROGRAM_NAME));
	mlx_loop(env.mlx_p);
	return (0);
}
